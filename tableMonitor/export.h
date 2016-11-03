#ifndef EXPORT_H
#define EXPORT_H

#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QList>
#include <QUrl>

class Export
{
public:
    Export();
    Export(QString *path);
    void setFilePath(QString *path);
    void setTable(QList<QList<QString>> *list);

private:
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

public slots:
    void write();
    void write(QUrl path);
};

#endif // EXPORT_H
