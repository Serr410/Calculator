#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPixmap"
#include "cmath"
#include "polish.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(600, 600);
    ui->label->setGeometry(width() - width()*18.65/20, width() - width()*18/20, width()*17/20, height()*17/20);
    QPushButton* button = new QPushButton(this);
    connect(button, SIGNAL(clicked()), this, SLOT(on_pushButton_button_clicked()));
    button->setGeometry(width()*0.7, height()*0.017, width()*0.27, height()*0.06); //Размер потом процентным сделать надо
    button->setText("Something idk");
    ui -> lineEdit_XM -> setText("3.14");
    ui -> lineEdit_XMI -> setText("-3.14");
    ui -> lineEdit_S -> setText("3.14");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_button_clicked() {

    QPixmap PM(ui->label->width(), ui->label->height());
    QPainter painter;
    painter.begin(&PM);
    PM.fill(Qt::white);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    QString informF = ui->lineEdit_F->text();
    double conclusion;

    if (ui->lineEdit_XMI->text().isEmpty() == true){
        ui -> lineEdit_XMI -> setText("-3.14");
    }
    if (ui->lineEdit_XM->text().isEmpty() == true){
        ui -> lineEdit_XM -> setText("3.14");
    }
    if (ui->lineEdit_S->text().isEmpty() == true){
        ui -> lineEdit_S -> setText(QString::number((((ui->lineEdit_XM->text()).toDouble()) - ((ui->lineEdit_XMI->text()).toDouble()))/2));
    }
    double xmin = (ui->lineEdit_XMI->text()).toDouble(), xmax = (ui->lineEdit_XM->text()).toDouble();

    informF.replace("x","(" + QString::number(xmax) + ")");
    calc(informF.toStdString(), conclusion);
    double ymin = (-1) * (ui->lineEdit_S->text()).toDouble(), ymax = (ui->lineEdit_S->text()).toDouble(); // Ошибка тут, надо найти правильную формулу для Y-ков

    int xgmin = 0, xgmax = PM.width();
    int ygmin = 0, ygmax = PM.height();

    double x, y;
    int xg, yg;

    double kx = (xgmax - xgmin)/(xmax - xmin), ky = (ygmin - ygmax)/(ymax - ymin);
    double xo = xgmin - kx * xmin, yo = ygmin - ky * ymax;

    painter.drawLine(0, yo, PM.width(), yo);
    painter.drawLine(xo, 0, xo, PM.height());
    QPainterPath path;
    double stepx = (xmax - xmin)/(xgmax - xgmin);
    x = xmin;

    informF = ui->lineEdit_F->text();
    double answer;
    QString informerF = informF;
    informerF.replace("x","(" + QString::number(x) + ")");
    calc(informerF.toStdString(), answer);
    pen.setColor(Qt::red);
    path.moveTo(xo + kx * x, yo + ky * answer);
    painter.setPen(pen);
    informerF = informF;
    int condition;
    while (x <= xmax) {
        informerF.replace("x","(" + QString::number(x) + ")"); // Надо сделать что то с асимптотами
        condition = calc(informerF.toStdString(), answer);
      //printf("%d ", condition);
      //printf("%f ", x);         //это индикаторы, активируешь когда надо
      //printf("%f | ", answer);
        y = answer;
        xg = (xo + kx * x);
        yg = (yo + ky * y);
        path.lineTo(xg, yg);
        informerF = informF;
        x += stepx;
        while ((yg > ygmax || yg < ygmin) && x <= xmax) {
            informerF.replace("x","(" + QString::number(x) + ")");
            calc(informerF.toStdString(), answer);
            y = answer;
            xg = (xo + kx * x);
            yg = (yo + ky * y);
            path.moveTo(xg, yg);
            informerF = informF;
            x += stepx;
        }

    }

    painter.drawPath(path);
    ui->label->setPixmap(PM);
}
