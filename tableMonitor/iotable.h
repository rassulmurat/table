#ifndef IOTABLE_H
#define IOTABLE_H

#include <QList>
#include <QObject>
#include <tableinteraction.h>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QUrl>

class IOTable : QObject
{
    Q_OBJECT
public:
    IOTable(TableInteraction *obj);
    int setPath(QString);

private:
    int readTable(QList<QList<QString>> *list);
    int writeTable(QList<QList<QString>> *list);
    TableInteraction *table;
    QString filepath = QString("undefined.csv");

public slots:
    void save();
    void saveAs(QUrl path);
    void load();
    void loadAs(QUrl path);
};

#endif // IOTABLE_H
