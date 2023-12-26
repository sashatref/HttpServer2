#pragma once

#include "export.h"

namespace HttpServer2Qt
{

struct StatusInfo
{
    qint64 totalTransferredStatic = 0;      //bytes
    qint64 totalRequestStatic = 0;          //count

    qint64 totalTransferredApi = 0;         //bytes
    qint64 totalRequestApi = 0;             //count

    qint64 uptime = 0;                      //seconds
};

class HTTP_SERVER_EXPORT ServerMonitor : public QObject
{
    Q_OBJECT
public:
    ServerMonitor(QObject *_parent = nullptr);

    void setUpdateInteval(int _ms);
    int getUpdateInterval() const;

    StatusInfo getStatusInfo() const;

public slots:
    void start();
    void stop();

    void addStaticSize(qint64 _bytes);
    void addApiSize(qint64 _bytes);

    void addStaticRequest();
    void addApiRequest();

signals:
    void statusChanged(const StatusInfo &_info);

private slots:
    void timedoutSlot();

private:
    QTimer *m_timer = nullptr;
    StatusInfo m_statusInfo;

    QDateTime m_startDt;
};

}
