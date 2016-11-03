#include "export.h"

Export::Export()
{
    doc = new QTextDocument();
    cursor = new QTextCursor();
}

Export::Export(QString *path)
{
    setFilePath(path);
    Export exprt;
}

void Export::setFilePath(QString *path)
{
    filePath = *(QString *)path;
}

void Export::setTable(QList<QList<QString> > *list)
{
    tableData = *(QList<QList<QString> >*)list;
}
