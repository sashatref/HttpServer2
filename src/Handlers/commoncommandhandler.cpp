#include "commoncommandhandler.h"

namespace HttpServer2Qt
{

CommonCommandHandler::CommonCommandHandler(Func _func):
    m_func(_func)
{

}

void CommonCommandHandler::execute(QByteArray &_data, QByteArray &_contentType)
{
    RequestData rData;
    rData.contentType = _contentType;

    _data = m_func(getResponseInfo(), &rData);

    _contentType = rData.contentType;
}

}
