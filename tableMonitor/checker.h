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
    QTimer *timer;
    //Last checked row
    int last = 0;
    TableInteraction *tInter;
    QList<int> toCount;

public slots:
    int checkOne();
    int start();
    int stop();
    int pouse();
    int TableInteraction::checkStatus(QString id, QString str);
};

#endif // CHECKER_H
