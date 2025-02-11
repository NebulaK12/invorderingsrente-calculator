/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QDateEdit *Vervaldatum;
    QDoubleSpinBox *arBedrag;
    QDateEdit *Betaaldatum;
    QPushButton *pushButtonBereken;
    QLabel *labelResultaat;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Vervaldatum = new QDateEdit(centralwidget);
        Vervaldatum->setObjectName("Vervaldatum");
        Vervaldatum->setGeometry(QRect(110, 150, 161, 22));
        arBedrag = new QDoubleSpinBox(centralwidget);
        arBedrag->setObjectName("arBedrag");
        arBedrag->setGeometry(QRect(110, 180, 161, 22));
        arBedrag->setMaximum(10000000.000000000000000);
        arBedrag->setSingleStep(0.010000000000000);
        Betaaldatum = new QDateEdit(centralwidget);
        Betaaldatum->setObjectName("Betaaldatum");
        Betaaldatum->setGeometry(QRect(110, 210, 161, 22));
        pushButtonBereken = new QPushButton(centralwidget);
        pushButtonBereken->setObjectName("pushButtonBereken");
        pushButtonBereken->setGeometry(QRect(110, 240, 75, 24));
        labelResultaat = new QLabel(centralwidget);
        labelResultaat->setObjectName("labelResultaat");
        labelResultaat->setGeometry(QRect(80, 280, 381, 121));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonBereken->setText(QCoreApplication::translate("MainWindow", "Bereken", nullptr));
        labelResultaat->setText(QCoreApplication::translate("MainWindow", "Rente", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
