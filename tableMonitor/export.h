#ifndef EXPORT_H
#define EXPORT_H

#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextDocumentWriter>
#include <QTextCharFormat>
#include <QList>
#include <QUrl>
#include <QDateTime>
#include "tableinteraction.h"

class Export: public QObject
{
    Q_OBJECT
public:
    Export();
    Export(QString *path);
    void setFilePath(QString *path);
    void setTable(QList<QList<QString>> *list);
    void setTable(QList<QString> headers, QList<QList<QString>> data);
    void setSignals(QObject *obj);
    void setTableModel(TableInteraction *table);

private:
    void init();
    void structFile();
    void header();
    void createTable();
    void populateTable();
    void insertRow(QList<QString>);
    void afterTable();
    QTextCursor *cursor;
    QTextDocument *doc;
    QList<QList<QString>> tableData;
    QString filePath;
    QObject *object;
    TableInteraction *tableModel;
    QList<int> exludedColumns;

public slots:
    void write();
    void write(QUrl path);
};

#endif // EXPORT_H
