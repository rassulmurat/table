#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "tablemodel.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    tableModel tModel(0);
    engine.rootContext()->setContextProperty("tableModel", &tModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *root = engine.rootObjects().value(0);
//    QTableView *table = root->findChild<QTableView*>("table");
//    tableModel tmodel(0);
//    table->setModel(&tmodel);
    return app.exec();
}
