#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton button;
    void button_clicked();

private slots:

    void on_pushButton_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
