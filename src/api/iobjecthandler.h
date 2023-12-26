#ifndef HTTP2_IOBJECTHANDLER_H
#define HTTP2_IOBJECTHANDLER_H

#include "../Handlers/restapihandler.h"
#include "ihandler.h"
#include "../export.h"

#include <HelperLibrary/setgetMacro.h>

namespace HttpServer2Qt
{

class HTTP_SERVER_EXPORT IObjectHandler : public IHandler
{
    friend class RestApiHandler;
public:
    virtual void addRecord(QByteArray &_data, QByteArray &_contentType) = 0;
    virtual void editRecord(QByteArray &_data, QByteArray &_contentType) = 0;
    virtual void deleteRecord(QByteArray &_data, QByteArray &_contentType) = 0;
    virtual void enumRecords(QByteArray &_data, QByteArray &_contentType) = 0;

    int getId() const;
    QString getRawId() const;

protected:
    void invalidIdPassed(int _id);

private:
    QString m_id;
};

}

#endif // HTTP2_IOBJECTHANDLER_H
