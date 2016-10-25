#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#endif // TABLEMODEL_H
#include <QAbstractTableModel>
#include <QFont>
#include <QBrush>

class tableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    tableModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant data (const QModelIndex & index, int role) const;
};
