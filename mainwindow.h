#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Dataloader.h"
#include "calculator.h"
#include "table.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_button_clicked(CsvParser& parser);

    void on_ageCheckBox_stateChanged(int arg1);

    void on_calculateButton_clicked();

private:
    DataLoader _dataLoader;
    Calculator _calculator;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
