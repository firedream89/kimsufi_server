#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QWebFrame>
#include <QWebView>
#include <QClipboard>
#include <QTime>
#include <QDesktopServices>
#include <QDebug>
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <windows.h>
#include <QFile>
#include <QMessageBox>

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
    void LoadPage();

private:
    Ui::MainWindow *ui;
    bool demarrage;
    QTimer tmp,timer;
    QWebView *web;
};

#endif // MAINWINDOW_H
