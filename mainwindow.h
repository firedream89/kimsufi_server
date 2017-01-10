#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Demarrage();


private slots:
    void arreter();
    void Tmp(bool f = 0);

private:
    Ui::MainWindow *ui;
    bool demarrage;
    QTimer tmp;
};

#endif // MAINWINDOW_H
