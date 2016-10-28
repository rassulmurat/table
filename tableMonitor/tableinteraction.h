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
    int populate();
    int readTblIo();
    int writeTblIo();
    int writeRow(QList<QString> list);

private:
    QObject *object;
    QList<QList<QString>> tableList;
    const QString filePath = "table.bin";

public slots:
    void appendSlot(QString name, QString ipaddr);
    void editSlot(QString id, QString name, QString ipaddr);
};

#endif // TABLEINTERACTION_H
