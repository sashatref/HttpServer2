#include "../project_pch.h"
#include "baseobjecthandler.h"
#include "../httpexception.h"

namespace HttpServer2Qt
{

BaseObjectHandler::BaseObjectHandler(const int _typeId, const QString &_apiTypeParam):
    m_typeId(_typeId),
    m_apiTypeParam(_apiTypeParam)
{

}

void BaseObjectHandler::addRecord(QByteArray &/*_data*/, QByteArray &/*_contentType*/)
{
    QVariant addVar(m_typeId, 0);

    IGadget *gadget = GadgetHelper::getIGadget(addVar, false);
    R_ASSERT_X(gadget, "IGadget *gadget == 0");

    checkRequiredParam(m_apiTypeParam);

    QVariantMap m = getParams();
    QVariantMap apiTypeParamMap = m[m_apiTypeParam].toMap();

    GadgetHelper::fromMap(gadget, apiTypeParamMap);

    emit addObject(addVar);
}

void BaseObjectHandler::editRecord(QByteArray &/*_data*/, QByteArray &/*_contentType*/)
{
    checkRequiredParam(m_apiTypeParam);

    QVariantMap m = getParams();
    QVariantMap apiTypeParamMap = m[m_apiTypeParam].toMap();
    const int id = getId();

    QVariant editVal(m_typeId, 0);

    emit getObject(editVal, id);

    IGadget *gadget = GadgetHelper::getIGadget(editVal, false);
    if(!gadget)
    {
        throw HttpClientException(QString("Record with ID <%1> not found")
                                  .arg(id));
    }

    GadgetHelper::fromMap(gadget, apiTypeParamMap);

    emit editObject(editVal);
}

void BaseObjectHandler::deleteRecord(QByteArray &/*_data*/, QByteArray &/*_contentType*/)
{
    QVariant deleteVar(m_typeId, 0);

    IGadget *gadget = GadgetHelper::getIGadget(deleteVar, false);
    R_ASSERT_X(gadget, "IGadget *gadget == 0");

    gadget->setProperty("id", getId());

    emit removeObject(deleteVar);
}

void BaseObjectHandler::enumRecords(QByteArray &_data, QByteArray &/*_contentType*/)
{
    const QVariantMap &inMap = getParams();

    int countRecord = 10;
    if(inMap.contains("countRecord"))
    {
        countRecord = inMap["countRecord"].toInt();
    }

    int page = inMap["page"].toInt();
    page = Numerics::fixValue(page, 1, INT_MAX);

    const QVariantMap filters = inMap["filters"].toMap();
    const QVariantMap sorting = inMap["sorting"].toMap();
    const QVariantMap equals = inMap["equals"].toMap();

    QStringList fields = inMap["fields"].toStringList();

    QVector<QVariant> data;
    emit getObjectList(data, m_typeId);

    auto filterFunc = [&](const QVariant &_dataItem) -> bool
    {
        const IGadget *gadget = GadgetHelper::getIGadget(_dataItem, false);
        R_ASSERT_X(gadget, "const IGadget *gadget == 0");

        bool isOk = false;

        for(auto it = filters.begin(); it != filters.end(); ++it)
        {
            const QString key = it.key();
            const QString value = it.value().toString();

            isOk = gadget->getProperty(key).toString().contains(value, Qt::CaseInsensitive);

            if(!isOk)
                return false;
        }


        for(auto it = equals.begin(); it != equals.end(); ++it)
        {
            const QVariant propValue = gadget->getProperty(it.key());

            if(it.value().type() == QVariant::Double)
            {
                isOk = propValue.toInt() == it.value().toInt();
            } else
            {
                isOk = propValue.toString() == it.value().toString();
            }

            if(!isOk)
                return false;
        }

        return true;
    };

    QVector<QVariant> filtered;

    for(auto &it : data)
    {
        if(filterFunc(it))
        {
            filtered << it;
        }
    }

    auto sortFunc = [sorting](const QVariant &_val1, const QVariant &_val2) -> bool
    {
        const IGadget *gadget1 = GadgetHelper::getIGadget(_val1, false);
        const IGadget *gadget2 = GadgetHelper::getIGadget(_val2, false);
        R_ASSERT_X(gadget1, "const IGadget *gadget1 == 0");
        R_ASSERT_X(gadget2, "const IGadget *gadget2 == 0");

        for(auto it = sorting.begin(); it != sorting.end(); ++it)
        {
            const QString key = it.key();
            const QString value = it.value().toString();

            bool res = gadget1->getProperty(key) < gadget2->getProperty(key);

            if(value == "asc")
            {
                res = !res;
            }

            return res;
        }

        return false;
    };

    qSort(filtered.begin(), filtered.end(), sortFunc);

    int start = (page - 1) * countRecord;
    Numerics::fixValue(start, 0, INT_MAX);

    if(start > filtered.size())
        invalidParameterValue("page", QString::number(page));

    int end = start + countRecord;
    if(end > filtered.size())
    {
        end = filtered.size();
    }

    QVariantMap m;
    QVariantList list;



    if(fields.isEmpty())
    {
        QVariant var(m_typeId, 0);
        const IGadget *gad = GadgetHelper::getIGadget(var, false);
        fields = gad->getPropertyNameList();
    }

    for(int i = start ; i < end; ++i)
    {
        const IGadget *gadget = GadgetHelper::getIGadget(filtered.at(i), false);
        R_ASSERT_X(gadget, "const IGadget *gadget == 0");
        list << GadgetHelper::toMap(gadget, fields);
    }

    m["totalCount"] = filtered.size();
    m["list"] = list;

    _data = Text::writeToJson(m);
}



}
