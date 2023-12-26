#include "connectionworker.h"
#include "httprequest.h"

#include "httpresponseimpl.h"
#include "httprequestimpl.h"
#include "httprequesthandler.h"
#include "httpexception.h"

namespace HttpServer2Qt
{

ConnectionWorker::ConnectionWorker(qintptr _handle, ServerMonitor *_monitor,
                                   HttpRequestHandlerFactory *_factory,
                                   const ServerOptions &_opt):
    m_handle        (_handle),
    m_factory       (_factory),
    m_opt           (_opt),
    m_monitor       (_monitor)
{
    connect(this, &ConnectionWorker::addApiRequest, _monitor, &ServerMonitor::addApiRequest);
    connect(this, &ConnectionWorker::addStaticRequest, _monitor, &ServerMonitor::addStaticRequest);
}

void ConnectionWorker::run()
{
    QTcpSocket *sock = nullptr;

    QTcpSocket socket;
    QSslSocket sslSocket;

    sock = m_opt.sslEnabled ? &sslSocket : &socket;

    if(!sock->setSocketDescriptor(m_handle))
    {
        return;
    }

    if(m_opt.sslEnabled)
    {
        sslSocket.setLocalCertificate(m_opt.sslCertificate);
        sslSocket.setPrivateKey(m_opt.sslKey);
        sslSocket.setPeerVerifyMode(QSslSocket::VerifyNone);

        sslSocket.startServerEncryption();
        sslSocket.waitForEncrypted();
    }

    HttpRequestImpl req(sock);
    if(!req.readHeaders())
    {
        return;
    }

    HttpResponseImpl res(sock, m_opt);
    res.setDate(HTTP::createHttpDate(QDateTime::currentDateTime()));
    if(!m_opt.serverName.isEmpty())
    {
        res.setServerName(m_opt.serverName);
    }

    QObject::connect(&res, &HttpResponseImpl::newApiData, m_monitor, &ServerMonitor::addApiSize);
    QObject::connect(&res, &HttpResponseImpl::newStaticData, m_monitor, &ServerMonitor::addStaticSize);

    QString relPath = req.getUrl().path();
    QString redirectTo = checkForRedirect(relPath);
    if(!redirectTo.isEmpty())
    {
        res.setRedirect(redirectTo, true);
        res.sendHeaders();
    } else
    {
        QScopedPointer<HttpRequestHandler> handler(m_factory->handleRequest(&req, &res));

        try
        {
            if(handler)
            {
                handler->handleRequest(&req, &res);
            }
        } catch(HttpClientException &e)
        {
            writeJsonError(handler.data(), &res, &req, HttpResponse::HTTP_BAD_REQUEST, QString::fromUtf8(e.what()));
        }catch(HttpUnauthorizedException &e)
        {
            writeJsonError(handler.data(), &res, &req, HttpResponse::HTTP_UNAUTHORIZED, QString::fromUtf8(e.what()));
        }catch(HttpNoImplementedException &e)
        {
            writeJsonError(handler.data(), &res, &req, HttpResponse::HTTP_NOT_IMPLEMENTED, QString::fromUtf8(e.what()));
        }catch(HttpNoMethodException &e)
        {
            writeJsonError(handler.data(), &res, &req, HttpResponse::HTTP_METHOD_NOT_ALLOWED, QString::fromUtf8(e.what()));
        }catch(HttpInternalException &e)
        {
            writeJsonError(handler.data(), &res, &req, HttpResponse::HTTP_INTERNAL_SERVER_ERROR, QString::fromUtf8(e.what()));
        }
        catch(HttpNotFound &e)
        {
            writeJsonError(handler.data(), &res, &req, HttpResponse::HTTP_NOT_FOUND, QString::fromUtf8(e.what()));
        }
        catch(HttpUserError &e)
        {
            writeJsonError(handler.data(), &res, &req, e.httpCode, QString::fromUtf8(e.what()), e.data);
        }
        catch(std::exception &e)
        {
            writeJsonError(handler.data(), &res, &req, HttpResponse::HTTP_INTERNAL_SERVER_ERROR, QString::fromUtf8(e.what()));
            qWarning() << "ConnectionWorker::run() | Unhandeled std::exception:" << e.what();
        }catch(...)
        {
            writeJsonError(handler.data(), &res, &req, HttpResponse::HTTP_INTERNAL_SERVER_ERROR, "unknown error");
            qWarning() << "ConnectionWorker::run() | Unhandeled unknown exception";
        }

        switch(res.getDataType())
        {
        case HttpResponse::Api_DATA:
            emit addApiRequest();
            break;
        case HttpResponse::Static_DATA:
            emit addStaticRequest();
            break;
        }
    }

    if(sock->state() == QAbstractSocket::ConnectedState)
    {
        sock->waitForBytesWritten();
        sock->disconnectFromHost();

        if(sock->state() == QAbstractSocket::ConnectedState)
        {
            sock->waitForDisconnected();
        }
    }
}

QString ConnectionWorker::checkForRedirect(const QString &_relPath)
{
    for(const auto &redirect : m_opt.redirects)
    {
        if(redirect.first.exactMatch(_relPath))
        {
            return redirect.second;
        }
    }

    return QString();
}

void ConnectionWorker::writeJsonError(HttpRequestHandler *_handler,
                                  HttpResponse *_response,
                                    HttpRequest *_req,
                                  int _code,
                                  const QString &_msg,
                                  const QVariantMap &_userData)
{
    _response->writeErrorJson(_code, _msg, _userData);

    QVariantMap errorData = {
        { "code", _code },
        { "message", _msg },
        { "userData", _userData }
    };

    emit _handler->logData(errorData, "ConnectionWorker", QtCriticalMsg, _req->getClientAddress().toString());
}

}
