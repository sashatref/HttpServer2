#ifndef ENUMS_H
#define ENUMS_H

#include <QMetaEnum>
#include "../../export.h"

namespace WebSocketApiQt
{

class HTTP_SERVER_EXPORT Enums
{
    Q_GADGET
public:
    enum QueryType{
        qtUnknown = -1,
        qtAdd,
        qtEdit,
        qtRemove,
        qtEnum
    };
    Q_ENUM(QueryType)

    static QueryType queryTypeFromString(const QString &_text);
    static QString queryTypeToString(const QueryType &_qType);
};

}

#endif // ENUMS_H
