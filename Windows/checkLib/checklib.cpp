#include "checklib.h"


CheckLib::CheckLib()
{
}

int CheckLib::check(QList<QString> list)
{
    QString command = list.value(2);
    QString str = exec(command);
    tableRow = list;
    return 0;
}

int CheckLib::findValues(QString str, QString *ret)
{
    QTextStream txtStrm(&str);
    QString txt;
    int line = 0;
    while(!txtStrm.atEnd()) {
        if(line == 15) {
            txt = txtStrm.readLine();
            break;
        }
        line++;
    }
    if (line != 15)
        return 1;
    QStringList list = txt.split(QRegExp(" "));
    *ret = list[9];
    ret->append(QString(" "));
    ret->append(list[10]);
    return 0;
}


QString CheckLib::exec(QString cmd)
{
    QString programm = QString("C:\\iperf-3.1.3-win32\\iperf3.exe");
    QStringList arguments;
    arguments<<"-c";
    arguments<<cmd;
    proc = new QProcess();

    QObject::connect(proc, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished(int,QProcess::ExitStatus)));

    proc->start(programm, arguments);

    return QString("");
}

void CheckLib::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
//    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    QString str;

    QByteArray buf = proc->readAllStandardOutput();
    QString tmp(buf);

    if (findValues(tmp, &str) == 1) {
        tableRow.replace(3, "fail");
    } else {
        tableRow.replace(3, str);
    }

    emit processFinished(tableRow, exitCode);
}

int CheckLib::killProcess()
{
    proc->kill();
    return 0;
}
