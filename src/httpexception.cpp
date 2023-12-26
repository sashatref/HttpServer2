#include "httpexception.h"

namespace HttpServer2Qt
{

HttpException::HttpException(const QString &_text) :
    HelperLibrary::UserExceptions::BaseException(_text, false)
{

}

HttpInternalException::HttpInternalException(const QString &_text):
    HttpException(_text)
{

}

HttpClientException::HttpClientException(const QString &_text):
    HttpException(_text)
{

}

HttpUnauthorizedException::HttpUnauthorizedException(const QString &_path,
                                                     const QString &_text):
    HttpException(_text),
    m_path(_path)
{

}

QString HttpUnauthorizedException::getPath() const
{
    return m_path;
}

HttpNoMethodException::HttpNoMethodException(const QString &_text):
    HttpException(_text)
{

}

HttpNoImplementedException::HttpNoImplementedException(const QString &_methodName):
    HttpInternalException(QString("The method is not yet implemented <%1>")
                          .arg(_methodName))
{

}

HttpNotFound::HttpNotFound(const QString &_text):
    HttpException(_text)
{

}

HttpUserError::HttpUserError(const QVariantMap &_data, int _httpCode, const QString &_text):
    HttpException(_text),
    data(_data),
    httpCode(_httpCode)
{

}



}
