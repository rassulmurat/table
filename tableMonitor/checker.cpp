#include "checker.h"

Checker::Checker(TableInteraction *inter):QObject()
{
    tInter = inter;
    checkLib = new CheckLib();
    QObject::connect(checkLib, SIGNAL(processFinished(QList<QString>)), this, SLOT(processFinished(QList<QString>)));
}

int Checker::checkOne()
{
    if (last == toCount.size()) {
        stop();
        return 0;
    }
    QList<QString> list;
    tInter->getRow(&list, toCount[last]);
    tInter->editRow(list[0], toCount[last], list[1], list[2], QString("Testing"));
    checkLib->check(list);

    return 0;
}

void Checker::processFinished(QList<QString> list)
{
    tInter->editRow(list[0], toCount[last], list[1], list[2], list[3]);
    last++;
    //Progression bar
    QMetaObject::invokeMethod(tInter->getObj(), "checkedAdd", Q_ARG(QVariant, (double)last/toCount.size()));
    checkOne();
}

int Checker::start()
{
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
        }
    }
    return 0;
}

int Checker::stop()
{
    last = 0;
    tInter->writeTblIo();
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
