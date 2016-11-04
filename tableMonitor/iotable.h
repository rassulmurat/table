#ifndef IOTABLE_H
#define IOTABLE_H

#include <QList>
#include <QObject>
#include <tablemodel.h>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QUrl>

class IOTable : QObject
{
    Q_OBJECT
public:
    /*
     * This class saves/loads a table to a file
     * This file performs as a config and can be load back to the program
     * File extension is .csv
     * Table Model is needed to set/get the table to save/load
     */
    IOTable(TableModel *obj);

    //Set Path of the file to save/load
    int setPath(QString);

private:
    //Read the table from the file and saves it in the TableModel class.
    int readTable(QList<QList<QString>> *list);

    //Gets the table from the TableModel and writes it to a file
    int writeTable(QList<QList<QString>> *list);
    TableModel *table;
    QString filepath = QString("undefined.csv");

public slots:
    //Below are listed slots that are connecting to gui.
    void save();
    void saveAs(QUrl path);
    void load();
    void loadAs(QUrl path);
};

#endif // IOTABLE_H
