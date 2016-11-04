#ifndef EXPORT_H
#define EXPORT_H

#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextDocumentWriter>
#include <QTextCharFormat>
#include <QTextBlockFormat>
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
    //Set Table to export to file, QList[0] are headers
    void setTable(QList<QList<QString>> *list);

    //Set Table to Export to file sets headers automatically
    void setTable(QList<QString> headers, QList<QList<QString>> data);

    //Add QObbject to connect slots/signals to.
    void setSignals(QObject *obj);

    /*
     * Set Class for tableModel interaction.
     * Automatically gets tableColumns and table data.
     */
    void setTableModel(TableInteraction *table);

    /*
     * Function to clean table data stored in class.
     * Used at the end of the writing.
     */
    void cleanTableData();

protected:
    /*
     * Main structure of the file.
     * Change this if differenct type of structure needed.
     */
    void structFile();

    //Below are listed members of file structure
    void header();
    void createTable();
    void populateTable();
    void afterTable();

private:
    //Initialize pointer and documnt.
    void init();

    //Below is listed data stored in class.
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
