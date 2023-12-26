#include "enums.h"

namespace WebSocketApiQt
{

Enums::QueryType Enums::queryTypeFromString(const QString &_text)
{
    if(_text == "add")
    {
        return qtAdd;
    } else if(_text == "edit")
    {
        return qtEdit;
    } else if(_text == "delete")
    {
        return qtRemove;
    } else if(_text == "enum")
    {
        return qtEnum;
    }
    return qtUnknown;
}

QString Enums::queryTypeToString(const Enums::QueryType &_qType)
{
    switch(_qType)
    {
    case qtAdd:
        return "add";
        break;
    case qtEdit:
        return "edit";
        break;
    case qtRemove:
        return "delete";
        break;
    case qtEnum:
        return "enum";
        break;
    }

    return "";
}

}
