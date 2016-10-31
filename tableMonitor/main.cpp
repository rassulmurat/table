#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTableView>
#include <QQmlComponent>
#include <QDebug>
#include "tableinteraction.h"
#include "checker.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *root = engine.rootObjects().value(0);
    TableInteraction *inter = new TableInteraction(root);
    QObject::connect(root, SIGNAL(appendSign(QString, QString)), inter, SLOT(appendSlot(QString, QString)));
    QObject::connect(root, SIGNAL(editSign(QString, QString, QString)), inter, SLOT(editSlot(QString, QString, QString)));

    Checker *checker = new Checker(inter);
    QObject::connect(root, SIGNAL(startSign()), checker, SLOT(start()));
    QObject::connect(root, SIGNAL(stopSign()), checker, SLOT(stop()));
    QObject::connect(root, SIGNAL(pouseSign()), checker, SLOT(pouse()));
    QObject::connect(root, SIGNAL(checkSign(QString, QString)), checker, SLOT(checkStatus(QString,QString)));

    return app.exec();
}
