#include "calculator.h"
#include "./ui_calculator.h"

double calcVal = 0.0;
bool divFlag = false;
bool multFlag = false;
bool addFlag = false;
bool subFlag = false;
bool equalFlag = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];

    for(int i = 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName); // get the buttons by name and add to array
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumbPressed())); // call num_pressed() when the button is released
    }
    connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonSub, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonMulti, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonDiv, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonEqual, SIGNAL(released()), this, SLOT(EqualButtonPressed()));

    connect(ui->ButtonDot, SIGNAL(released()), this, SLOT(DotButtonPressed()));

    connect(ui->ButtonAC, SIGNAL(released()), this, SLOT(AcButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumbPressed(){
    if(equalFlag){
        ui->Display->setText("");
        equalFlag = false;
    }
    QPushButton *button = (QPushButton *)sender(); //returns a pointer to the button pressed
    QString butVal = button->text(); // get number on button
    QString displayVal = ui->Display->text(); // get the value in the display
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(butVal);
    } else{
        QString newVal = displayVal + butVal; // concatenate the number to the right
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16)); // Set value in display and allow up to 16 digits before using exponents
    }
}

void Calculator::DotButtonPressed(){
    QPushButton *button = (QPushButton *)sender(); //returns a pointer to the button pressed
    QString butVal = button->text(); // get number on button
    QString displayVal = ui->Display->text(); // get the value in the display
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(butVal);
    } else{
        QString newVal = displayVal + butVal; // concatenate the number to the right
        ui->Display->setText(newVal); // Set value in display and allow up to 16 digits before using exponents
    }
}

void Calculator::MathButtonPressed(){
    divFlag = false;
    multFlag = false;
    addFlag = false;
    subFlag = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text(); // get math symbol on the button

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divFlag = true;
        ui->Display->setText("/");
    } else if(QString::compare(butVal, "x", Qt::CaseInsensitive) == 0){
        multFlag = true;
        ui->Display->setText("x");
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addFlag = true;
        ui->Display->setText("+");
    } else {
        subFlag = true;
        ui->Display->setText("-");
    }
    //ui->Display->setText("");
}

void Calculator::EqualButtonPressed(){
    equalFlag = true;
    double solution = 0.0;

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addFlag || subFlag || multFlag || divFlag ){
        if(addFlag){
            solution = calcVal + dblDisplayVal;
        } else if(subFlag){
            solution = calcVal - dblDisplayVal;
        } else if(multFlag){
            solution = calcVal * dblDisplayVal;
        } else {
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::AcButtonPressed(){
    ui->Display->setText("0.0");
    addFlag = false;
    subFlag = false;
    multFlag = false;
    divFlag = false;
}
