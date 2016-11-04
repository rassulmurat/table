#ifndef CHECKER_H
#define CHECKER_H

#include "tablemodel.h"
#include <QTimer>
#include <QLibrary>
#include "checklib.h"

class TestNetwork: public QObject
{
    Q_OBJECT
public:
    TestNetwork(TableModel *inter);
    int populateToCount();

private:
    //Last checked row
    int last = 0;

    TableModel *tInter;

    //List of ID's to check.
    QList<int> toCount;

    //Dynamic link library.
    CheckLib *checkLib;

    //True if test is in progress. Otherwise , false.
    bool isWorking;

    //When the network testing is finished
    int finish();

    //Check next row
    int testNext();

public slots:
    //Below are listed slots for connecting to dll.
    int start();
    int stop();
    int pouse();

    //Below are listed slot for connecting to gui.
    int checkStatus(QString id, QString str);
    void processFinished(QString str, int exitCode);
    void pingTested(QString ping, int exitCode);
};

#endif // CHECKER_H
