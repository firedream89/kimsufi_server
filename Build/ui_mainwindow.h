/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionA_Propos;
    QAction *actionA_Propos_de_Qt;
    QAction *actionQuitter;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *bArreter;
    QComboBox *cServeur;
    QLCDNumber *lcdNumber;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *dispo;
    QMenuBar *menuBar;
    QMenu *menuMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 97);
        actionA_Propos = new QAction(MainWindow);
        actionA_Propos->setObjectName(QStringLiteral("actionA_Propos"));
        actionA_Propos_de_Qt = new QAction(MainWindow);
        actionA_Propos_de_Qt->setObjectName(QStringLiteral("actionA_Propos_de_Qt"));
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        bArreter = new QPushButton(centralWidget);
        bArreter->setObjectName(QStringLiteral("bArreter"));

        gridLayout->addWidget(bArreter, 0, 0, 1, 1);

        cServeur = new QComboBox(centralWidget);
        cServeur->setObjectName(QStringLiteral("cServeur"));

        gridLayout->addWidget(cServeur, 0, 1, 1, 1);

        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));

        gridLayout->addWidget(lcdNumber, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(107, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        dispo = new QLabel(centralWidget);
        dispo->setObjectName(QStringLiteral("dispo"));

        formLayout->setWidget(0, QFormLayout::FieldRole, dispo);


        gridLayout->addLayout(formLayout, 1, 0, 1, 4);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionA_Propos);
        menuMenu->addAction(actionA_Propos_de_Qt);
        menuMenu->addAction(actionQuitter);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionA_Propos->setText(QApplication::translate("MainWindow", "A Propos", 0));
        actionA_Propos_de_Qt->setText(QApplication::translate("MainWindow", "A Propos de Qt", 0));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        bArreter->setText(QApplication::translate("MainWindow", "D\303\251marrer", 0));
        label->setText(QApplication::translate("MainWindow", "Dernier scan :", 0));
        dispo->setText(QApplication::translate("MainWindow", "Aucun", 0));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
