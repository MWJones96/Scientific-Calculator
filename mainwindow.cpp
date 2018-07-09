#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RPN.h"
#include "RPNEvaluator.h"
#include <string>
#include <iostream>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size().width(), this->size().height());

    connect(ui->button_0, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_1, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_2, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_3, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_4, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_5, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_6, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_7, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_8, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_9, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_add, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_sub, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_mult, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_divide, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_exp, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_lb, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_rb, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_e, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_pi, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_phi, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_sin, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_cos, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_tan, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_asin, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_acos, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_atan, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_sinh, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_cosh, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_tanh, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_asinh, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_acosh, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_atanh, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_ln, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_log, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_max, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_min, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_sqrt, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_cbrt, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_abs, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_floor, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_ceil, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_ans, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_dot, SIGNAL(released()), this, SLOT(processButton()));
    connect(ui->button_comma, SIGNAL(released()), this, SLOT(processButton()));

    connect(ui->button_c, SIGNAL(released()), this, SLOT(clear()));

    connect(ui->button_equals, SIGNAL(released()), this, SLOT(calculateExpression()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processButton()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if(button->objectName() == "button_pi")
    {
        ui->equationBox->setText(ui->equationBox->text() + "pi");
        return;
    }
    else if(button->objectName() == "button_phi")
    {
        ui->equationBox->setText(ui->equationBox->text() + "phi");
        return;
    }
    else if(button->objectName() == "button_asin")
    {
        ui->equationBox->setText(ui->equationBox->text() + "asin");
        return;
    }
    else if(button->objectName() == "button_acos")
    {
        ui->equationBox->setText(ui->equationBox->text() + "acos");
        return;
    }
    else if(button->objectName() == "button_atan")
    {
        ui->equationBox->setText(ui->equationBox->text() + "atan");
        return;
    }
    else if(button->objectName() == "button_asinh")
    {
        ui->equationBox->setText(ui->equationBox->text() + "asinh");
        return;
    }
    else if(button->objectName() == "button_acosh")
    {
        ui->equationBox->setText(ui->equationBox->text() + "acosh");
        return;
    }
    else if(button->objectName() == "button_atanh")
    {
        ui->equationBox->setText(ui->equationBox->text() + "atanh");
        return;
    }
    else if(button->objectName() == "button_sqrt")
    {
        ui->equationBox->setText(ui->equationBox->text() + "sqrt");
        return;
    }
    else if(button->objectName() == "button_cbrt")
    {
        ui->equationBox->setText(ui->equationBox->text() + "cbrt");
        return;
    }
    else
        ui->equationBox->setText(ui->equationBox->text() + button->text());
}

void MainWindow::calculateExpression()
{
    RPN rpn;
    RPNEvaluator rpnE;
    std::vector<std::string> tokens = rpn.parseString(ui->equationBox->text().toUtf8().constData());
    long double val = rpnE.evaluateRPN(tokens);
    ui->equationBox->setText(QString::fromStdString(std::to_string(val)));
}

void MainWindow::clear()
{
    ui->equationBox->setText("");
}
