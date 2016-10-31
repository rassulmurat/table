#ifndef CHECKLIB_H
#define CHECKLIB_H

#include "checklib_global.h"
#include <QList>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <QByteArray>
#include <QDebug>

class CHECKLIBSHARED_EXPORT CheckLib
{

public:
    CheckLib();
    int check(QList<QString> *list);

private:
    QString exec(QString);
};

#endif // CHECKLIB_H
