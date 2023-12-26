#include "gzipstreamer.h"


namespace HttpServer2Qt
{

GZipStreamer::GZipStreamer():
    m_enabled               (true),
    m_gzipCompressLevel     (3),
    m_sourceDataSizeLimit   (20_mb)
{
    m_gzipMimeTypes
            << "text/html"
            << "text/css"
            << "application/javascript"
            << "application/json";
}

void GZipStreamer::process(HttpRequest *_req, HttpResponse *_res, const QByteArray &_sourceData, const QString &_contentType)
{
    QBuffer buff(const_cast<QByteArray*>(&_sourceData));
    buff.open(QIODevice::ReadOnly);

    process(_req, _res, &buff, _contentType);
}

void GZipStreamer::process(HttpRequest *_req, HttpResponse *_res, QIODevice *_sourceData, const QString &_contentType)
{
    _res->setContentType(_contentType);

    if(_req->hasClientGZipSupport() &&
            isSizeOk(_sourceData) &&
            isMatchMimeType(_contentType))
    {
        _res->setContentEncoding("gzip");
        QByteArray zipped = GZipWrapper::compressData(_sourceData->readAll(), m_gzipCompressLevel);
        _res->setContentLength(zipped.size());
        _res->sendHeaders();
        _res->writeData(zipped);
    } else
    {
        _res->setContentLength(_sourceData->size());
        _res->sendHeaders();
        _res->writeData(_sourceData->readAll());
    }
}

bool GZipStreamer::isMatchMimeType(const QString &_contentType)
{
    for(auto &it : m_gzipMimeTypes)
    {
        QRegExp regExp(it);
        regExp.setCaseSensitivity(Qt::CaseInsensitive);
        regExp.setPatternSyntax(QRegExp::Wildcard);
        if(regExp.exactMatch(_contentType))
        {
            return true;
        }
    }

    return false;
}

bool GZipStreamer::isSizeOk(const QByteArray &_data)
{
    return _data.size() < m_sourceDataSizeLimit;
}

bool GZipStreamer::isSizeOk(QIODevice *_source)
{
    return _source->size() < m_sourceDataSizeLimit;
}

}
