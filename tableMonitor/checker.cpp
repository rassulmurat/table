#include "checker.h"

Checker::Checker(TableInteraction *inter):QObject()
{
    tInter = inter;
    isWorking = false;
    checkLib = new CheckLib();
    QObject::connect(checkLib, SIGNAL(processFinished(QList<QString>, int)), this, SLOT(processFinished(QList<QString>, int)));
    QObject::connect(tInter->getObj(), SIGNAL(startSign()), this, SLOT(start()));
    QObject::connect(tInter->getObj(), SIGNAL(stopSign()), this, SLOT(stop()));
    QObject::connect(tInter->getObj(), SIGNAL(pouseSign()), this, SLOT(pouse()));
    QObject::connect(tInter->getObj(), SIGNAL(checkSign(QString, QString)), this, SLOT(checkStatus(QString,QString)));
}

int Checker::checkOne()
{
    if (last == toCount.size()) {
        finish();
        return 0;
    }
    QList<QString> list;
    tInter->getRow(&list, toCount[last]);
    tInter->editStatus(toCount[last], "Testing");
    checkLib->check(list);
    return 0;
}

void Checker::processFinished(QList<QString> list, int exitCode)
{
    if (exitCode == 0) {
        tInter->editStatus(toCount[last], list[3]);
        last++;
        //Progression bar
        QMetaObject::invokeMethod(tInter->getObj(), "checkedAdd", Q_ARG(QVariant, (double)last/toCount.size()));
        checkOne();
    }
}

int Checker::start()
{
    if (isWorking) {
        printf("Error: Already started\n");
        return 1;
    }
    isWorking = true;
    populateToCount();
    QMetaObject::invokeMethod(tInter->getObj(), "checkedAdd", Q_ARG(QVariant, 0));
    checkOne();
    return 0;
}

int Checker::populateToCount()
{
    for (int i = 0; i < tInter->size(); ++i) {
        QList<QString> list;
        tInter->getRow(&list, i);
        if (list[0] == "true") {
            toCount.append(i);
            tInter->editStatus(i, QString("Not Tested"));
        }
    }
    return 0;
}

int Checker::finish()
{
    last = 0;
    tInter->writeTblIo();
    while (toCount.size() > 0) {
        toCount.removeAt(0);
    }
    QMetaObject::invokeMethod(tInter->getObj(), "finished");
    return 0;
}

int Checker::stop()
{
    tInter->editStatus(toCount[last], QString("Stoped"));
    last = 0;
    tInter->writeTblIo();
    checkLib->killProcess();
    while (toCount.size() > 0) {
        toCount.removeAt(0);
    }
    isWorking = false;
    return 0;
}

int Checker::pouse()
{
    return 0;
}

int Checker::checkStatus(QString id,QString str)
{
    QList<QString> list;
    tInter->getRow(&list, id.toInt());
    list[0] = str;
    tInter->setRow(list, id.toInt());
    tInter->writeTblIo();
    if (QString::compare(str, QString("true"), Qt::CaseInsensitive) == 0) {
        int res = toCount.indexOf(id.toInt(), 0);
        if (res != -1)
            return 0;
        toCount.append(id.toInt());
    } else {
        int res = toCount.indexOf(id.toInt(), 0);
        if ( res == -1)
            return 1;
        toCount.removeAt(res);
    }
    return 0;
}
