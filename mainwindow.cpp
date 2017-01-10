#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebView>
#include <QClipboard>
#include <QTime>
#include <QDebug>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Dispo Serveur Kimsufi");
    demarrage = false;
    Beep(700,1000);

    QString fen("Pushbullet");
    HWND hWnds = FindWindow(NULL,fen.toStdWString().c_str());
    if(hWnds != NULL)
    {
        SetForegroundWindow(hWnds);
        QClipboard *pp = QApplication::clipboard();
        pp->clear();
        QEventLoop l;
        QTimer t;
        connect(&t,SIGNAL(timeout()),&l,SLOT(quit()));
        t.start(2000);
        l.exec();
        QString test("Dispo Serveur Kimsufi Activé\nhttps://www.kimsufi.com/fr/commande/kimsufi.xml?reference=" + ui->eServeur->text() + "&quantity=1");
        pp->setText(test);
        qDebug() << pp->text();
        keybd_event(VK_LCONTROL,0,0,0);
        keybd_event('V',0,0,0);
        keybd_event(VK_LCONTROL,0,KEYEVENTF_KEYUP,0);
        keybd_event(VK_RETURN,0,0,0);
        keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
    }

    connect(ui->bArreter,SIGNAL(clicked(bool)),this,SLOT(arreter()));
    connect(&tmp,SIGNAL(timeout()),&tmp,SLOT(stop()));
    connect(&tmp,SIGNAL(timeout()),this,SLOT(Tmp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Demarrage()
{
    QWebView *web = new QWebView;
    QEventLoop l;
    QTime t;
    QTimer timer,timer2;
    QStringList v,server;
    QString final,var;
    QClipboard *cp = QApplication::clipboard();
    bool europe(false),dispo(false);

    connect(web,SIGNAL(loadFinished(bool)),&l,SLOT(quit()));
    connect(&timer,SIGNAL(timeout()),&l,SLOT(quit()));
    connect(&timer,SIGNAL(timeout()),&timer,SLOT(stop()));
    connect(&timer2,SIGNAL(timeout()),&l,SLOT(quit()));

    ui->listDispo->setAlternatingRowColors(true);
    while(demarrage)
    {
        web->load(QUrl("https://www.ovh.com/engine/api/dedicated/server/availabilities?country=fr?&hardware=" + ui->eServeur->text()));
        l.exec();
        cp->clear();
        web->page()->triggerAction(QWebPage::SelectAll);
        web->page()->triggerAction(QWebPage::Copy);
        var.clear();
        var = cp->text();
        server.clear();
        server = var.split("{");
        europe = false;
        for(int cpt = 0;cpt<server.count();cpt++)
        {
            if(europe)
            {
                v.clear();
                v = server.at(cpt).split("\"");
                dispo = false;
                final.clear();
                for(int cpt2 = 0;cpt2<v.count();cpt2++)
                {
                    if(v.at(cpt2).contains("datacenter") && !dispo)
                    {
                        final += QTime::currentTime().toString("hh:mm:ss ") + v.at(cpt2+2) + " ";
                        dispo = true;
                    }
                    else if(v.at(cpt2).contains("availability") && dispo)
                        final += v.at(cpt2+2);
                }
                if(final.split(" ").last() == "")
                    final += v.at(3);

                ui->listDispo->insertItem(0,final);
                if(final.split(" ").last() != "unavailable")
                {
                    demarrage = false;
                    timer.start(30000);

                    while(timer.isActive())
                    {
                        //Envoie info via pushbullet
                        QString fen("Pushbullet");
                        HWND hWnds = FindWindow(NULL,fen.toStdWString().c_str());
                        if(hWnds != NULL)
                        {
                            SetForegroundWindow(hWnds);
                            QClipboard *pp = QApplication::clipboard();
                            pp->clear();
                            QEventLoop l;
                            QTimer t;
                            connect(&t,SIGNAL(timeout()),&l,SLOT(quit()));
                            t.start(2000);
                            l.exec();
                            pp->setText(ui->listDispo->item(0)->text() + "\nhttps://www.kimsufi.com/fr/commande/kimsufi.xml?reference=" + ui->eServeur->text() + "&quantity=1");
                            qDebug() << pp->text();
                            keybd_event(VK_LCONTROL,0,0,0);
                            keybd_event('V',0,0,0);
                            keybd_event(VK_LCONTROL,0,KEYEVENTF_KEYUP,0);
                            keybd_event(VK_RETURN,0,0,0);
                            keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
                        }

                        Beep(700,500);
                        timer2.start(1000);
                        l.exec();
                    }
                }
                if(server.at(cpt).contains("]") || server.at(cpt).contains("default"))
                    europe = false;
            }
            if(server.at(cpt).contains("europe"))
                europe = true;
        }
        Tmp(true);
    }
}

void MainWindow::arreter()
{
    if(demarrage)
    {
        ui->bArreter->setText("Démarrer");
        demarrage = false;
    }
    else
    {
        ui->bArreter->setText("Arreter");
        demarrage = true;
        Demarrage();
    }
}

void MainWindow::Tmp(bool f)
{
    if(f)
        tmp.start(10000);
    while(tmp.isActive())
    {
        qApp->processEvents();
        ui->lcdNumber->display(tmp.remainingTime()/1000);
    }
}