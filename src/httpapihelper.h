#pragma once

#include "export.h"

namespace HttpServer2Qt
{

class HTTP_SERVER_EXPORT HttpApiHelper
{
public:

    static void nonAuthorized(const QString &_path);

    static void internalServerError(const QString &_text);

    static void invalidParameterValue(const QString &_paramName, const QString &_paramValue);

    static void checkRequiredParam(const QStringList &_paramNames, const QVariantMap &_allParams);

    static void checkRequiredParam(const QString &_paramName, const QVariantMap &_allParams);

};

}
