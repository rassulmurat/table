#include "checklib.h"


CheckLib::CheckLib()
{
}

int CheckLib::check(QList<QString> list)
{
    QString command = list.value(2);
    QString str = exec(command);
    return 0;
}

int CheckLib::findValuesPing(QString str, QString *ret)
{
    QTextStream txtStrm(&str);
    QString txt;
    int tmp = 10/freq;
    int lineNum = 10 + tmp;
    int line = 0;
    while(!txtStrm.atEnd()) {
        if(line == lineNum) {
            txt = txtStrm.readLine();
            break;
        }
        txtStrm.readLine();
        line++;
    }
    if (line != lineNum) {
        *ret = "Fail";
        return 1;
    }
    QStringList list = txt.split(QRegExp(" "));

    QString latency = list[14];
    latency.append(QString(" "));
    latency.append(list[15]);
    *ret = latency;
    return 0;
}

int CheckLib::findValuesSpeed(QString str, QString *ret)
{
    QTextStream txtStrm(&str);
    QString txt;
    int tmp = 10/freq;
    int lineNum = 5 + tmp;
    int line = 0;
    while(!txtStrm.atEnd()) {
        if(line == lineNum) {
            txt = txtStrm.readLine();
            break;
        }
        txtStrm.readLine();
        line++;
    }

    if (line != lineNum) {
        *ret = "Fail";
        return 1;
    }
    QStringList list = txt.split(QRegExp(" "));
    *ret = list[10];
    ret->append(QString(" "));
    ret->append(list[11]);
    return 0;
}

void CheckLib::finishedTestPing(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString programm = QString("iperf");
    QStringList arguments;
    arguments<<"-c";
    arguments<<cmd;
    QString str;
    str.sprintf("-i %d", freq);
    arguments<<str;

    QByteArray buf = proc->readAllStandardOutput();
    QString tmp(buf);

    proc = new QProcess();

    QObject::connect(proc, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));

    proc->start(programm, arguments);

    Q_UNUSED(exitStatus);
    Q_UNUSED(exitCode);

    findValuesPing(tmp, &str);
    emit pingTested(str, exitCode);
}



QString CheckLib::exec(QString cmdVal)
{
    QString programm = QString("iperf");
    cmd = cmdVal;
    QStringList arguments;
    arguments<<"-c";
    arguments<<cmd;
    arguments<<"-u";
    QString str;
    str.sprintf("-i %d", freq);
    arguments<<str;
    proc = new QProcess();

    QObject::connect(proc, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finishedTestPing(int,QProcess::ExitStatus)));

    proc->start(programm, arguments);

    return QString("");
}

void CheckLib::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitStatus);
    QString str;

    QByteArray buf = proc->readAllStandardOutput();
    QString tmp(buf);
    findValuesSpeed(tmp, &str);

    emit processFinished(str, exitCode);
}

int CheckLib::killProcess()
{
    proc->kill();
    return 0;
}
