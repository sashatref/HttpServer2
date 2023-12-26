#pragma once

#include "../httprequesthandler.h"

#include "../export.h"

#include <HelperLibrary/cistring.h>
#include <QScopedPointer>

class QIODevice;

namespace HttpServer2Qt
{

class FileSystemRequestHandlerP;
class HTTP_SERVER_EXPORT FileSystemRequestHandler : public HttpRequestHandler
{
    Q_OBJECT
    QScopedPointer<FileSystemRequestHandlerP> p;
public:
    FileSystemRequestHandler(const QString &_wwwPath);
    ~FileSystemRequestHandler();

    void setUseCache(bool _b);

public:
    virtual void handleRequest(HttpRequest *_req, HttpResponse *_res) override;

protected:
    virtual QSharedPointer<QIODevice> createDevice(const QString &_fileName);
    virtual QByteArray dataProxy(QIODevice *input, qint64 _countOfBytes);

private:
    //true если обработано, если кэш совпадает и отправка файла не требуется
    bool ckeckCache(const QString &_fullPath, const QString &_relPath, HttpRequest *_req, HttpResponse *_res);

    void writeSync(const QByteArray &_data, HttpResponse *_res);

    QString makeEtag(const QString &filePath);

    bool parseRangeHeader(const QMap<CIString, QString> &_headers,
                                      qint64 &_from,
                                      qint64 &_to,
                                      const qint64 _bufferSize);

    void sendFileRange(HttpResponse& response, QIODevice *f, qint64 rangeStart, qint64 rangeEnd);
    void sendFile(HttpRequest &request, HttpResponse& response, QIODevice *_f, const QString &_mediaType);

    void copyDataChunked(QIODevice *_src, HttpResponse *_dect, qint64 _from, qint64 _to);

    static QByteArray gzipData(QIODevice *_source);
    static bool isGzipHeaderPresent(const QMap<CIString, QString> &_headers);
};

}

