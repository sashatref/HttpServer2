#include "filesystemrequesthandler.h"

#include "httprequest.h"
#include "httpresponse.h"
#include "httpexception.h"
#include "priv/utils.h"
#include "priv/gzipstreamer.h"

namespace HttpServer2Qt
{

class FileSystemRequestHandlerP
{
public:
    bool m_useCache = true;
    bool m_log = false;

    bool m_phpSupport = false;
    QString m_phpPath = "php-cgi.exe";

    QString m_wwwPath;

    GZipStreamer m_gzipStreamer;

    const qint64 m_bufferSize = 8192;
};

FileSystemRequestHandler::FileSystemRequestHandler(const QString &_wwwPath):
    p               (new FileSystemRequestHandlerP())
{
    p->m_wwwPath = _wwwPath;
}

FileSystemRequestHandler::~FileSystemRequestHandler()
{

}

static QVariantMap convert(const QMap<CIString, QString> &_in)
{
    QVariantMap out;

    for(auto it = _in.begin(); it != _in.end(); ++it)
    {
        out[it.key()] = it.value();
    }

    return out;
}

void FileSystemRequestHandler::setUseCache(bool _b)
{
    p->m_useCache = _b;
}

void FileSystemRequestHandler::handleRequest(HttpRequest *_req, HttpResponse *_res)
{   
    _res->setDataType(HttpResponse::Static_DATA);

    QString relPath = _req->getUrl().path();

    if (relPath.contains(".."))
    {
        throw HttpClientException("Path must not contain characters [..]");
    }

    QString fullPath = p->m_wwwPath + relPath;

    QVariantMap m = {
        { "relPath" , relPath },
        { "absPath", fullPath },
        { "userAgent", _req->getUserAgent() }
    };

    emit logData(m, "FileSystem", QtInfoMsg, _req->getClientAddress().toString());

    QSharedPointer<QIODevice> inputDevice = createDevice(fullPath);

    if(fullPath.isEmpty() || !inputDevice->open(QIODevice::ReadOnly))
    {
        throw HttpNotFound(QString("File [%1] not found").arg(relPath));
    }

    if(p->m_log)
    {
        zDebug() << "Request path: " << relPath;
    }

    if(ckeckCache(fullPath, relPath, _req, _res))
    {
        return;
    }

    QString mimeType = QMimeDatabase().mimeTypeForFile(fullPath).name();


    if(_req->getMethod() == HttpRequest::HTTP_HEAD)
    {
        _res->setResponseCode(HttpResponse::HTTP_OK);

        if(p->m_useCache)
        {
            _res->setLastModified(HTTP::createHttpDateForFile(fullPath));
            _res->setEtag(makeEtag(fullPath));
        }

        _res->setHeader("Accept-Ranges", "bytes");
        _res->setContentType(mimeType);
        _res->setContentLength(inputDevice->size());
        _res->sendHeaders();
    }

    if(_req->getMethod() == HttpRequest::HTTP_GET)
    {
        _res->setResponseCode(HttpResponse::HTTP_OK);

        if(p->m_useCache)
        {
            _res->setLastModified(HTTP::createHttpDateForFile(fullPath));
            _res->setEtag(makeEtag(fullPath));
        }

        _res->setHeader("Accept-Ranges", "bytes");
        _res->setContentType(mimeType);

        const QMap<CIString, QString> headers = _req->getHeaders();

        if(headers.contains("Range"))
        {
            qint64 rangeStart = 0;
            qint64 rangeEnd = inputDevice->size();
            if(parseRangeHeader(headers, rangeStart, rangeEnd, inputDevice->size()) && rangeStart != rangeEnd)
            {
                sendFileRange(*_res, inputDevice.data(), rangeStart, rangeEnd);
            } else
            {
                _res->writeErrorJson(HttpResponse::HTTP_REQUESTED_RANGE_NOT_SATISFIABLE,
                                     QString("Range header [%1] is not valid").arg(headers["Range"]));
            }
        } else
        {
            sendFile(*_req, *_res, inputDevice.data(), mimeType);
        }
    }
}

QSharedPointer<QIODevice> FileSystemRequestHandler::createDevice(const QString &_fileName)
{
    return QSharedPointer<QIODevice>(new QFile(_fileName));
}

QByteArray FileSystemRequestHandler::dataProxy(QIODevice *input, qint64 _countOfBytes)
{
    return input->read(_countOfBytes);
}

bool FileSystemRequestHandler::ckeckCache(const QString &_fullPath, const QString &_relPath, HttpRequest *_req, HttpResponse *_res)
{
    if(p->m_useCache)
    {
        QString lastModif;
        if(Utils::parseIsModifiedSinceHeader(_req->getHeaders(), lastModif))
        {
            QString realModif = HTTP::createHttpDateForFile(_fullPath);

            if(p->m_log)
            {
                zDebug() << QString("File <%1> send code 'Not Modified'").arg(_relPath);
            }

            if(realModif == lastModif)
            {
                _res->setResponseCode(HttpResponse::HTTP_NOT_MODIFIED);
                _res->sendHeaders();
                return true;
            }
        }

        QString etag;
        if(Utils::parseIsEtagHeader(_req->getHeaders(), etag))
        {
            QString realEtag = makeEtag(_fullPath);

            if(p->m_log)
            {
                zDebug() << QString("File <%1> send code 'Etag Not Modified'").arg(_relPath);
            }

            if(realEtag == etag)
            {
                _res->setResponseCode(HttpResponse::HTTP_NOT_MODIFIED);
                _res->sendHeaders();
                return true;
            }
        }
    }

    return false;
}


void FileSystemRequestHandler::writeSync(const QByteArray &_data, HttpResponse *_res)
{
    //qDebug() << QString(_data).toStdString().c_str();

    _res->writeData(_data);
}

QString FileSystemRequestHandler::makeEtag(const QString &filePath)
{
    QFileInfo fI(filePath);
    return QString::number(fI.lastModified().toSecsSinceEpoch(), 16);
}



bool FileSystemRequestHandler::parseRangeHeader(const QMap<CIString, QString> &_headers,
                                                qint64 &_from, qint64 &_to, const qint64 _bufferSize)
{
    QString range = _headers["Range"];
    QStringList items = range.split("=");
    if(items.size() == 2)
    {
        QStringList subIt = items.last().split("-");
        if(subIt.size() == 2)
        {
            _from = subIt.first().toLongLong();

            bool isOk = false;
            _to = subIt.last().toLongLong(&isOk) + 1;

            if(!isOk)
            {
                _to = _bufferSize;
            }

            return true;
        }
    }

    return false;
}

void FileSystemRequestHandler::sendFileRange(HttpResponse &response, QIODevice *f, qint64 rangeStart, qint64 rangeEnd)
{
    const int contentLength = rangeEnd - rangeStart;

    response.setResponseCode(HttpResponse::HTTP_PARTIAL_CONTENT);
    response.setContentLength(contentLength);

    QString bytesExpr = QString("bytes %1-%2/%3")
            .arg(rangeStart)
            .arg(rangeEnd - 1)
            .arg(f->size());

    response.setHeader("Content-Range", bytesExpr);
    response.sendHeaders();

    copyDataChunked(f, &response, rangeStart, rangeEnd);
}

void FileSystemRequestHandler::sendFile(HttpRequest &request, HttpResponse &response, QIODevice *_f, const QString &_mediaType)
{
    qint64 fileSize = _f->size();

    response.setResponseCode(HttpResponse::HTTP_OK);

    if(p->m_gzipStreamer.isSizeOk(_f) && p->m_gzipStreamer.m_enabled)
    {
        p->m_gzipStreamer.process(&request, &response, _f, _mediaType);
    } else
    {
        response.setContentType(_mediaType);
        response.setContentLength(fileSize);
        response.sendHeaders();
        copyDataChunked(_f, &response, 0, _f->size());
    }
}

void FileSystemRequestHandler::copyDataChunked(QIODevice *_src, HttpResponse *_dect, qint64 _from, qint64 _to)
{
    _src->seek(_from);

    qint64 est = _to - _from;

    if(p->m_log)
    {
       zDebug() << "copyDataChunked | Est:" << est << " | FileSize:" << _src->size() << " | From:" << _from << " | To:" << _to;
    }

    while(!_src->atEnd() && est > 0)
    {
        if(!_dect->isWrittable())
        {
            break;
        }

        const qint64 actualBuffSize = qMin(est, p->m_bufferSize);

        QByteArray dataChunck = dataProxy(_src, actualBuffSize);
        est -= dataChunck.size();

        writeSync(dataChunck, _dect);
    }
}

QByteArray FileSystemRequestHandler::gzipData(QIODevice *_source)
{
    return GZipWrapper::compressData(_source->readAll(), 6);
}

bool FileSystemRequestHandler::isGzipHeaderPresent(const QMap<CIString, QString> &_headers)
{
    return Utils::findCookieListValue(_headers.value("Accept-Encoding"), "gzip");
}

}
