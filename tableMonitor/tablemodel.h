#ifndef TABLEINTERACTION_H
#define TABLEINTERACTION_H

#include <QVariantList>
#include <QObject>
#include <QList>
#include <QFile>
#include <QDataStream>
#include <QDebug>

class TableModel : public QObject
{
    Q_OBJECT
public:
    /*
     * This Class stores table and interacts with gui.
     * Use this class to interact with a gui
     */
    TableModel(QObject *obj);

    //Appends the row to the table data in model and also adds it in gui.
    int appendRow(int id, QList<QString> list);

    //Edits row in data model and also emits changes to gui
    int editRow(QString check, int id, QString name, QString ip, QString status, QString latency);

    //Changes status (speed/ latency) in pair.
    int editStatus(int id, QString status, QString latency);

    /*
     * Sets table to table model
     * Mainly used in iotable class.
     */
    void setTable(QList<QList<QString>> list);

    /*
     * Sets table cell.
     * id is a row of the table.
     * role is a column of the table. Use enum ROLES.
     * value is a value to store in a cell.
     */
    int setRole(int id, int role, QString value);

    /*
     * Sets a table row.
     * Used in many internal functions.
     */
    int setRow(QList<QString> list, int pos);

    //Table size.
    int size();

    /*
     * Returns a pointer to a table.
     * Used in iotable
     */
    QList<QList<QString>> *getTable();

    //Gets a table row.
    int getRow(QList<QString> *list, int pos);

    //Return object of gui.
    QObject *getObj();

    //Returns column name by ROLES.
    QString getColumnName(int);

    //Table columns
    enum ROLES{
        CHECK = 0,
        NAME = 1,
        IP = 2,
        SPEED = 3,
        LATENCY = 4,
        ROLES_SIZE = 5,
    };

private:
    QObject *object;
    QList<QList<QString>> tableList;
    const QString filePath = "table.bin";

    //Populate table.
    int populate();
    const int rolesSize = 5;

public slots:
    //Below are listed slots to connect to gui.
    void appendSlot(QString name, QString ipaddr);
    void editSlot(QString id, QString name, QString ipaddr);
    void removeRow(QString id);
};

#endif // TABLEINTERACTION_H
