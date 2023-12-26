#include "httpresponse.h"

namespace HttpServer2Qt
{

const QString HttpResponse::HTTP_REASON_CONTINUE                        = "Continue";
const QString HttpResponse::HTTP_REASON_SWITCHING_PROTOCOLS             = "Switching Protocols";
const QString HttpResponse::HTTP_REASON_PROCESSING                      = "Processing";
const QString HttpResponse::HTTP_REASON_OK                              = "OK";
const QString HttpResponse::HTTP_REASON_CREATED                         = "Created";
const QString HttpResponse::HTTP_REASON_ACCEPTED                        = "Accepted";
const QString HttpResponse::HTTP_REASON_NONAUTHORITATIVE                = "Non-Authoritative Information";
const QString HttpResponse::HTTP_REASON_NO_CONTENT                      = "No Content";
const QString HttpResponse::HTTP_REASON_RESET_CONTENT                   = "Reset Content";
const QString HttpResponse::HTTP_REASON_PARTIAL_CONTENT                 = "Partial Content";
const QString HttpResponse::HTTP_REASON_MULTI_STATUS                    = "Multi Status";
const QString HttpResponse::HTTP_REASON_ALREADY_REPORTED                = "Already Reported";
const QString HttpResponse::HTTP_REASON_IM_USED                         = "IM Used";
const QString HttpResponse::HTTP_REASON_MULTIPLE_CHOICES                = "Multiple Choices";
const QString HttpResponse::HTTP_REASON_MOVED_PERMANENTLY               = "Moved Permanently";
const QString HttpResponse::HTTP_REASON_FOUND                           = "Found";
const QString HttpResponse::HTTP_REASON_SEE_OTHER                       = "See Other";
const QString HttpResponse::HTTP_REASON_NOT_MODIFIED                    = "Not Modified";
const QString HttpResponse::HTTP_REASON_USE_PROXY                       = "Use Proxy";
const QString HttpResponse::HTTP_REASON_TEMPORARY_REDIRECT              = "Temporary Redirect";
const QString HttpResponse::HTTP_REASON_PERMANENT_REDIRECT              = "Permanent Redirect";
const QString HttpResponse::HTTP_REASON_BAD_REQUEST                     = "Bad Request";
const QString HttpResponse::HTTP_REASON_UNAUTHORIZED                    = "Unauthorized";
const QString HttpResponse::HTTP_REASON_PAYMENT_REQUIRED                = "Payment Required";
const QString HttpResponse::HTTP_REASON_FORBIDDEN                       = "Forbidden";
const QString HttpResponse::HTTP_REASON_NOT_FOUND                       = "Not Found";
const QString HttpResponse::HTTP_REASON_METHOD_NOT_ALLOWED              = "Method Not Allowed";
const QString HttpResponse::HTTP_REASON_NOT_ACCEPTABLE                  = "Not Acceptable";
const QString HttpResponse::HTTP_REASON_PROXY_AUTHENTICATION_REQUIRED   = "Proxy Authentication Required";
const QString HttpResponse::HTTP_REASON_REQUEST_TIMEOUT                 = "Request Time-out";
const QString HttpResponse::HTTP_REASON_CONFLICT                        = "Conflict";
const QString HttpResponse::HTTP_REASON_GONE                            = "Gone";
const QString HttpResponse::HTTP_REASON_LENGTH_REQUIRED                 = "Length Required";
const QString HttpResponse::HTTP_REASON_PRECONDITION_FAILED             = "Precondition Failed";
const QString HttpResponse::HTTP_REASON_REQUEST_ENTITY_TOO_LARGE        = "Request Entity Too Large";
const QString HttpResponse::HTTP_REASON_REQUEST_URI_TOO_LONG            = "Request-URI Too Large";
const QString HttpResponse::HTTP_REASON_UNSUPPORTED_MEDIA_TYPE          = "Unsupported Media Type";
const QString HttpResponse::HTTP_REASON_REQUESTED_RANGE_NOT_SATISFIABLE = "Requested Range Not Satisfiable";
const QString HttpResponse::HTTP_REASON_EXPECTATION_FAILED              = "Expectation Failed";
const QString HttpResponse::HTTP_REASON_IM_A_TEAPOT                     = "I'm a Teapot";
const QString HttpResponse::HTTP_REASON_ENCHANCE_YOUR_CALM              = "Enchance Your Calm";
const QString HttpResponse::HTTP_REASON_MISDIRECTED_REQUEST             = "Misdirected Request";
const QString HttpResponse::HTTP_REASON_UNPROCESSABLE_ENTITY            = "Unprocessable Entity";
const QString HttpResponse::HTTP_REASON_LOCKED                          = "Locked";
const QString HttpResponse::HTTP_REASON_FAILED_DEPENDENCY               = "Failed Dependency";
const QString HttpResponse::HTTP_REASON_UPGRADE_REQUIRED                = "Upgrade Required";
const QString HttpResponse::HTTP_REASON_PRECONDITION_REQUIRED           = "Precondition Required";
const QString HttpResponse::HTTP_REASON_TOO_MANY_REQUESTS               = "Too Many Requests";
const QString HttpResponse::HTTP_REASON_REQUEST_HEADER_FIELDS_TOO_LARGE = "Request Header Fields Too Large";
const QString HttpResponse::HTTP_REASON_UNAVAILABLE_FOR_LEGAL_REASONS   = "Unavailable For Legal Reasons";
const QString HttpResponse::HTTP_REASON_INTERNAL_SERVER_ERROR           = "Internal Server Error";
const QString HttpResponse::HTTP_REASON_NOT_IMPLEMENTED                 = "Not Implemented";
const QString HttpResponse::HTTP_REASON_BAD_GATEWAY                     = "Bad Gateway";
const QString HttpResponse::HTTP_REASON_SERVICE_UNAVAILABLE             = "Service Unavailable";
const QString HttpResponse::HTTP_REASON_GATEWAY_TIMEOUT                 = "Gateway Time-Out";
const QString HttpResponse::HTTP_REASON_VERSION_NOT_SUPPORTED           = "HTTP Version Not Supported";
const QString HttpResponse::HTTP_REASON_VARIANT_ALSO_NEGOTIATES         = "Variant Also Negotiates";
const QString HttpResponse::HTTP_REASON_INSUFFICIENT_STORAGE            = "Insufficient Storage";
const QString HttpResponse::HTTP_REASON_LOOP_DETECTED                   = "Loop Detected";
const QString HttpResponse::HTTP_REASON_NOT_EXTENDED                    = "Not Extended";
const QString HttpResponse::HTTP_REASON_NETWORK_AUTHENTICATION_REQUIRED = "Network Authentication Required";
const QString HttpResponse::HTTP_REASON_UNKNOWN                         = "???";

QString HttpResponse::defaultReasonForCode(int _code)
{
    switch (_code)
    {
    case HTTP_CONTINUE:
        return HTTP_REASON_CONTINUE;
    case HTTP_SWITCHING_PROTOCOLS:
        return HTTP_REASON_SWITCHING_PROTOCOLS;
    case HTTP_PROCESSING:
        return HTTP_REASON_PROCESSING;
    case HTTP_OK:
        return HTTP_REASON_OK;
    case HTTP_CREATED:
        return HTTP_REASON_CREATED;
    case HTTP_ACCEPTED:
        return HTTP_REASON_ACCEPTED;
    case HTTP_NONAUTHORITATIVE:
        return HTTP_REASON_NONAUTHORITATIVE;
    case HTTP_NO_CONTENT:
        return HTTP_REASON_NO_CONTENT;
    case HTTP_RESET_CONTENT:
        return HTTP_REASON_RESET_CONTENT;
    case HTTP_PARTIAL_CONTENT:
        return HTTP_REASON_PARTIAL_CONTENT;
    case HTTP_MULTI_STATUS:
        return HTTP_REASON_MULTI_STATUS;
    case HTTP_ALREADY_REPORTED:
        return HTTP_REASON_ALREADY_REPORTED;
    case HTTP_IM_USED:
        return HTTP_REASON_IM_USED;
    case HTTP_MULTIPLE_CHOICES:
        return HTTP_REASON_MULTIPLE_CHOICES;
    case HTTP_MOVED_PERMANENTLY:
        return HTTP_REASON_MOVED_PERMANENTLY;
    case HTTP_FOUND:
        return HTTP_REASON_FOUND;
    case HTTP_SEE_OTHER:
        return HTTP_REASON_SEE_OTHER;
    case HTTP_NOT_MODIFIED:
        return HTTP_REASON_NOT_MODIFIED;
    case HTTP_USE_PROXY:
        return HTTP_REASON_USE_PROXY;
    case HTTP_TEMPORARY_REDIRECT:
        return HTTP_REASON_TEMPORARY_REDIRECT;
    case HTTP_BAD_REQUEST:
        return HTTP_REASON_BAD_REQUEST;
    case HTTP_UNAUTHORIZED:
        return HTTP_REASON_UNAUTHORIZED;
    case HTTP_PAYMENT_REQUIRED:
        return HTTP_REASON_PAYMENT_REQUIRED;
    case HTTP_FORBIDDEN:
        return HTTP_REASON_FORBIDDEN;
    case HTTP_NOT_FOUND:
        return HTTP_REASON_NOT_FOUND;
    case HTTP_METHOD_NOT_ALLOWED:
        return HTTP_REASON_METHOD_NOT_ALLOWED;
    case HTTP_NOT_ACCEPTABLE:
        return HTTP_REASON_NOT_ACCEPTABLE;
    case HTTP_PROXY_AUTHENTICATION_REQUIRED:
        return HTTP_REASON_PROXY_AUTHENTICATION_REQUIRED;
    case HTTP_REQUEST_TIMEOUT:
        return HTTP_REASON_REQUEST_TIMEOUT;
    case HTTP_CONFLICT:
        return HTTP_REASON_CONFLICT;
    case HTTP_GONE:
        return HTTP_REASON_GONE;
    case HTTP_LENGTH_REQUIRED:
        return HTTP_REASON_LENGTH_REQUIRED;
    case HTTP_PRECONDITION_FAILED:
        return HTTP_REASON_PRECONDITION_FAILED;
    case HTTP_REQUEST_ENTITY_TOO_LARGE:
        return HTTP_REASON_REQUEST_ENTITY_TOO_LARGE;
    case HTTP_REQUEST_URI_TOO_LONG:
        return HTTP_REASON_REQUEST_URI_TOO_LONG;
    case HTTP_UNSUPPORTED_MEDIA_TYPE:
        return HTTP_REASON_UNSUPPORTED_MEDIA_TYPE;
    case HTTP_REQUESTED_RANGE_NOT_SATISFIABLE:
        return HTTP_REASON_REQUESTED_RANGE_NOT_SATISFIABLE;
    case HTTP_EXPECTATION_FAILED:
        return HTTP_REASON_EXPECTATION_FAILED;
    case HTTP_IM_A_TEAPOT:
        return HTTP_REASON_IM_A_TEAPOT;
    case HTTP_ENCHANCE_YOUR_CALM:
        return HTTP_REASON_ENCHANCE_YOUR_CALM;
    case HTTP_MISDIRECTED_REQUEST:
        return HTTP_REASON_MISDIRECTED_REQUEST;
    case HTTP_UNPROCESSABLE_ENTITY:
        return HTTP_REASON_UNPROCESSABLE_ENTITY;
    case HTTP_LOCKED:
        return HTTP_REASON_LOCKED;
    case HTTP_FAILED_DEPENDENCY:
        return HTTP_REASON_FAILED_DEPENDENCY;
    case HTTP_UPGRADE_REQUIRED:
        return HTTP_REASON_UPGRADE_REQUIRED;
    case HTTP_PRECONDITION_REQUIRED:
        return HTTP_REASON_PRECONDITION_REQUIRED;
    case HTTP_TOO_MANY_REQUESTS:
        return HTTP_REASON_TOO_MANY_REQUESTS;
    case HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE:
        return HTTP_REASON_REQUEST_HEADER_FIELDS_TOO_LARGE;
    case HTTP_UNAVAILABLE_FOR_LEGAL_REASONS:
        return HTTP_REASON_UNAVAILABLE_FOR_LEGAL_REASONS;
    case HTTP_INTERNAL_SERVER_ERROR:
        return HTTP_REASON_INTERNAL_SERVER_ERROR;
    case HTTP_NOT_IMPLEMENTED:
        return HTTP_REASON_NOT_IMPLEMENTED;
    case HTTP_BAD_GATEWAY:
        return HTTP_REASON_BAD_GATEWAY;
    case HTTP_SERVICE_UNAVAILABLE:
        return HTTP_REASON_SERVICE_UNAVAILABLE;
    case HTTP_GATEWAY_TIMEOUT:
        return HTTP_REASON_GATEWAY_TIMEOUT;
    case HTTP_VERSION_NOT_SUPPORTED:
        return HTTP_REASON_VERSION_NOT_SUPPORTED;
    case HTTP_VARIANT_ALSO_NEGOTIATES:
        return HTTP_REASON_VARIANT_ALSO_NEGOTIATES;
    case HTTP_INSUFFICIENT_STORAGE:
        return HTTP_REASON_INSUFFICIENT_STORAGE;
    case HTTP_LOOP_DETECTED:
        return HTTP_REASON_LOOP_DETECTED;
    case HTTP_NOT_EXTENDED:
        return HTTP_REASON_NOT_EXTENDED;
    case HTTP_NETWORK_AUTHENTICATION_REQUIRED:
        return HTTP_REASON_NETWORK_AUTHENTICATION_REQUIRED;
    default:
        return HTTP_REASON_UNKNOWN;
    }
}

HttpResponse::HttpResponse(QAbstractSocket *_sock, const ServerOptions &_opt):
    m_httpVersion   ("HTTP/1.1"),
    m_serverOpt     (_opt),
    m_sock          (_sock)
{

}

HttpResponse::~HttpResponse()
{

}

void HttpResponse::beginTransaction()
{
    m_inTransaction = true;
    m_bufferedData.clear();
}

void HttpResponse::commiTransaction()
{
    m_inTransaction = false;
    writeData(m_bufferedData);
}

void HttpResponse::setDataType(HttpResponse::DataType _dt)
{
    m_dt = _dt;
}

void HttpResponse::setResponseCode(int _code, QString _reason)
{
    if(_reason.isEmpty())
    {
        _reason = defaultReasonForCode(_code);
    }

    m_statusCode = _code;
    m_statusDescription = _reason;
}

void HttpResponse::setHeader(const QString &_key, const QString &_value)
{
    m_headers[_key] = _value;
}

void HttpResponse::setContentEncoding(const QString &_encoding)
{
    m_headers["Content-Encoding"] = _encoding;
}

void HttpResponse::setContentLength(qint64 _fileSize)
{
    m_headers["Content-Length"] = QString::number(_fileSize);
}

void HttpResponse::setContentType(const QString &_mimeType)
{
    m_headers["Content-Type"] = _mimeType;
}

void HttpResponse::setLastModified(const QString &_dateTime)
{
    m_headers["Last-Modified"] = _dateTime;
}

void HttpResponse::sendHeaders()
{
    QString out;
    QTextStream stream(&out);

    stream << m_httpVersion << " " << m_statusCode << " " << m_statusDescription << "\r\n";

    for(auto it = m_headers.begin(); it != m_headers.end(); ++it)
    {
        stream << it.key() << ": " << it.value() << "\r\n";
    }

    stream << "\r\n";

//    qDebug() << out.toStdString().c_str();

    writeData(out);
}

void HttpResponse::writeErrorJson(int _code, const QString &_msg, const QVariantMap &_userData)
{
    QVariantMap m;
    m["message"] = _msg;
    m["status"] = _code;

    if(!_userData.isEmpty())
    {
        m["userData"] = _userData;
    }

    setResponseCode(_code);
    setContentType("application/json");
    sendHeaders();
    writeData(Text::writeToJson(m));
}

void HttpResponse::setRedirect(const QString &_path, bool _permanent)
{
    setResponseCode(_permanent ? HttpResponse::HTTP_MOVED_PERMANENTLY : HttpResponse::HTTP_FOUND);
    setHeader("Location", _path);
}

void HttpResponse::setDate(const QString &_dateTime)
{
    setHeader("Date", _dateTime);
}

void HttpResponse::setServerName(const QString &_name)
{
    setHeader("Server", _name);
}

void HttpResponse::setEtag(const QString &_etag)
{
    setHeader("ETag", _etag);
}


void HttpResponse::writeData(const QByteArray &_data)
{  
    if(m_inTransaction)
    {
        m_bufferedData.append(_data);
        return;
    }

    if(isWrittable())
    {
        switch(m_dt)
        {
        case Static_DATA:
            emit newStaticData(_data.size());
            break;
        case Api_DATA:
            emit newApiData(_data.size());
            break;
        }

        m_sock->write(_data);
        m_sock->waitForBytesWritten(10000);
    }
}

void HttpResponse::writeData(const QString &_data)
{
    writeData(_data.toUtf8());
}

void HttpResponse::writeData(const char *_data)
{
    writeData(QString(_data));
}

bool HttpResponse::isWrittable() const
{
    return m_sock->state() == QAbstractSocket::ConnectedState;
}

HttpResponse::DataType HttpResponse::getDataType() const
{
    return m_dt;
}

}
