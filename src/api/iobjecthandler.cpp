#include "iobjecthandler.h"

#include "../httpexception.h"

namespace HttpServer2Qt
{
    int IObjectHandler::getId() const
    {
        return m_id.toInt();
    }

    QString IObjectHandler::getRawId() const
    {
        return m_id;
    }

    void IObjectHandler::invalidIdPassed(int _id)
    {
        throw HttpClientException(QString("Invalid id passed <%1>").arg(_id));
    }
}


