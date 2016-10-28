#ifndef CHECKLIB_H
#define CHECKLIB_H

#include "checklib_global.h"
#include <QList>

class CHECKLIBSHARED_EXPORT CheckLib
{

public:
    CheckLib();
    int check(QList<QString> *list);
};

#endif // CHECKLIB_H
