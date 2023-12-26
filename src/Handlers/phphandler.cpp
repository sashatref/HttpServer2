#include "phphandler.h"

#include "httprequest.h"
#include "httpresponse.h"
#include "httpexception.h"

namespace HttpServer2Qt
{
    PhpHandler::PhpHandler():
        m_phpPath("D:/Dependency/php-7.3.10-nts-Win32-VC15-x64/php-cgi.exe")
    {

    }

    void PhpHandler::handleRequest(HttpRequest *_req, HttpResponse *_res)
    {
        QProcess process;

        //const QString filePath = _req->getUrl().path();
        const QString filePath = "/index.php";
        const QString scriptName = QFileInfo(filePath).fileName();

        QString documentRoot = "D:/git_projects/CBTS/cbts-backend/public";

        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

        env.insert("AUTH_TYPE", "BASIC");
        env.insert("CONTENT_LENGTH", QString::number(_req->getContentLength()));
        env.insert("CONTENT_TYPE", _req->getContentType());
        env.insert("GETAWAY_INTERFACE", "CGI/1.1");
        env.insert("PATH_INFO", filePath);
        env.insert("PATH_TRANSLATED", documentRoot + filePath);

        env.insert("REQUEST_METHOD", _req->getMethod());
        env.insert("QUERY_STRING", _req->getUrl().query());
        env.insert("SERVER_SOFTWARE", "HttpServer2");
        env.insert("HTTP_ACCEPT", _req->getHeaders()["Accept"]);
        env.insert("HTTP_REFERER", _req->getHeaders()["Referer"]);
        env.insert("HTTP_USER_AGENT", _req->getUserAgent());
        env.insert("HTTP HOST", "localhost");
        env.insert("SERVER_ADDR", "127.0.0.1");
        env.insert("REMOTE_PORT", "80");
        env.insert("REMOTE_ADDR", "127.0.0.1");
        env.insert("REMOTE_PORT", "80");
        env.insert("REMOTE_USER", "");
        env.insert("SCRIPT_NAME", scriptName);
        env.insert("SCRIPT_FILENAME", documentRoot + scriptName);
        env.insert("REDIRECT_STATUS", "1");
//
//        env.insert("CONTENT_FILE", scriptName);
        //env.insert("DOCUMENT_ROOT", documentRoot);

        process.setProcessEnvironment(env);
        process.setWorkingDirectory("D:/Dependency/php-7.3.10-nts-Win32-VC15-x64");
        process.start(m_phpPath, QStringList() << documentRoot + filePath );
        if(!process.waitForFinished(phpFileTimeout))
        {
            process.terminate();
            //throw HttpInternalException(QString("Php file executing timeout"));
        }

        if(process.exitCode() != 0)
        {
//            throw HttpClientException(QString("Php file executing error: %1")
//                                      .arg(QString(process.readAllStandardOutput())));
        }

        QByteArray data = process.readAllStandardOutput();

        //qDebug() << process.arguments();
        //qDebug() << data;


        QByteArray statusPart = data.mid(0, data.indexOf("\r\n"));
        if(statusPart.startsWith("Status"))
        {
            QByteArray code = statusPart.mid(statusPart.indexOf(":") + 1);
            _res->writeData("HTTP/1.1");
            _res->writeData(code);
            _res->writeData("\r\n");
        } else
        {
            _res->writeData("HTTP/1.1 200 OK\r\n");
        }

        _res->writeData(data);
    }
}

