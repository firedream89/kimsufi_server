#include "mainwindow.h"
#include "ui_mainwindow.h"
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

QString version =  "1.03";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Dispo Serveur Kimsufi");
    demarrage = false;
    Beep(700,1000);

    tmp.setInterval(1000);
    tmp.setSingleShot(false);

    connect(ui->bArreter,SIGNAL(clicked(bool)),this,SLOT(arreter()));
    connect(&tmp,SIGNAL(timeout()),this,SLOT(Tmp()));
    connect(ui->actionQuitter,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
    connect(ui->actionA_Propos_de_Qt,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));
    connect(ui->actionA_Propos,SIGNAL(triggered(bool)),this,SLOT(About()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(Demarrage()));

    this->show();
    InitListServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::About()
{
    QFormLayout *layout = new QFormLayout;
    QLabel vVersion(version);
    QLabel auteur("Kévin BRIAND");
    QLabel licence("Ce logiciel est sous licence GNU LGPLv3");
    QLabel github("<a href='https://github.com/firedream89?tab=repositories'>ici</a>");
    github.setOpenExternalLinks(true);
    layout->addRow("Version",&vVersion);
    layout->addRow("Auteur",&auteur);
    layout->addRow("Licence",&licence);
    layout->addRow("Sources",&github);
    QDialog *fen = new QDialog;
    fen->setLayout(layout);
    fen->setWindowTitle("A Propos de " + this->windowTitle());
    fen->exec();
}

void MainWindow::InitListServer()
{
    QWebView *web = new QWebView;
    QEventLoop loop;
    QTimer timer;
    connect(web,SIGNAL(loadFinished(bool)),&loop,SLOT(quit()));
    connect(&timer,SIGNAL(timeout()),&loop,SLOT(quit()));

    web->load(QUrl("https://www.kimsufi.com/fr/serveurs.xml"));
    timer.start(30000);
    loop.exec();

    QFile fichier("web_Temp.txt");
    fichier.resize(0);
    fichier.open(QIODevice::WriteOnly);
    QTextStream flux(&fichier);
    flux << web->page()->mainFrame()->toHtml();
    fichier.close();

    if(!fichier.open(QIODevice::ReadOnly))
        QMessageBox::information(this,"","Echec d'ouverture du fichier");

    while(!flux.atEnd())
    {
        QString var = flux.readLine();
        if(var.contains("zone-dedicated-availability") && var.split("\"").count() >= 7)
        {
            QString tmp = var.split("\"").at(7);
            var = flux.readLine();
            ui->cServeur->addItem(var.split(">").at(2).split("<").at(0),tmp);
        }
        else if(var.contains("</table>"))
            break;
    }
    fichier.close();
}

void MainWindow::Demarrage()
{
    tmp.stop();
    timer.stop();

    QWebView *web = new QWebView;
    QEventLoop l;
    QTimer timer2;
    QStringList v,server;
    QString final,var;

    bool europe(false),dispo(false);

    connect(web,SIGNAL(loadFinished(bool)),&l,SLOT(quit()));
    connect(&timer,SIGNAL(timeout()),&l,SLOT(quit()));
    connect(&timer2,SIGNAL(timeout()),&l,SLOT(quit()));
    connect(ui->bArreter,SIGNAL(clicked(bool)),&timer,SLOT(stop()));


        //Chargement de la page web et extraction des informations serveurs
        web->load(QUrl("https://www.ovh.com/engine/api/dedicated/server/availabilities?country=fr?&hardware=" + ui->cServeur->itemData(ui->cServeur->currentIndex()).toString()));
        l.exec();

        var.clear();
        var = web->page()->mainFrame()->toPlainText();
        server.clear();
        server = var.split("{");
        europe = false;
        for(int cpt = 0;cpt<server.count();cpt++)
        {
            if(europe)//Lecture des serveurs disponible en europe
            {
                //Lecture des informations de disponibilité
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

                ui->dispo->setText(final);

                if(final.split(" ").last() != "unavailable")//si un serveur est disponible
                {
                    //Ouverture de la page d'achat du serveur
                    QDesktopServices::openUrl(QUrl("https://www.kimsufi.com/fr/commande/kimsufi.xml?reference=" + ui->cServeur->itemData(ui->cServeur->currentIndex()).toString()));

                    while(timer.isActive())//envoie d'un bip toute les secondes pdt 10 Sec
                    {
                        Beep(700,500);
                        timer2.start(1000);
                        qApp->processEvents();
                        l.exec();
                    }
                    if(demarrage)
                        arreter();
                    return;
                }
                if(server.at(cpt).contains("]") || server.at(cpt).contains("default"))
                    europe = false;
            }
            if(server.at(cpt).contains("europe"))//Recherche de la liste des serveurs européen
                europe = true;
        }

        if(demarrage)
        {
            tmp.start();
            timer.start(10000);
        }
        else
            timer.stop();
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

void MainWindow::Tmp()
{
    qApp->processEvents();
    ui->lcdNumber->display(timer.remainingTime()/1000);
}