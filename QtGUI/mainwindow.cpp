#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IngredientRequest.h"
#include "Nutrient.h"
#include "Measurement.h"

#include <iostream>
#include <string>

//const std::string API_KEY = "don't commit this!";
const std::string API_KEY = "YKsot922BiMbmNv7D4G5AIakMatDJSTXF8xVEgt3";

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
    QString Q_nut_name;
    QString Q_nut_amount;
    QString Q_nut_unit;
    Measurement nut_mes;

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

    // Print out all of the nutrient information.
    for (auto const& [nut_name, nut] : ing_result->nutrients) {
        // Get all of the information to print.
        nut_mes = nut->get_serving();
        Q_nut_name = QString::fromStdString(nut_name);
        Q_nut_amount = QString::fromStdString(std::to_string(nut_mes.get_amount()));
        Q_nut_unit = QString::fromStdString(nut_mes.get_unit());
        disp = "\tNutrient: " + Q_nut_name + ' ' + Q_nut_amount + ' ' + Q_nut_unit;
        ui->textBrowser->append(disp);
    }
}
