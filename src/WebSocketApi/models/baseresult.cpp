#include "baseresult.h"

namespace WebSocketApiQt
{

BaseResult::BaseResult():
    apiVer      (-1),
    result      (),
    statusCode  (-1),
    errMsg      ()
{

}

BaseResult::~BaseResult()
{

}

}
