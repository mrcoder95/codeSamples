/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *ElementY;
    QLineEdit *ElementX;
    QLineEdit *volfrac;
    QLabel *label_4;
    QLineEdit *penal;
    QLabel *label_5;
    QLineEdit *rmin;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *saveImage;
    QTextBrowser *commandLine;
    QPushButton *start;
    QPushButton *clearconsole;
    QPushButton *stop;
    QLabel *label_8;
    QLineEdit *E_Val;
    QLabel *label_9;
    QLineEdit *imageScale;
    QLabel *imageoutput;
    QLabel *label_10;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(780, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(320, 10, 181, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 50, 101, 17));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(420, 50, 101, 17));
        ElementY = new QLineEdit(centralwidget);
        ElementY->setObjectName(QString::fromUtf8("ElementY"));
        ElementY->setGeometry(QRect(570, 50, 142, 25));
        ElementY->setInputMethodHints(Qt::ImhNone);
        ElementX = new QLineEdit(centralwidget);
        ElementX->setObjectName(QString::fromUtf8("ElementX"));
        ElementX->setGeometry(QRect(180, 50, 142, 25));
        ElementX->setInputMethodHints(Qt::ImhNone);
        volfrac = new QLineEdit(centralwidget);
        volfrac->setObjectName(QString::fromUtf8("volfrac"));
        volfrac->setGeometry(QRect(180, 100, 142, 25));
        volfrac->setInputMethodHints(Qt::ImhNone);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 100, 111, 17));
        penal = new QLineEdit(centralwidget);
        penal->setObjectName(QString::fromUtf8("penal"));
        penal->setGeometry(QRect(570, 100, 142, 25));
        penal->setInputMethodHints(Qt::ImhNone);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(420, 100, 101, 17));
        rmin = new QLineEdit(centralwidget);
        rmin->setObjectName(QString::fromUtf8("rmin"));
        rmin->setGeometry(QRect(180, 150, 142, 25));
        rmin->setInputMethodHints(Qt::ImhNone);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(50, 150, 101, 17));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(50, 200, 101, 17));
        saveImage = new QComboBox(centralwidget);
        saveImage->addItem(QString());
        saveImage->addItem(QString());
        saveImage->setObjectName(QString::fromUtf8("saveImage"));
        saveImage->setGeometry(QRect(180, 200, 141, 25));
        commandLine = new QTextBrowser(centralwidget);
        commandLine->setObjectName(QString::fromUtf8("commandLine"));
        commandLine->setGeometry(QRect(20, 490, 741, 261));
        start = new QPushButton(centralwidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(200, 240, 89, 25));
        clearconsole = new QPushButton(centralwidget);
        clearconsole->setObjectName(QString::fromUtf8("clearconsole"));
        clearconsole->setGeometry(QRect(460, 240, 101, 25));
        stop = new QPushButton(centralwidget);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setGeometry(QRect(330, 240, 89, 25));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(420, 150, 121, 17));
        E_Val = new QLineEdit(centralwidget);
        E_Val->setObjectName(QString::fromUtf8("E_Val"));
        E_Val->setGeometry(QRect(570, 150, 142, 25));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(420, 200, 131, 17));
        imageScale = new QLineEdit(centralwidget);
        imageScale->setObjectName(QString::fromUtf8("imageScale"));
        imageScale->setGeometry(QRect(570, 200, 142, 25));
        imageoutput = new QLabel(centralwidget);
        imageoutput->setObjectName(QString::fromUtf8("imageoutput"));
        imageoutput->setGeometry(QRect(20, 300, 741, 180));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 270, 141, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 780, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "FEM Solver", nullptr));
#if QT_CONFIG(statustip)
        MainWindow->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        label->setText(QCoreApplication::translate("MainWindow", "Qt License - Open Source", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Elements in X", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Elements in Y", nullptr));
        ElementY->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        ElementX->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        volfrac->setText(QCoreApplication::translate("MainWindow", "0.5", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Volume Fraction", nullptr));
        penal->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Penal", nullptr));
        rmin->setText(QCoreApplication::translate("MainWindow", "1.5", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "R Minimum", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Save Image", nullptr));
        saveImage->setItemText(0, QCoreApplication::translate("MainWindow", "False", nullptr));
        saveImage->setItemText(1, QCoreApplication::translate("MainWindow", "True", nullptr));

        start->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        clearconsole->setText(QCoreApplication::translate("MainWindow", "Clear Console", nullptr));
        stop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Young's Modulus", nullptr));
        E_Val->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Scale Image", nullptr));
        imageScale->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        imageoutput->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Simulation Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
