#include "httprequestimpl.h"

namespace HttpServer2Qt
{


HttpRequestImpl::HttpRequestImpl(QAbstractSocket *_socket):
    m_socket(_socket)
{

}

QString HttpRequestImpl::getMethod() const
{
    return m_method;
}

void HttpRequestImpl::setUrl(const QUrl &_url)
{
    m_url = _url;
}

QUrl HttpRequestImpl::getUrl() const
{
    return m_url;
}

QHostAddress HttpRequestImpl::getClientAddress() const
{
    return m_clientAddress;
}

QString HttpRequestImpl::getHttpVersion() const
{
    return m_httpVersion;
}

const QMap<CIString, QString> &HttpRequestImpl::getHeaders() const
{
    return m_headers;
}

const QMap<CIString, QString> &HttpRequestImpl::getCookies() const
{
    return m_cookies;
}

QByteArray HttpRequestImpl::getRawData() const
{
    return m_rawData;
}

bool HttpRequestImpl::readHeaders()
{
    m_rawData.clear();
    m_clientAddress = m_socket->peerAddress();

    bool isFinishReadHeaders = false;
    while(!isFinishReadHeaders && m_socket->waitForReadyRead(4000))
    {
        while(!isFinishReadHeaders && m_socket->bytesAvailable() > 0)
        {
            QByteArray chunk = m_socket->readLine();

            m_rawData += chunk;

            if(m_rawData.endsWith("\r\n\r\n"))
            {
                isFinishReadHeaders = true;
                break;
            }
        }
    }

    if(isFinishReadHeaders)
    {
        if(parseHeaders())
        {
            parseCookies();
        }
    }

    return isFinishReadHeaders;
}

QAbstractSocket *HttpRequestImpl::getSocket()
{
    return m_socket;
}

bool HttpRequestImpl::parseHeaders()
{
    m_headers.clear();

    QList<QByteArray> lines = Text::split(m_rawData, QByteArray("\r\n"), QString::SkipEmptyParts);

    if(lines.size() == 0)
    {
        return false;
    }

    {   //parse first line
        QStringList tokens = QString(lines.first()).split(" ", QString::SkipEmptyParts);

        if(tokens.size() != 3)
        {
            return false;
        }

        m_method = tokens.first().toUpper();
        m_url = QUrl(tokens.at(1));
        m_httpVersion = tokens.last();
    }

    for(int i = 1; i < lines.size(); i++)
    {
        QStringList tokens = QString(lines.at(i)).split(":");
        if(tokens.size() == 2)
        {
            m_headers[tokens.first()] = tokens.last().trimmed();
        }
    }

    return true;
}

bool HttpRequestImpl::parseCookies()
{
    QString cookieRaw = m_headers["Cookie"];

    m_cookies.clear();

    QStringList cookies = cookieRaw.split(';');
    for(int i = 0 ; i < cookies.size(); i++)
    {
        QStringList keyValue = cookies.at(i).split('=');
        if(keyValue.size() < 2)
        {
            continue;
        }

        m_cookies[keyValue[0].trimmed()] = keyValue[1].trimmed();
    }

    return true;
}

}


