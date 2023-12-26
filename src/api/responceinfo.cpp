#include "responceinfo.h"
#include "../httpexception.h"
#include "utils.h"

namespace HttpServer2Qt
{

const QMap<CIString, QString> &ResponceInfo::getCookies() const
{
    return m_cookies;
}

const QVariantMap &ResponceInfo::getParams() const
{
    return m_params;
}

const QMap<CIString, QString> &ResponceInfo::getHeaders() const
{
    return m_headers;
}

QString ResponceInfo::parseAuthToken() const
{
    auto it = m_headers.find("Authorization");
    if(it == m_headers.end())
    {
        throw HttpUnauthorizedException("", QString("No 'Authorization' header"));
    }

    QStringList tokens = QString(it.value()).split(" ");
    if(tokens.size() != 2)
    {
        throw HttpUnauthorizedException("",
                                        QString("Invalid 'X-Authorization' value. Must be 2 parts after split with space"));
    }

//    if(tokens[0] == "BASE-TOKEN")
//    {
//        QVariantMap map = Utils::parseCookies(tokens[1]);

//        const QString sessionKey = map["sessionKey"].toString();
//        const int userId = map["userId"].toInt();

//        if(map["sessionKey"].isNull())
//        {
//            throw HttpUnauthorizedException("",
//                                            QString("'X-Authorization' => value 'sessionKey' not specified"));
//        }

//        if(map["userId"].isNull())
//        {
//            throw HttpUnauthorizedException("",
//                                            QString("'X-Authorization' => value 'userId' not specified"));
//        }

//        res = qMakePair(userId, sessionKey);
    if(tokens[0] == "Bearer")
    {
        return tokens[1];
    }
    else
    {
        throw HttpUnauthorizedException("", QString("'Authorization' type <%1> not supported")
                                        .arg(tokens[0]));
    }

    return QString();
}

const QHostAddress &ResponceInfo::getClientAddress() const
{
    return m_clientAddress;
}

}
