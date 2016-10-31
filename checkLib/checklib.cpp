#include "checklib.h"


CheckLib::CheckLib()
{
}

int CheckLib::check(QList<QString> *list)
{
    QString tmp = list->value(2);
    QString command = "iperf -c ";
    command.append(tmp);
    QString str = exec(command);
    qDebug()<<str;
    return 0;
}


QString CheckLib::exec(QString cmd)
{
    char buffer[128];
    QString result = "";
    QByteArray barr = cmd.toLatin1();
    const char *command = barr.data();
    FILE* pipe = popen(command, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result.append(buffer);
                qDebug()<<buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
