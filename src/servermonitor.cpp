#include "servermonitor.h"

namespace HttpServer2Qt
{

ServerMonitor::ServerMonitor(QObject *_parent):
    QObject(_parent)
{
    m_timer = new QTimer(this);
    setUpdateInteval(1000);

    connect(m_timer, &QTimer::timeout, this, &ServerMonitor::timedoutSlot);
}

void ServerMonitor::setUpdateInteval(int _ms)
{
    m_timer->setInterval(_ms);
}

int ServerMonitor::getUpdateInterval() const
{
    return m_timer->interval();
}

StatusInfo ServerMonitor::getStatusInfo() const
{
    return m_statusInfo;
}

void ServerMonitor::start()
{
    m_startDt = QDateTime::currentDateTime();

    m_timer->start();
}

void ServerMonitor::stop()
{
    m_timer->stop();
}

void ServerMonitor::addStaticSize(qint64 _bytes)
{
    m_statusInfo.totalTransferredStatic += _bytes;
}

void ServerMonitor::addApiSize(qint64 _bytes)
{
    m_statusInfo.totalTransferredApi = _bytes;
}

void ServerMonitor::addStaticRequest()
{
    m_statusInfo.totalRequestStatic++;
}

void ServerMonitor::addApiRequest()
{
    m_statusInfo.totalRequestApi++;
}

void ServerMonitor::timedoutSlot()
{
    m_statusInfo.uptime = m_startDt.secsTo(QDateTime::currentDateTime());

    emit statusChanged(m_statusInfo);
}

}
