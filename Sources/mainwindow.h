#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QWebFrame>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();  
    void InitListServer();


private slots:
    void arreter();
    void Tmp();
    void About();
    void Demarrage();

private:
    Ui::MainWindow *ui;
    bool demarrage;
    QTimer tmp,timer;
};

#endif // MAINWINDOW_H
