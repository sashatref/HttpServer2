#pragma once

#include "httprequest.h"
#include "httpresponse.h"

namespace HttpServer2Qt
{

class GZipStreamer
{
public:
    GZipStreamer();

    bool m_enabled;
    QStringList m_gzipMimeTypes;
    int m_gzipCompressLevel;
    int m_sourceDataSizeLimit;

    void process(HttpRequest *_req, HttpResponse *_res, const QByteArray &_sourceData, const QString &_contentType);

    void process(HttpRequest *_req, HttpResponse *_res, QIODevice *_sourceData, const QString &_contentType);

    bool isMatchMimeType(const QString &_contentType);
    bool isSizeOk(const QByteArray &_data);

    bool isSizeOk(QIODevice *_source);

private:

};

}

