#pragma once

#ifdef _DEBUG
    #ifdef USE_VLD
        #include <vld.h>
    #endif
#endif

#include <limits>

#include <QBuffer>
#include <QTimer>
#include <QUrl>
#include <QHostAddress>
#include <QWebSocketServer>
#include <QSslError>
#include <QWebSocket>
#include <QTcpServer>
#include <QThread>
#include <QThreadPool>
#include <QRunnable>
#include <QEventLoop>
#include <QReadWriteLock>
#include <QMimeDatabase>
#include <QSslKey>
#include <QSslCertificate>
#include <QUrlQuery>
#include <QMimeDatabase>
#include <QProcess>

#define PERFORMANCE_CHECK

#include <HelperLibrary/functions.h>
#include <HelperLibrary/Exceptions/userexception.h>
#include <HelperLibrary/converterfunctions.h>
#include <HelperLibrary/igadget.h>
#include <HelperLibrary/releaseassert.h>
#include <HelperLibrary/anymacro.h>
#include <HelperLibrary/setgetMacro.h>
#include <HelperLibrary/signalwaiter.h>
#include <HelperLibrary/leakchecker.h>

#include <HelperLibrary/ZipManager/gzipwrapper.h>

#include <HelperLibrary/Logger/logger.h>
#include <HelperLibrary/Logger/loggermacro.h>
#include <HelperLibrary/cistring.h>

using namespace HelperLibrary;
using HelperLibraryNS::LeakChecker;

#define ProjectName "HttpServer2"
#define zDebug() wDebugCat(ProjectName)
#define zInfo() wInfoCat(ProjectName)
#define zCritical() wCriticalCat(ProjectName)
#define zWarning() wWarningCat(ProjectName)
