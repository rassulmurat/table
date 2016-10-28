#include "checklib.h"


CheckLib::CheckLib()
{
}

int CheckLib::check(QList<QString> *list)
{
    list->insert( 3, "OK");
    return 0;
}
