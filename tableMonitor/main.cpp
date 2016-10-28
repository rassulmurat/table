#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTableView>
#include <QQmlComponent>
#include <QDebug>
#include "tableinteraction.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlComponent component(&engine, QUrl("qrc:/main.qml"));
    QObject *obj = component.create();
    QObject *root = engine.rootObjects().value(0);
    QObject *mdlObj = root->findChild<QObject*>("model1");
    TableInteraction *inter = new TableInteraction(obj);
    QObject::connect(mdlObj, SIGNAL(appendSign(QString, QString)), inter, SLOT(appendSlot(QString,QString)));
    return app.exec();
}
