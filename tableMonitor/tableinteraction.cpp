#include "tableinteraction.h"

TableInteraction::TableInteraction(QObject *obj): QObject()
{
    object = obj;
    readTblIo();
    populate();
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
    writeTblIo();
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

int TableInteraction::readTblIo()
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        printf("Could not open file\n");
        return 1;
    }
    QDataStream stream(&file);
    stream>>tableList;
    file.close();
    return 0;
}

int TableInteraction::writeTblIo()
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        printf("Could not open file\n");
        return 1;
    }
    QDataStream stream(&file);
    stream<<tableList;
    file.close();
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
    writeTblIo();
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

