#include "iotable.h"

IOTable::IOTable(TableModel *obj):QObject()
{
    table = obj;
    QObject::connect(table->getObj(), SIGNAL(saveSign()), this, SLOT(save()));
    QObject::connect(table->getObj(), SIGNAL(saveAsSign(QUrl)), this, SLOT(saveAs(QUrl)));
    QObject::connect(table->getObj(), SIGNAL(loadSign()), this, SLOT(load()));
    QObject::connect(table->getObj(), SIGNAL(loadAsSign(QUrl)), this, SLOT(loadAs(QUrl)));
}

int IOTable::setPath(QString path)
{
    filepath = path;
    return 0;
}

int IOTable::readTable(QList<QList<QString>> *list)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        printf("Could not open file\n");
        return 1;
    }
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString str = stream.readLine();
        QList<QString> tmpList;
        QStringList strList = str.split(QRegExp(","));
        for (int i = 0; i < strList.size(); ++i) {
            tmpList.append(strList[i]);
        }
        list->append(tmpList);
    }
    return 0;
}

int IOTable::writeTable(QList<QList<QString> > *list)
{
    QFile file(filepath);
    if (!file.open(QIODevice::WriteOnly)) {
        perror("Could not open file");
        return 1;
    }
    QString str;
    for (int i = 0; i < list->size(); ++i) {
        for (int x = 0; x < list->value(i).size(); ++x) {
            str.append(list->value(i).value(x));
            if (x != list->value(i).size() - 1) {
                str.append(QString(","));
            }
        }
        str.append("\n");
    }
    QTextStream stream(&file);
    stream<<str;
    return 0;
}

void IOTable::save()
{
    writeTable(table->getTable());
}

void IOTable::saveAs(QUrl path)
{
    QString str = path.path(QUrl::FullyDecoded);
    if (!str.contains(".csv")) {
        str.append(".csv");
    }
    setPath(str);
    save();
}

void IOTable::load()
{
    QList<QList<QString>> list;
    readTable(&list);
    table->setTable(list);
}

void IOTable::loadAs(QUrl path)
{
    QString str = path.path(QUrl::FullyDecoded);
    if (!str.contains(".csv")) {
        str.append(".csv");
    }
    setPath(str);
    load();
}
