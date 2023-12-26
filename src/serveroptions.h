#pragma once

#include "export.h"

#include <QSslKey>
#include <QSslCertificate>
#include <QList>
#include <QRegExp>

namespace HttpServer2Qt
{

class LogConfig
{
    bool logAccess = false;
    QString logAccessFile;

    bool logErrors = false;
    QString logErrorsFile;
};

class HTTP_SERVER_EXPORT ServerOptions
{
public:
    ServerOptions();

    bool sslEnabled = false;
    QSslKey sslKey;
    QSslCertificate sslCertificate;
    int port = 80;

    QString serverName; //имя сервера, которое будет использоваться при формирование заголовков ответа
    int poolThreadCount;   //количество потоков HTTP сервера
    QList<QPair<QRegExp, QString>> redirects;   //перенаправления, используемые в HTTP сервере

    LogConfig logConfig;

    void addToIndexRedirect();  //добавляем стандартный редирект / => /index.html
};

}

