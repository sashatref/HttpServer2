#pragma once

#include <QtCore/qglobal.h>

#ifdef HttpServer2_BUILD_STATIC
    #define HTTP_SERVER_EXPORT
#else
    #if defined(HTTP_SERVER2_DEFINE)
        #define HTTP_SERVER_EXPORT Q_DECL_EXPORT
    #else
        #define HTTP_SERVER_EXPORT Q_DECL_IMPORT
    #endif
#endif
