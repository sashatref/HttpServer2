#pragma once

#include <HelperLibrary/cistring.h>
#include "serveroptions.h"


#include "export.h"
class QIODevice;
class QAbstractSocket;

namespace HttpServer2Qt
{

class HTTP_SERVER_EXPORT HttpResponse : public QObject
{
    Q_OBJECT
public:
    enum HTTPStatus
    {
        HTTP_CONTINUE                        = 100,
        HTTP_SWITCHING_PROTOCOLS             = 101,
        HTTP_PROCESSING                      = 102,
        HTTP_OK                              = 200,
        HTTP_CREATED                         = 201,
        HTTP_ACCEPTED                        = 202,
        HTTP_NONAUTHORITATIVE                = 203,
        HTTP_NO_CONTENT                      = 204,
        HTTP_RESET_CONTENT                   = 205,
        HTTP_PARTIAL_CONTENT                 = 206,
        HTTP_MULTI_STATUS                    = 207,
        HTTP_ALREADY_REPORTED                = 208,
        HTTP_IM_USED                         = 226,
        HTTP_MULTIPLE_CHOICES                = 300,
        HTTP_MOVED_PERMANENTLY               = 301,
        HTTP_FOUND                           = 302,
        HTTP_SEE_OTHER                       = 303,
        HTTP_NOT_MODIFIED                    = 304,
        HTTP_USE_PROXY                       = 305,
        HTTP_USEPROXY                        = 305, /// @deprecated
        // UNUSED: 306
        HTTP_TEMPORARY_REDIRECT              = 307,
        HTTP_PERMANENT_REDIRECT              = 308,
        HTTP_BAD_REQUEST                     = 400,
        HTTP_UNAUTHORIZED                    = 401,
        HTTP_PAYMENT_REQUIRED                = 402,
        HTTP_FORBIDDEN                       = 403,
        HTTP_NOT_FOUND                       = 404,
        HTTP_METHOD_NOT_ALLOWED              = 405,
        HTTP_NOT_ACCEPTABLE                  = 406,
        HTTP_PROXY_AUTHENTICATION_REQUIRED   = 407,
        HTTP_REQUEST_TIMEOUT                 = 408,
        HTTP_CONFLICT                        = 409,
        HTTP_GONE                            = 410,
        HTTP_LENGTH_REQUIRED                 = 411,
        HTTP_PRECONDITION_FAILED             = 412,
        HTTP_REQUEST_ENTITY_TOO_LARGE        = 413,
        HTTP_REQUESTENTITYTOOLARGE           = 413, /// @deprecated
        HTTP_REQUEST_URI_TOO_LONG            = 414,
        HTTP_REQUESTURITOOLONG               = 414, /// @deprecated
        HTTP_UNSUPPORTED_MEDIA_TYPE          = 415,
        HTTP_UNSUPPORTEDMEDIATYPE            = 415, /// @deprecated
        HTTP_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
        HTTP_EXPECTATION_FAILED              = 417,
        HTTP_IM_A_TEAPOT                     = 418,
        HTTP_ENCHANCE_YOUR_CALM              = 420,
        HTTP_MISDIRECTED_REQUEST             = 421,
        HTTP_UNPROCESSABLE_ENTITY            = 422,
        HTTP_LOCKED                          = 423,
        HTTP_FAILED_DEPENDENCY               = 424,
        HTTP_UPGRADE_REQUIRED                = 426,
        HTTP_PRECONDITION_REQUIRED           = 428,
        HTTP_TOO_MANY_REQUESTS               = 429,
        HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
        HTTP_UNAVAILABLE_FOR_LEGAL_REASONS   = 451,
        HTTP_INTERNAL_SERVER_ERROR           = 500,
        HTTP_NOT_IMPLEMENTED                 = 501,
        HTTP_BAD_GATEWAY                     = 502,
        HTTP_SERVICE_UNAVAILABLE             = 503,
        HTTP_GATEWAY_TIMEOUT                 = 504,
        HTTP_VERSION_NOT_SUPPORTED           = 505,
        HTTP_VARIANT_ALSO_NEGOTIATES         = 506,
        HTTP_INSUFFICIENT_STORAGE            = 507,
        HTTP_LOOP_DETECTED                   = 508,
        HTTP_NOT_EXTENDED                    = 510,
        HTTP_NETWORK_AUTHENTICATION_REQUIRED = 511
    };

    enum DataType
    {
        Api_DATA,
        Static_DATA
    };

    QString defaultReasonForCode(int _code);

    HttpResponse(QAbstractSocket *_sock, const ServerOptions &_opt);
    ~HttpResponse();

    void beginTransaction();
    void commiTransaction();

    void setDataType(DataType _dt);
    void setResponseCode(int _code, QString _reason = "");
    void setHeader(const QString &_key, const QString &_value);

    void setContentEncoding(const QString &_encoding);
    void setContentLength(qint64 _fileSize);
    void setContentType(const QString &_mimeType);
    void setLastModified(const QString &_dateTime); //example : Wed, 11 Feb 2009 11:20:59 GMT
    void setRedirect(const QString &_path, bool _permanent);
    void setDate(const QString &_dateTime);
    void setServerName(const QString &_name);
    void setEtag(const QString &_etag);

    void sendHeaders();

    void writeErrorJson(int _code, const QString &_msg, const QVariantMap &_userData = QVariantMap());

    void writeData(const QByteArray &_data);
    void writeData(const QString &_data);
    void writeData(const char *_data);

    bool isWrittable() const;

    DataType getDataType() const;

    static const QString HTTP_REASON_CONTINUE;
    static const QString HTTP_REASON_SWITCHING_PROTOCOLS;
    static const QString HTTP_REASON_PROCESSING;
    static const QString HTTP_REASON_OK;
    static const QString HTTP_REASON_CREATED;
    static const QString HTTP_REASON_ACCEPTED;
    static const QString HTTP_REASON_NONAUTHORITATIVE;
    static const QString HTTP_REASON_NO_CONTENT;
    static const QString HTTP_REASON_RESET_CONTENT;
    static const QString HTTP_REASON_PARTIAL_CONTENT;
    static const QString HTTP_REASON_MULTI_STATUS;
    static const QString HTTP_REASON_ALREADY_REPORTED;
    static const QString HTTP_REASON_IM_USED;
    static const QString HTTP_REASON_MULTIPLE_CHOICES;
    static const QString HTTP_REASON_MOVED_PERMANENTLY;
    static const QString HTTP_REASON_FOUND;
    static const QString HTTP_REASON_SEE_OTHER;
    static const QString HTTP_REASON_NOT_MODIFIED;
    static const QString HTTP_REASON_USE_PROXY;
    static const QString HTTP_REASON_TEMPORARY_REDIRECT;
    static const QString HTTP_REASON_PERMANENT_REDIRECT;
    static const QString HTTP_REASON_BAD_REQUEST;
    static const QString HTTP_REASON_UNAUTHORIZED;
    static const QString HTTP_REASON_PAYMENT_REQUIRED;
    static const QString HTTP_REASON_FORBIDDEN;
    static const QString HTTP_REASON_NOT_FOUND;
    static const QString HTTP_REASON_METHOD_NOT_ALLOWED;
    static const QString HTTP_REASON_NOT_ACCEPTABLE;
    static const QString HTTP_REASON_PROXY_AUTHENTICATION_REQUIRED;
    static const QString HTTP_REASON_REQUEST_TIMEOUT;
    static const QString HTTP_REASON_CONFLICT;
    static const QString HTTP_REASON_GONE;
    static const QString HTTP_REASON_LENGTH_REQUIRED;
    static const QString HTTP_REASON_PRECONDITION_FAILED;
    static const QString HTTP_REASON_REQUEST_ENTITY_TOO_LARGE;
    static const QString HTTP_REASON_REQUEST_URI_TOO_LONG;
    static const QString HTTP_REASON_UNSUPPORTED_MEDIA_TYPE;
    static const QString HTTP_REASON_REQUESTED_RANGE_NOT_SATISFIABLE;
    static const QString HTTP_REASON_EXPECTATION_FAILED;
    static const QString HTTP_REASON_IM_A_TEAPOT;
    static const QString HTTP_REASON_ENCHANCE_YOUR_CALM;
    static const QString HTTP_REASON_MISDIRECTED_REQUEST;
    static const QString HTTP_REASON_UNPROCESSABLE_ENTITY;
    static const QString HTTP_REASON_LOCKED;
    static const QString HTTP_REASON_FAILED_DEPENDENCY;
    static const QString HTTP_REASON_UPGRADE_REQUIRED;
    static const QString HTTP_REASON_PRECONDITION_REQUIRED;
    static const QString HTTP_REASON_TOO_MANY_REQUESTS;
    static const QString HTTP_REASON_REQUEST_HEADER_FIELDS_TOO_LARGE;
    static const QString HTTP_REASON_UNAVAILABLE_FOR_LEGAL_REASONS;
    static const QString HTTP_REASON_INTERNAL_SERVER_ERROR;
    static const QString HTTP_REASON_NOT_IMPLEMENTED;
    static const QString HTTP_REASON_BAD_GATEWAY;
    static const QString HTTP_REASON_SERVICE_UNAVAILABLE;
    static const QString HTTP_REASON_GATEWAY_TIMEOUT;
    static const QString HTTP_REASON_VERSION_NOT_SUPPORTED;
    static const QString HTTP_REASON_VARIANT_ALSO_NEGOTIATES;
    static const QString HTTP_REASON_INSUFFICIENT_STORAGE;
    static const QString HTTP_REASON_LOOP_DETECTED;
    static const QString HTTP_REASON_NOT_EXTENDED;
    static const QString HTTP_REASON_NETWORK_AUTHENTICATION_REQUIRED;
    static const QString HTTP_REASON_UNKNOWN;

signals:
    void newStaticData(qint64 _size);
    void newApiData(qint64 _size);

protected:
    QString m_httpVersion;
    DataType m_dt = Static_DATA;

    int m_statusCode = 0;
    QString m_statusDescription;
    QMap<CIString, QString> m_headers;

    ServerOptions m_serverOpt;
    QAbstractSocket *m_sock;

    QByteArray m_bufferedData;
    bool m_inTransaction = false;
};

}
