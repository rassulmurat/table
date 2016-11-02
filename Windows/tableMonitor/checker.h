#ifndef CHECKER_H
#define CHECKER_H

#include "tableinteraction.h"
#include <QTimer>
#include <QLibrary>
#include "checklib.h"

class Checker: public QObject
{
    Q_OBJECT
public:
    Checker(TableInteraction *inter);
    int populateToCount();

private:
    //Last checked row
    int last = 0;
    TableInteraction *tInter;
    //List of ID's to check.
    QList<int> toCount;
    CheckLib *checkLib;
    bool isWorking;
    int finish();

public slots:
    int checkOne();
    int start();
    int stop();
    int pouse();
    int checkStatus(QString id, QString str);
    void processFinished(QList<QString> list, int exitCode);
};

#endif // CHECKER_H
