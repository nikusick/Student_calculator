#include "table.h"
#include "ui_table.h"
#include <QObject>
#include <QPushButton>
#include <QMessageBox>

Table::Table(QWidget *parent, CsvParser& parser) : QDialog(parent), ui(new Ui::Table), _parser(parser) {
        ui->setupUi(this);
        setTable();
}

Table::~Table() {
    delete ui;
}

void Table::setTable() {
    vector<vector<string>> data = _parser.getData();
    ui->table->setColumnCount(data[0].size());
    ui->table->setRowCount(data.size() - 1);
    QStringList name_table;
    for (int i = 0; i < data[0].size(); ++i) {
        name_table << QString::fromStdString(data[0][i]);
    }
    ui->table->setHorizontalHeaderLabels(name_table);
    for (int i = 1; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            ui->table->setItem(i - 1, j, new QTableWidgetItem(QString::fromStdString(data[i][j])));
        }
    }
}

void Table::on_SaveButton_clicked()
{
    try {
        vector<string> row;
        vector<vector<string>> newData;
        for (int i = 0; i < ui->table->columnCount(); ++i) {
            row.push_back(ui->table->horizontalHeaderItem(i)->text().toStdString());
        }
        newData.push_back(row);
        for (int i = 0; i < ui->table->rowCount(); ++i) {
            row.clear();
            for (int j = 0; j < ui->table->columnCount(); ++j) {
                if (ui->table->item(i, j)->text().toStdString() == "") {
                    throw out_of_range("Cells can not be empty!");
                }
                row.push_back(ui->table->item(i, j)->text().toStdString());
            }
            newData.push_back(row);
        }
        if (newData.empty()) {
            throw out_of_range("File can not be empty!");
        }
        for (int i = 1; i < newData.size(); ++i) {
            if (newData[i].size() != newData[i - 1].size()) {
                throw out_of_range("Number of columns is not constant!" + to_string(i));
            }
        }
        _parser.setData(newData);
        close();
    }
    catch (out_of_range& text) {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.setInformativeText(text.what());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}


void Table::on_cancelButton_clicked()
{
    close();
}

