#ifndef CHECKLIB_H
#define CHECKLIB_H

#include "checklib_global.h"
#include <QList>
#include <QProcess>
#include <QByteArray>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>
#include <QStringList>
#include <QObject>

class CHECKLIBSHARED_EXPORT CheckLib: public QObject
{
    Q_OBJECT
public:
    CheckLib();
    int check(QList<QString> list);
    int killProcess();

private:
    QString exec(QString);
    int findValues(QString str, QString *ret);
    QProcess *proc;
    QList<QString> tableRow;

public slots:
    void finished(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    void processFinished(QList<QString> list, int exitCode);

};

#endif // CHECKLIB_H
