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
public:
    TableInteraction(QObject *obj);
    int appendRow(QString check, int id, QString name, QString ip, QString status);
    int editRow(QString check, int id, QString name, QString ip, QString status);
    int populate();
    int readTblIo();
    int writeTblIo();

public slots:
    void appendSlot(QString name, QString ipaddr);

private:
    QObject *object;
    QList<QList<QString>> tableList;
    const QString filePath = "table.bin";
};

#endif // TABLEINTERACTION_H
