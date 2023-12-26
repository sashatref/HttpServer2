set(PROJECT_NAME HttpServer2)

project(${PROJECT_NAME} VERSION 1.0.0)

set(SOURCES
    Handlers/phphandler.cpp
    httpserver.cpp
    priv/gzipstreamer.cpp
    priv/httpserverp.cpp
    priv/asynctcpserver.cpp
    priv/connectionworker.cpp
    api/baseobjecthandler.cpp
    api/icommandhandler.cpp
    api/ihandler.cpp
    api/iobjecthandler.cpp
    Handlers/restapihandler.cpp
    httpexception.cpp
    httprequest.cpp
    httprequesthandler.cpp
    httprequesthandlerfactory.cpp
    httpresponse.cpp
    serveroptions.cpp
    priv/httprequestimpl.cpp
    priv/httpresponseimpl.cpp
    Handlers/filesystemrequesthandler.cpp
    Handlers/commoncommandhandler.cpp
    Handlers/datacommandhandler.cpp
    api/responceinfo.cpp
    httpapihelper.cpp
    priv/utils.cpp
    servermonitor.cpp
    Handlers/phphandler.h
    httpserver.h
    export.h
    priv/gzipstreamer.h
    priv/httpserverp.h
    httpexception.h
    priv/asynctcpserver.h
    priv/connectionworker.h
    api/baseobjecthandler.h
    api/icommandhandler.h
    api/ihandler.h
    api/iobjecthandler.h
    Handlers/restapihandler.h
    httpexception.h
    httprequest.h
    httprequesthandler.h
    httprequesthandlerfactory.h
    httpresponse.h
    serveroptions.h
    priv/httprequestimpl.h
    priv/httpresponseimpl.h
    Handlers/filesystemrequesthandler.h
    Handlers/commoncommandhandler.h
    Handlers/datacommandhandler.h
    api/responceinfo.h
    httpapihelper.h
    priv/utils.h
    servermonitor.h
    templates.qrc
    WebSocketApi/models/baserequest.cpp
    WebSocketApi/models/baseresult.cpp
    WebSocketApi/models/commandrequest.cpp
    WebSocketApi/models/commandresult.cpp
    WebSocketApi/models/enums.cpp
    WebSocketApi/models/objectrequest.cpp
    WebSocketApi/models/objectresult.cpp
    WebSocketApi/websocketapi.cpp
    WebSocketApi/websocketserver.cpp
    WebSocketApi/websocketserverp.cpp
    WebSocketApi/basewshandler.cpp
    WebSocketApi/models/baserequest.h
    WebSocketApi/models/baseresult.h
    WebSocketApi/models/commandrequest.h
    WebSocketApi/models/commandresult.h
    WebSocketApi/models/enums.h
    WebSocketApi/models/objectrequest.h
    WebSocketApi/models/objectresult.h
    WebSocketApi/websocketapi.h
    WebSocketApi/websocketserver.h
    WebSocketApi/websocketserverp.h
    WebSocketApi/basewshandler.h
)

if(${PROJECT_NAME}_BUILD_STATIC)
    set(LIB_TYPE STATIC)
else()
    set(LIB_TYPE SHARED)
endif()

add_library(${PROJECT_NAME} ${LIB_TYPE} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Network
    Qt5::WebSockets
    HelperLibrary
)

target_include_directories(${PROJECT_NAME}
    INTERFACE ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/priv
)

target_compile_definitions(${PROJECT_NAME} PRIVATE "HTTP_SERVER2_DEFINE")
target_precompile_headers(${PROJECT_NAME} PRIVATE project_pch.h)

if(NOT ${PROJECT_NAME}_BUILD_STATIC)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ".")
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_BUILD_STATIC")
endif()

moveHeaders()
deployTr()
aviaNames()
makeAI()
