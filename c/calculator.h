#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    // Slots para botones numéricos
    void digit_pressed();
    
    // Slots para botones de operaciones
    void on_buttonPlus_clicked();
    void on_buttonMinus_clicked();
    void on_buttonMultiply_clicked();
    void on_buttonDivide_clicked();
    
    // Slots para botones de control
    void on_buttonEquals_clicked();
    void on_buttonClear_clicked();
    void on_buttonClearEntry_clicked();
    void on_buttonDot_clicked();

private:
    Ui::Calculator *ui;
    
    double firstNum;
    double secondNum;
    QString displayVal;
    bool waitingForOperand;
    char pendingOperation;
    
    void calculate();
};
#endif // CALCULATOR_H