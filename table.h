#ifndef TABLE_H
#define TABLE_H

#include <QDialog>
#include <vector>

#include <QTableWidgetItem>
#include <QTableWidget>
#include <QHBoxLayout>
#include "Dataloader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Table; }
QT_END_NAMESPACE

class Table : public QDialog {
    Q_OBJECT

public:
    Table(QWidget *parent, CsvParser& parser);
    void setTable();
    ~Table();

private slots:
    void on_SaveButton_clicked();

    void on_cancelButton_clicked();

private:
    CsvParser& _parser;
    Ui::Table* ui;
};

#endif // TABLE_H
