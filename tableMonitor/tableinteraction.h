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
    int appendRow(QString check, int id, QString name, QString ip, QString status);
    int editRow(QString check, int id, QString name, QString ip, QString status);
    int readTblIo();
    int writeTblIo();
    int getRow(QList<QString> *list, int pos);
    int setRow(QList<QString> list, int pos);
    QObject *getObj();
    int size();

private:
    QObject *object;
    QList<QList<QString>> tableList;
    const QString filePath = "table.bin";
    int populate();

public slots:
    void appendSlot(QString name, QString ipaddr);
    void editSlot(QString id, QString name, QString ipaddr);
    void removeRow(QString id);
};

#endif // TABLEINTERACTION_H
