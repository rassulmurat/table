#include "tablemodel.h"

TableModel::TableModel(QObject *obj): QObject()
{
    object = obj;
    QObject::connect(obj, SIGNAL(appendSign(QString, QString)), this, SLOT(appendSlot(QString, QString)));
    QObject::connect(obj, SIGNAL(editSign(QString, QString, QString)), this, SLOT(editSlot(QString, QString, QString)));
    QObject::connect(obj, SIGNAL(removeSign(QString)), this, SLOT(removeRow(QString)));
}

int TableModel::appendRow(int id, QList<QString> list)
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

int TableModel::editRow(QString check, int id, QString name, QString ip, QString status, QString latency)
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

 void TableModel::removeRow(QString id)
 {
    tableList.removeAt(id.toInt());
 }

 int TableModel::setRole(int id, int role, QString value)
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
int TableModel::populate()
{
    for (int i = 0; i < tableList.size(); ++i) {
        QList<QString> list = tableList[i];
        appendRow(i+1, list);
    }
    return 0;
}

int TableModel::editStatus(int id, QString status, QString latency)
{
    QList<QString> list;
    getRow(&list, id);
    editRow(list[0], id, list[1], list[2], status, latency);
    return 0;
}

void TableModel::appendSlot(QString name, QString ipaddr)
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

void TableModel::editSlot(QString id, QString name, QString ipaddr)
{
    int realid = id.toInt() - 1;
    QList<QString> list = tableList[realid];
    editRow(list[0], realid, name, ipaddr, list[3], list[4]);
}

int TableModel::getRow(QList<QString> *list, int pos)
{
    if (pos > tableList.size() - 1)
        return 1;
    *list = tableList[pos];
    return 0;
}

int TableModel::setRow(QList<QString> list, int pos)
{
    if (pos > tableList.size() - 1)
        return 1;
    tableList[pos] = list;
    return 0;
}

int TableModel::size()
{
    return tableList.size();
}

QObject *TableModel::getObj()
{
    return object;
}

QList<QList<QString>> *TableModel::getTable()
{
    return &tableList;
}

void TableModel::setTable(QList<QList<QString>> list)
{
    tableList = list;
    populate();
}

QString TableModel::getColumnName(int role)
{
    switch (role) {
    case CHECK:     return QString("Check");
    case NAME:      return QString("Name");
    case IP:        return QString("IP Adress");
    case SPEED:     return QString("Speed");
    case LATENCY:   return QString("Latency");
    default:        return QString("ERROR");
    }
}


