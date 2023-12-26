#include "../project_pch.h"
#include "restapihandler.h"

#include "../httpexception.h"
#include "../api/iobjecthandler.h"
#include "../api/icommandhandler.h"
#include "../httprequest.h"
#include "../httpresponse.h"
#include "commoncommandhandler.h"
#include "priv/gzipstreamer.h"

namespace HttpServer2Qt
{




RestApiHandler::RestApiHandler(QObject *_parent):
    HttpRequestHandler      (_parent),
    m_objectPath            ("object"),
    m_commandPath           ("command"),
    m_gzipStreamer          (new GZipStreamer())
{

}

RestApiHandler::~RestApiHandler()
{
    delete m_gzipStreamer;
}


RestApiHandler::Action RestApiHandler::parseActionName(const QString &_text)
{
    Action action = UnknownAction;

    if(_text == m_objectPath)
    {
        action = Object;
    } else if(_text == m_commandPath)
    {
        action = Command;
    } else
    {
        throw HttpNoMethodException(QString("Incorrect api action name ('%1')").arg(_text));
    }

    return action;
}

RestApiHandler::Format RestApiHandler::parseDataFormat(const QString &_suffix)
{
    Format format = Json;

    if(_suffix == "json" || _suffix.isEmpty())
    {
        format = Json;
    } else if(_suffix == "xml")
    {
        format = Xml;
    } else
    {
        throw HttpNoMethodException(QString("Data format <%1> not supported").arg(_suffix));
    }
    return format;
}

RestApiHandler::QueryType RestApiHandler::parseQueryType(const QString &_text)
{
    QueryType type = UnknownQuery;

    if(_text == "add")
    {
        type = Add;
    } else if(_text == "edit")
    {
        type = Edit;
    } else if(_text == "enum")
    {
        type = Enum;
    } else if(_text == "delete")
    {
        type = Delete;
    } else
    {
        throw HttpNoMethodException(QString("Method not allowed ('%1')").arg(_text));
    }

    return type;
}

void RestApiHandler::checkForRegisteredObject(const QString &_objectName)
{
    if(!m_objectFact.isRegistered(_objectName))
    {
        throw HttpNoMethodException(QString("Actions for object <%1> not registered").arg(_objectName));
    }
}

void RestApiHandler::checkForRegisteredCommand(const QString &_commandName)
{
    if(!m_commandFact.isRegistered(_commandName))
    {
        throw HttpNoMethodException(QString("Actions for command <%1> not registered").arg(_commandName));
    }
}

void RestApiHandler::objectHandler(HttpRequest *_req, HttpResponse *_res,
                                   Format _format,
                                   RestApiHandler::QueryType _query,
                                   const QString &_objectName,
                                   const QString &_id)
{
    QScopedPointer<IObjectHandler> handler(m_objectFact.create(_objectName));

    handler->m_format = _format;
    handler->m_id = _id;
    handler->m_info.m_cookies = _req->getCookies();
    handler->m_info.m_headers = _req->getHeaders();
    handler->m_info.m_clientAddress = _req->getClientAddress();

    const HttpRequest::HttpMethod method = _req->getMethodEnum();

    if(_id != -1 && _query == Edit && method == HttpRequest::GET_METHOD)
    {
        throw HttpClientException(QString("Used an incorrect HTTP-method <%1>")
                                  .arg(_req->getMethod()));
    }

    QByteArray data;
    QByteArray contentType = "application/json";

    /*
        GET  /dogs/enum — получить список собак
        POST /dogs/add — создать новую собаку
        POST /dogs/edit — редактирование всех собак сразу
        POST /dogs/delete — удаление всех собак

        GET  /dogs/enum/12345 — показать информацию о собаке
        POST /dogs/edit/12345 — редактировать собаку 12345
        POST /dogs/delete/12345 — удалить
    */

    switch (method)
    {
    case HttpRequest::GET_METHOD:
        handler->m_info.m_params = parseUrlQuery(_req->getUrl().query());
        switch (_query)
        {
        case Enum:
            handler->enumRecords(data, contentType);
            break;
        default:
            throw HttpClientException(QString("Used an incorrect HTTP-method <%1>")
                                      .arg(_req->getMethod()));
            break;
        }
        break;
    case HttpRequest::POST_METHOD:
        handler->m_info.m_params = Text::parseJson(_req->readAllData());
        switch (_query)
        {
        case Add:
            handler->addRecord(data, contentType);
            break;
        case Edit:
            handler->editRecord(data, contentType);
            break;
        case Delete:
            handler->deleteRecord(data, contentType);
            break;
        case Enum:
            handler->enumRecords(data, contentType);
            break;
        default:
            throw HttpClientException(QString("Used an incorrect HTTP-method <%1>")
                                      .arg(_req->getMethod()));
            break;
        }
        break;
    default:
        throw HttpClientException(QString("Used an incorrect HTTP-method <%1>")
                                  .arg(_req->getMethod()));
        break;
    }

    _res->setResponseCode(HttpResponse::HTTP_OK);
    m_gzipStreamer->process(_req, _res, data, contentType);

    QVariantMap logMap = {
        { "path" , _req->getUrl().path() },
        { "data", handler->m_info.m_params }
    };

    emit logData(logMap, "RestApi", QtInfoMsg, _req->getClientAddress().toString());

}




void RestApiHandler::commandHandler(HttpRequest *_req, HttpResponse *_res,
                                    RestApiHandler::Format _format,
                                    const QString &_commandName)
{
    QScopedPointer<ICommandHandler> handler(m_commandFact.create(_commandName));

    handler->m_format = _format;

    if(_req->getMethodEnum() == HttpRequest::GET_METHOD)
    {
        handler->m_info.m_params = parseUrlQuery(_req->getUrl().query());
    } else
    {
        handler->m_info.m_params = Text::parseJson(_req->readAllData());
    }

    handler->m_info.m_cookies = _req->getCookies();
    handler->m_info.m_headers = _req->getHeaders();
    handler->m_info.m_clientAddress = _req->getClientAddress();

    if(!handler->allowedMethod().contains(_req->getMethod()))
    {
        throw HttpClientException(QString("Used an incorrect HTTP-method <%1>")
                                  .arg(_req->getMethod()));
    }

    QByteArray data;
    QByteArray contentType = "application/json";
    handler->execute(data, contentType);

    QString redirectUrl;
    if(handler->isRedirect(redirectUrl))
    {
        _res->setRedirect(redirectUrl, true);
        _res->sendHeaders();
        return;
    }

    _res->setResponseCode(HttpResponse::HTTP_OK);
    m_gzipStreamer->process(_req, _res, data, contentType);

    QVariantMap logMap = {
        { "path" , _req->getUrl().path() },
        { "data", handler->m_info.m_params }
    };

    emit logData(logMap, "RestApi", QtInfoMsg, _req->getClientAddress().toString());
}

void RestApiHandler::registerCommonCommand(const QString &_command,
                                           std::function<QByteArray(const ResponceInfo &, RequestData*)> _func)
{
    m_commandFact.add(_command, [=]{

        CommonCommandHandler *h = new CommonCommandHandler(_func);
        return h;
    });
}

QVariantMap RestApiHandler::parseUrlQuery(const QString &_query)
{
    QUrlQuery q(_query);

    QVariantMap out;

    for(const QPair<QString, QString> &item : q.queryItems())
    {
        out[item.first] = item.second;
    }

    return out;
}

void RestApiHandler::handleRequest(HttpRequest *_req, HttpResponse *_res)
{
    _res->setDataType(HttpResponse::Api_DATA);
    _res->setResponseCode(HttpResponse::HTTP_OK);

    QString baseUrl = _req->getUrl().path();
    QString relPath = baseUrl;


    //QVariantMap parameters = HttpParser::parseUrlParams(_socket->m_relPath, &baseUrl);

    QStringList parts = relPath.split("/", QString::SkipEmptyParts);

    if(parts.size() < 2)
    {
        throw HttpNoMethodException(QString("Method is not available Url('%1')").arg(relPath));
    }

    Action action = parseActionName(parts.at(1)); //тип действия, (object | command)
    Format format = Json;
    QString baseName;
    QString extName;

    switch(action)
    {
    case Object:
    {
        // пустое/object/<objectName>/<queryType>/<id> - необзяталеьный
        if(parts.size() < 4)
        {
            throw HttpNoMethodException(QString("Method is not available Url('%1')").arg(relPath));
        }

        QString objectName = parts.at(2); //название типа объекта

        checkForRegisteredObject(objectName);

        QueryType queryType;
        QString objectId;

        switch(parts.size())
        {
        case 4:
            baseName = QFileInfo(parts.at(3)).baseName();
            extName = QFileInfo(parts.at(3)).suffix();
            format = parseDataFormat(extName);
            queryType = parseQueryType(baseName);
            break;
        case 5:
            baseName = QFileInfo(parts.at(3)).baseName();
            extName = QFileInfo(parts.at(3)).suffix();
            format = parseDataFormat(extName);
            queryType = parseQueryType(baseName);

            objectId = parts.at(4);
            break;
        default:
            throw HttpNoMethodException(QString("Method is not available Url('%1')").arg(relPath));
            break;
        }

        objectHandler(_req, _res, format, queryType, objectName, objectId);
    }
        break;
    case Command:
    {
        // пустое/command/<commandName>
        if(parts.size() < 3)
        {
            throw HttpNoMethodException(QString("Method is not available Url('%1')").arg(relPath));
        }

        QString commandName = parts.at(2); //название типа объекта

        checkForRegisteredCommand(commandName);

        switch(parts.size())
        {
        case 3:
            baseName = QFileInfo(parts.at(2)).baseName();
            extName = QFileInfo(parts.at(2)).suffix();
            format = parseDataFormat(extName);
            break;
        default:
            throw HttpNoMethodException(QString("Method is not available Url('%1')").arg(relPath));
            break;
        }

        commandHandler(_req, _res, format, commandName);
    }
        break;
    default:
        break;
    }
}

}
