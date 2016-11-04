#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTableView>
#include <QQmlComponent>
#include <QDebug>
#include "tableinteraction.h"
#include "checker.h"
#include "iotable.h"
#include "export.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *root = engine.rootObjects().value(0);
    TableInteraction *inter = new TableInteraction(root);
    Checker *checker = new Checker(inter);
    IOTable *io = new IOTable(inter);

    Export *exprt = new Export;
    exprt->setSignals(root);
    exprt->setTableModel(inter);
//    QString path("test_doc.odt");
//    exprt->setFilePath(&path);
//    QList<QList<QString>> list;
//    QList<QString> row;
//    row.append("First Column");
//    row.append("Second Column");
//    list.append(row);

//    row.replace(0, "1 row");
//    row.replace(1, "1 row");
//    list.append(row);

//    exprt->setTable(&list);
//    exprt->write();

    return app.exec();
}
