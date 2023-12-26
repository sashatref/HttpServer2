#include "httpapihelper.h"
#include "httpexception.h"

namespace HttpServer2Qt
{


void HttpApiHelper::nonAuthorized(const QString &_path)
{
    throw HttpUnauthorizedException(_path, QString("Unauthorized access"));
}

void HttpApiHelper::internalServerError(const QString &_text)
{
    throw HttpInternalException(_text);
}

void HttpApiHelper::invalidParameterValue(const QString &_paramName, const QString &_paramValue)
{
    throw HttpClientException(QString("Invalid parameter value. Parameter <%1> | Value <%2>")
                              .arg(_paramName)
                              .arg(_paramValue));
}

void HttpApiHelper::checkRequiredParam(const QStringList &_paramNames, const QVariantMap &_allParams)
{
    const QVariantMap &m = _allParams;
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

void HttpApiHelper::checkRequiredParam(const QString &_paramName, const QVariantMap &_allParams)
{
    checkRequiredParam(QStringList() << _paramName, _allParams);
}

}
