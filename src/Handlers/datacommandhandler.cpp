#include "datacommandhandler.h"

namespace HttpServer2Qt
{
DataCommandHandler::DataCommandHandler(const QByteArray &_data, const QByteArray &_contentType):
    m_data          (_data),
    m_contentType   (_contentType)
{

}

void DataCommandHandler::execute(QByteArray &_data, QByteArray &_contentType)
{
    _data = m_data;
    _contentType = m_contentType;
}

QStringList DataCommandHandler::allowedMethod() const
{
    return QStringList("GET");
}

}


