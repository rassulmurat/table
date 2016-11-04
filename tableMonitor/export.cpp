#include "export.h"

Export::Export(): QObject(0)
{
    init();
}

Export::Export(QString *path): QObject(0)
{
    setFilePath(path);
//    init();
}

void Export::init()
{
    doc = new QTextDocument();
    cursor = new QTextCursor(doc);
    exludedColumns.append(TableModel::CHECK);
}

void Export::setFilePath(QString *path)
{
    filePath = *(QString *)path;
}

void Export::setTable(QList<QList<QString> > *list)
{
    tableData = *(QList<QList<QString> >*)list;
}

void Export::setSignals(QObject *obj)
{
    object = obj;
    QObject::connect(object, SIGNAL(exportToOdt(QUrl)), this, SLOT(write(QUrl)));
}

void Export::setTableModel(TableModel *table)
{
    tableModel = table;
}

void Export::structFile()
{
    header();
    cursor->insertText("\n");
    createTable();
    populateTable();
    afterTable();
}

void Export::header()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString str = dateTime.toString("dd:MM:yyyy, HH:mm");
    QTextBlockFormat chFormat;
    chFormat.setAlignment(Qt::AlignCenter);
    cursor->setBlockFormat(chFormat);
    cursor->insertText(QString("Протокол Тестирован %1").arg(str));
}

void Export::createTable()
{
    QTextTableFormat tableFormat;
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    cursor->insertTable(tableData.size(), tableData[0].size());
    for (int i = 0; i < tableData[0].size(); ++i) {
        cursor->insertText(tableData[0].value(i));
        cursor->movePosition(QTextCursor::NextCell);
    }
}

void Export::populateTable()
{
    for (int row = 1; row < tableData.size(); ++row) {
        for (int i = 0; i < tableData[row].size(); ++i) {
            cursor->insertText(tableData[row].value(i));
            cursor->movePosition(QTextCursor::NextCell);
        }
    }
}

void Export::afterTable()
{
    cursor->movePosition(QTextCursor::End);
    cursor->insertText("\n\n");
    cursor->insertText("Тестировал:_________________");
    cursor->insertText("         ");
    cursor->insertText("Подпись:_______________");
}

void Export::write()
{
    structFile();
    QTextDocumentWriter writer(filePath);
    writer.write(doc);
    doc->clear();
    cleanTableData();
}

void Export::cleanTableData()
{
    while (tableData.size()>0) {
        tableData.removeAt(0);
    }
}

void Export::write(QUrl path)
{
    init();
    QString str = path.toLocalFile();
    if (!str.contains(".odt")) {
        str.append(".odt");
    }
    setFilePath(&str);
    QList<QString> headers;
    for (int col = 0; col < TableModel::ROLES_SIZE; ++col) {
       if(!exludedColumns.contains(col)) {
           headers.append(tableModel->getColumnName(col));
       }
    }
    tableData.append(headers);
    for (int row = 0; row < tableModel->size(); ++row) {
        QList<QString> list;
        tableModel->getRow(&list, row);
        if (QString::compare(list[tableModel->CHECK], QString("true"), Qt::CaseInsensitive) == 0) {
            for (int col = 0; col < list.size(); ++col) {
                if (exludedColumns.contains(col)) {
                    list.removeAt(col);
                }
            }
            tableData.append(list);
        }
    }
    write();
}
