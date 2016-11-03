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
    int findValuesPing(QString str, QString *ret);
    int findValuesSpeed(QString str, QString *ret);
    QProcess *proc;
    int freq = 10;
    QString cmd;


public slots:
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void finishedTestPing(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    void processFinished(QString, int exitCode);
    void pingTested(QString ping, int exitCode);

};

#endif // CHECKLIB_H
