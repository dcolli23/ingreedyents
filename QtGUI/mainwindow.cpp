#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IngredientRequest.h"

#include <iostream>
#include <string>

const std::string API_KEY = "don't commit this!";

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
//    ui->pushButton->click();
}

void MainWindow::on_pushButton_clicked()
{
    // This is where we have the meat and potatoes of submitting the UPC GET request.
    QString UPC = ui->lineEdit->text();
    QString disp = "Button has been clicked with \"" + UPC + "\"!\n";
    ui->textBrowser->append(disp);

    // Make the ingredient request via the given URL.
    string UPC_std_string = UPC.toStdString();
    cout << "UPC string: " << UPC_std_string << endl;
    IngredientRequest* user_request = new IngredientRequest(UPC_std_string, API_KEY);
    user_request->form_FDC_ID_URL();
    cout << "FDC ID URL: " << user_request->get_FDC_ID_URL() << endl;
    cout << "Other URL: " << user_request->get_detailed_nutrition_URL() << endl;
    Ingredient* ing_result = user_request->make_request();

    QString ing_name = QString::fromStdString(ing_result->get_ingredient_name());
    disp = "\tIngredient Name: " + ing_name + '\n';
    ui->textBrowser->append(disp);
}
