#pragma once

#include "../Handlers/restapihandler.h"
#include "../export.h"
#include "responceinfo.h"

#include <HelperLibrary/setgetMacro.h>

namespace HttpServer2Qt
{

class HTTP_SERVER_EXPORT IHandler
{
public:
    virtual ~IHandler();

    friend class RestApiHandler;

    RestApiHandler::Format getFormat() const;   //возвращает тип данных из запроса клиента

    const QVariantMap &getParams() const;   //возвращает список параметров из запроса клиента
    const QMap<CIString, QString> &getCookie() const;   //возвращает список кукисов
    const QMap<CIString, QString> &getHeaders() const;

    const ResponceInfo &getResponseInfo() const;

public:
    void nonAuthorized(const QString &_path);
    void internalServerError(const QString &_text);
    void invalidParameterValue(const QString &_paramName, const QString &_paramValue);

    void checkRequiredParam(const QStringList &_paramNames);
    void checkRequiredParam(const QString &_paramName);


private:
    RestApiHandler::Format m_format;

    ResponceInfo m_info;
};

}

