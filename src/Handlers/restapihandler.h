#pragma once

#include "../export.h"

#include <HelperLibrary/objectfactory.h>
#include "../httprequesthandler.h"


/*
    /api/command/getAosTypes

    /api/object/aosMistake/enum
*/

/*
    GET  /dogs/enum — получить список собак
    POST /dogs/add — создать новую собаку
    POST /dogs/edit — редактирование всех собак сразу
    POST /dogs/delete — удаление всех собак

    GET  /dogs/enum/12345 — показать информацию о собаке
    POST /dogs/edit/12345 — редактировать собаку 12345
    POST /dogs/delete/12345 — удалить
*/

class QUrlQuery;

namespace HttpServer2Qt
{

struct RequestData;
class IObjectHandler;
class ICommandHandler;
class ResponceInfo;
class GZipStreamer;

class HTTP_SERVER_EXPORT RestApiHandler : public HttpRequestHandler
{
    Q_OBJECT
public:
    enum Format
    {
        UnknownFromat,
        Json,
        Xml
    };

    enum Action
    {
        UnknownAction,
        Object,
        Command
    };

    enum QueryType
    {
        UnknownQuery,
        Enum,
        Add,
        Edit,
        Delete
    };

    RestApiHandler(QObject *_parent = 0);
    ~RestApiHandler();

    const QString m_objectPath;
    const QString m_commandPath;

    GZipStreamer *m_gzipStreamer = nullptr;

    ObjectFactory<IObjectHandler, QString> m_objectFact;
    ObjectFactory<ICommandHandler, QString> m_commandFact;

    void registerCommonCommand(const QString &_command,
                               std::function<QByteArray(const ResponceInfo &, RequestData*)> _func);

    template<class T>
    void registerCommonCommand(const QString &_command,
                               T *_obj,
                               QByteArray (T::*func)(const ResponceInfo&))
    {
        auto newFunc = std::bind(func, _obj, std::placeholders::_1);
        registerCommonCommand(_command, newFunc);
    }

    template<class T>
    void registerCommonCommand(const QString &_command,
                               T *_obj,
                               QByteArray (T::*func)(const ResponceInfo&, RequestData*))
    {
        auto newFunc = std::bind(func, _obj, std::placeholders::_1, std::placeholders::_2);
        registerCommonCommand(_command, newFunc);
    }

    template<class T>
    void registerCommonCommand(const QString &_command, T *_obj, QByteArray (T::*func)())
    {
        auto newFunc = std::bind(func, _obj);
        registerCommonCommand(_command, newFunc);
    }

signals:
    void message(const QString &_text, QtMsgType _msgType);

private:
    static QVariantMap parseUrlQuery(const QString &_query);

    Action parseActionName(const QString &_text);

    static Format parseDataFormat(const QString &_suffix);
    static QueryType parseQueryType(const QString &_text);

    void checkForRegisteredObject(const QString &_objectName);
    void checkForRegisteredCommand(const QString &_commandName);

    void objectHandler(HttpRequest *_req, HttpResponse *_res,
                       Format _format,
                       QueryType _query,
                       const QString &_objectName,
                       const QString &_id);

    void commandHandler(HttpRequest *_req, HttpResponse *_res,
                       Format _format, const
                        QString &_commandName);

    QVariantMap parseParameters(const QString &_url);

    // HttpRequestHandler interface
public:
    virtual void handleRequest(HttpRequest *_req, HttpResponse *_res) override final;
};

}

