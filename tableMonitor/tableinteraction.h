#ifndef TABLEINTERACTION_H
#define TABLEINTERACTION_H

#include <QVariantList>
#include <QObject>
#include <QList>
#include <QFile>
#include <QDataStream>
#include <QDebug>

class TableInteraction : public QObject
{
    Q_OBJECT
public:
    TableInteraction(QObject *obj);
    int appendRow(int id, QList<QString> list);
    int editRow(QString check, int id, QString name, QString ip, QString status, QString latency);
    int editStatus(int id, QString status, QString latency);
    int getRow(QList<QString> *list, int pos);
    int setRow(QList<QString> list, int pos);
    QObject *getObj();
    int size();
    QList<QList<QString>> *getTable();
    void setTable(QList<QList<QString>> list);
    int setResponse(int id, QList<QString> list);
    int setRole(int id, int role, QString value);

private:
    QObject *object;
    QList<QList<QString>> tableList;
    const QString filePath = "table.bin";
    int populate();
    const int rolesSize = 5;

public slots:
    void appendSlot(QString name, QString ipaddr);
    void editSlot(QString id, QString name, QString ipaddr);
    void removeRow(QString id);
};

#endif // TABLEINTERACTION_H
