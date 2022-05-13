#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Dataloader.h"
#include "table.h"
#include "calculator.h"

#include <QFileDialog>
#include <QString>

string calendar[12] = {"Январе", "Феврале", "Марте", "Апреле",
                       "Мае", "Июне", "Июле", "Августе", "Сентябре",
                       "Октябре", "Ноябре", "Декабре"};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->transport , &QPushButton::clicked, [&]() { on_button_clicked(_dataLoader.getTransportParser()); });
    connect(ui->caffe_and_cinema , &QPushButton::clicked, [&]() { on_button_clicked(_dataLoader.getWeekendsParser()); });
    connect(ui->costs , &QPushButton::clicked, [&]() { on_button_clicked(_dataLoader.getCostsParser()); });
    connect(ui->institute , &QPushButton::clicked, [&]() { on_button_clicked(_dataLoader.getInstituteParser()); });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->clear();
    ui->editWidget->setEnabled(false);
    ui->dataWidget->setEnabled(false);
    ui->calculateButton->setEnabled(false);
    QString str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "");
    ui->textBrowser->setText(str);
    try {
        string path = str.toStdString();
        _dataLoader = DataLoader(path);
        ui->editWidget->setEnabled(true);
        ui->dataWidget->setEnabled(true);
        ui->calculateButton->setEnabled(true);
        ui->ageWidget->setEnabled(false);
    }
    catch (out_of_range& text) {
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->setFontPointSize(14);
        ui->textEdit->setText(QString::fromStdString(text.what()));
    }
}


void MainWindow::on_button_clicked(CsvParser& parser)
{
    Table _fileTable = Table(nullptr, parser);
    _fileTable.setWindowTitle("Editor");
    _fileTable.exec();
}

void MainWindow::on_ageCheckBox_stateChanged(int arg1)
{
    ui->ageWidget->setEnabled(arg1);
    ui->ageBox->setEnabled(arg1);
}


void MainWindow::on_calculateButton_clicked()
{
    string name = ui->nameEdit->text().toStdString();
    string city = ui->cityEdit->text().toStdString();
    string address = ui->addessEdit->text().toStdString();
    string institute = ui->instituteEdit->text().toStdString();
    string cafe = ui->cafeEdit->text().toStdString();
    string cinema = ui->cinemaEdit->text().toStdString();
    int month = ui->monthBox->value();
    int age = ui->ageBox->isEnabled() ? ui->ageBox->value() : 0;
    try {
        ui->textEdit->setTextColor(Qt::black);
        ui->textEdit->setFontPointSize(14);
        ui->textEdit->setText(QString::fromStdString("Студент " + name + " тратит "
                                                     + to_string(_calculator.getCosts(_dataLoader, month, city, address,
                                                                                     age, institute, cafe, cinema))
                                                     + " рублей в " + calendar[month - 1]));
    }
    catch (out_of_range) {
        ui->textEdit->setTextColor(Qt::red);
        ui->textEdit->setFontPointSize(15);
        ui->textEdit->setText(QString::fromStdString("Not found"));
    }

}
