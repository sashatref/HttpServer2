#include "../project_pch.h"
#include "ihandler.h"

#include "../httpexception.h"


namespace HttpServer2Qt
{

IHandler::~IHandler()
{

}

RestApiHandler::Format IHandler::getFormat() const
{
    return m_format;
}

const QVariantMap &IHandler::getParams() const
{
    return m_info.getParams();
}

const QMap<CIString, QString> &IHandler::getCookie() const
{
    return m_info.getCookies();
}

const QMap<CIString, QString> &IHandler::getHeaders() const
{
    return m_info.getHeaders();
}

const ResponceInfo &IHandler::getResponseInfo() const
{
    return m_info;
}

void IHandler::nonAuthorized(const QString &_path)
{
    throw HttpUnauthorizedException(_path, QString("Unauthorized access"));
}

void IHandler::internalServerError(const QString &_text)
{
    throw HttpInternalException(_text);
}

void IHandler::invalidParameterValue(const QString &_paramName, const QString &_paramValue)
{
    throw HttpClientException(QString("Invalid parameter value. Parameter <%1> | Value <%2>")
                              .arg(_paramName)
                              .arg(_paramValue));
}

void IHandler::checkRequiredParam(const QStringList &_paramNames)
{
    const QVariantMap &m = getParams();
    for(int i = 0, count = _paramNames.size(); i < count; i++)
    {
        if(!m.contains(_paramNames.at(i)))
        {
            throw HttpClientException(QString("Required parameters not specified <%1> from values <%2>")
                                      .arg(_paramNames.at(i))
                                      .arg(_paramNames.join(", ")));
        }
    }
}

void IHandler::checkRequiredParam(const QString &_paramName)
{
    checkRequiredParam(QStringList() << _paramName);
}

}
