#include "tableinteraction.h"

TableInteraction::TableInteraction(QObject *obj): QObject()
{
    object = obj;
    QObject::connect(obj, SIGNAL(appendSign(QString, QString)), this, SLOT(appendSlot(QString, QString)));
    QObject::connect(obj, SIGNAL(editSign(QString, QString, QString)), this, SLOT(editSlot(QString, QString, QString)));
    QObject::connect(obj, SIGNAL(removeSign(QString)), this, SLOT(removeRow(QString)));
}

int TableInteraction::appendRow(int id, QList<QString> list)
{
    QVariantList listVar;
    QString idstr = QString::number(id);
    for (int i = 0; i < list.size(); ++i) {
        if (i == 1) {
            listVar.append(id);
        }
        listVar.append(list[i]);
    }
    QMetaObject::invokeMethod(object, "appendRow", Q_ARG(QVariant, QVariant::fromValue(listVar)));
    return 0;
}

int TableInteraction::editRow(QString check, int id, QString name, QString ip, QString status, QString latency)
{
    QVariantList list;
    QString idstr = QString::number(id);
    list<<check<<idstr<<name<<ip<<status<<latency;
    QList<QString> tmp;
    tmp.append(check);
    tmp.append(name);
    tmp.append(ip);
    tmp.append(status);
    tmp.append(latency);
    tableList[id] = tmp;
    QMetaObject::invokeMethod(object, "modifyRow", Q_ARG(QVariant, QVariant::fromValue(list)));
    return 0;
}

 void TableInteraction::removeRow(QString id)
 {
    tableList.removeAt(id.toInt());
 }

 int TableInteraction::setResponse(int id, QList<QString> listStr)
 {
    QVariantList varList;
    varList<<id<<listStr[0]<<listStr[1];

    tableList[id].replace(3, listStr[0]);
    tableList[id].replace(4, listStr[1]);
    QMetaObject::invokeMethod(object, "setResponse", Q_ARG(QVariant, QVariant::fromValue(varList)));
    return 0;
 }

 int TableInteraction::setRole(int id, int role, QString value)
 {
    QVariantList varList;

    for (int i = 0; i < rolesSize; ++i) {
        if (role != i) {
            if (i == 1) {
                varList.append(id);
            }
            varList.append(tableList[id].value(i));
        } else {
            tableList[id].replace(role, value);
            varList.append(value);
        }
    }

    QMetaObject::invokeMethod(object, "modifyRow", Q_ARG(QVariant, QVariant::fromValue(varList)));
    return 0;
 }

/*
 *Populates table from tableList
*/
int TableInteraction::populate()
{
    for (int i = 0; i < tableList.size(); ++i) {
        QList<QString> list = tableList[i];
        appendRow(i+1, list);
    }
    return 0;
}

int TableInteraction::editStatus(int id, QString status, QString latency)
{
    QList<QString> list;
    getRow(&list, id);
    editRow(list[0], id, list[1], list[2], status, latency);
    return 0;
}

void TableInteraction::appendSlot(QString name, QString ipaddr)
{
    int size = tableList.size();
    QList<QString> list;
    list.append("true");
    list.append(name);
    list.append(ipaddr);
    list.append("New");
    list.append(("New"));
    tableList.append(list);
    appendRow(size + 1, list);
}

void TableInteraction::editSlot(QString id, QString name, QString ipaddr)
{
    int realid = id.toInt() - 1;
    QList<QString> list = tableList[realid];
    editRow(list[0], realid, name, ipaddr, list[3], list[4]);
}

int TableInteraction::getRow(QList<QString> *list, int pos)
{
    if (pos > tableList.size() - 1)
        return 1;
    *list = tableList[pos];
    return 0;
}

int TableInteraction::setRow(QList<QString> list, int pos)
{
    if (pos > tableList.size() - 1)
        return 1;
    tableList[pos] = list;
    return 0;
}

int TableInteraction::size()
{
    return tableList.size();
}

QObject *TableInteraction::getObj()
{
    return object;
}

QList<QList<QString>> *TableInteraction::getTable()
{
    return &tableList;
}

void TableInteraction::setTable(QList<QList<QString>> list)
{
    tableList = list;
    populate();
}


