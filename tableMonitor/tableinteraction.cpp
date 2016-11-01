#include "tableinteraction.h"

TableInteraction::TableInteraction(QObject *obj): QObject()
{
    object = obj;
    QObject::connect(obj, SIGNAL(appendSign(QString, QString)), this, SLOT(appendSlot(QString, QString)));
    QObject::connect(obj, SIGNAL(editSign(QString, QString, QString)), this, SLOT(editSlot(QString, QString, QString)));
    QObject::connect(obj, SIGNAL(removeSign(QString)), this, SLOT(removeRow(QString)));
}

int TableInteraction::appendRow(QString check, int id, QString name, QString ip, QString status)
{
    QVariantList list;
    QString idstr = QString::number(id);
    list<<check<<idstr<<name<<ip<<status;
    QMetaObject::invokeMethod(object, "appendRow", Q_ARG(QVariant, QVariant::fromValue(list)));
    return 0;
}

int TableInteraction::editRow(QString check, int id, QString name, QString ip, QString status)
{
    QVariantList list;
    QString idstr = QString::number(id);
    list<<check<<idstr<<name<<ip<<status;
    QList<QString> tmp;
    tmp.append(check);
    tmp.append(name);
    tmp.append(ip);
    tmp.append(status);
    tableList[id] = tmp;
    QMetaObject::invokeMethod(object, "modifyRow", Q_ARG(QVariant, QVariant::fromValue(list)));
    return 0;
}

 void TableInteraction::removeRow(QString id)
 {
    tableList.removeAt(id.toInt());
 }

/*
 *Populates table from tableList
*/
int TableInteraction::populate()
{
    for (int i = 0; i < tableList.size(); ++i) {
        QList<QString> list = tableList[i];
        appendRow(list[0], i+1, list[1], list[2], list[3]);
    }
    return 0;
}

int TableInteraction::editStatus(int id, QString str)
{
    QList<QString> list;
    getRow(&list, id);
    editRow(list[0], id, list[1], list[2], str);
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
    tableList.append(list);
    appendRow("true", size + 1, name, ipaddr, "New");
}

void TableInteraction::editSlot(QString id, QString name, QString ipaddr)
{
    int realid = id.toInt() - 1;
    QList<QString> list = tableList[realid];
    editRow(list[0], realid, name, ipaddr, list[3]);
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


