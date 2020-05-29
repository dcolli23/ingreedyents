#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_returnPressed()
{
    // This will be for submitting the UPC through pressing enter on the entry line.
    ui->pushButton->click();
}

void MainWindow::on_pushButton_clicked()
{
    // This is where we have the meat and potatoes of submitting the UPC GET request.
    QString UPC = ui->lineEdit->text();
    QString disp = "Button has been clicked with \"" + UPC + "\"!\n";
    ui->textBrowser->append(disp);


}
