#pragma once

#include "iobjecthandler.h"
#include "../export.h"


namespace HttpServer2Qt
{

class HTTP_SERVER_EXPORT BaseObjectHandler : public QObject, public IObjectHandler
{
    Q_OBJECT
public:
    BaseObjectHandler(const int _typeId, const QString &_apiTypeParam);

    virtual void addRecord(QByteArray &_data, QByteArray &_contentType) override;
    virtual void editRecord(QByteArray &_data, QByteArray &_contentType) override;
    virtual void deleteRecord(QByteArray &_data, QByteArray &_contentType) override;
    virtual void enumRecords(QByteArray &_data, QByteArray &_contentType) override;

signals:
    void addObject(const QVariant &_val);
    void editObject(const QVariant &_val);
    void getObject(QVariant &_val, const int _id);
    void removeObject(const QVariant &_val);
    void getObjectList(QVector<QVariant> &_data, const int _typeId);

protected:
    const int m_typeId;
    const QString m_apiTypeParam;
};

}

