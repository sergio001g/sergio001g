#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
    , firstNum(0)
    , secondNum(0)
    , waitingForOperand(true)
    , pendingOperation('\0')
{
    ui->setupUi(this);
    
    // Conectar señales de botones numéricos
    connect(ui->button0, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->button1, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->button2, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->button3, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->button4, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->button5, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->button6, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->button7, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->button8, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    connect(ui->button9, SIGNAL(clicked()), this, SLOT(digit_pressed()));
    
    // Inicializar la pantalla
    ui->display->setText("0");
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::digit_pressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonText = button->text();
    
    if (waitingForOperand) {
        ui->display->clear();
        waitingForOperand = false;
    }
    
    ui->display->setText(ui->display->text() + buttonText);
}

void Calculator::on_buttonDot_clicked()
{
    if (waitingForOperand) {
        ui->display->setText("0.");
        waitingForOperand = false;
    } else if (!ui->display->text().contains('.')) {
        ui->display->setText(ui->display->text() + ".");
    }
}

void Calculator::on_buttonPlus_clicked()
{
    calculate();
    pendingOperation = '+';
    waitingForOperand = true;
    firstNum = ui->display->text().toDouble();
}

void Calculator::on_buttonMinus_clicked()
{
    calculate();
    pendingOperation = '-';
    waitingForOperand = true;
    firstNum = ui->display->text().toDouble();
}

void Calculator::on_buttonMultiply_clicked()
{
    calculate();
    pendingOperation = '*';
    waitingForOperand = true;
    firstNum = ui->display->text().toDouble();
}

void Calculator::on_buttonDivide_clicked()
{
    calculate();
    pendingOperation = '/';
    waitingForOperand = true;
    firstNum = ui->display->text().toDouble();
}

void Calculator::on_buttonEquals_clicked()
{
    calculate();
    pendingOperation = '\0';
}

void Calculator::on_buttonClear_clicked()
{
    firstNum = 0;
    secondNum = 0;
    pendingOperation = '\0';
    waitingForOperand = true;
    ui->display->setText("0");
}

void Calculator::on_buttonClearEntry_clicked()
{
    ui->display->setText("0");
    waitingForOperand = true;
}

void Calculator::calculate()
{
    if (!waitingForOperand) {
        secondNum = ui->display->text().toDouble();
        
        double result = 0.0;
        bool error = false;
        
        switch (pendingOperation) {
        case '+':
            result = firstNum + secondNum;
            break;
        case '-':
            result = firstNum - secondNum;
            break;
        case '*':
            result = firstNum * secondNum;
            break;
        case '/':
            if (secondNum != 0) {
                result = firstNum / secondNum;
            } else {
                error = true;
            }
            break;
        default:
            return; // No hay operación pendiente
        }
        
        if (error) {
            ui->display->setText("Error");
        } else {
            ui->display->setText(QString::number(result, 'g', 15));
        }
        
        firstNum = result;
        waitingForOperand = true;
    }
}