/********************************************************************************
** Form generated from reading UI file 'saveimage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEIMAGE_H
#define UI_SAVEIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_saveimage
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *accept;
    QPushButton *reject;
    QLineEdit *filename;
    QLineEdit *folder;
    QPushButton *folderBrowser;

    void setupUi(QWidget *saveimage)
    {
        if (saveimage->objectName().isEmpty())
            saveimage->setObjectName(QString::fromUtf8("saveimage"));
        saveimage->resize(670, 147);
        label = new QLabel(saveimage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 67, 17));
        label_2 = new QLabel(saveimage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 50, 67, 17));
        accept = new QPushButton(saveimage);
        accept->setObjectName(QString::fromUtf8("accept"));
        accept->setGeometry(QRect(230, 110, 89, 25));
        reject = new QPushButton(saveimage);
        reject->setObjectName(QString::fromUtf8("reject"));
        reject->setGeometry(QRect(370, 110, 89, 25));
        filename = new QLineEdit(saveimage);
        filename->setObjectName(QString::fromUtf8("filename"));
        filename->setGeometry(QRect(190, 10, 351, 25));
        folder = new QLineEdit(saveimage);
        folder->setObjectName(QString::fromUtf8("folder"));
        folder->setGeometry(QRect(190, 50, 351, 25));
        folderBrowser = new QPushButton(saveimage);
        folderBrowser->setObjectName(QString::fromUtf8("folderBrowser"));
        folderBrowser->setGeometry(QRect(570, 50, 89, 25));

        retranslateUi(saveimage);

        QMetaObject::connectSlotsByName(saveimage);
    } // setupUi

    void retranslateUi(QWidget *saveimage)
    {
        saveimage->setWindowTitle(QCoreApplication::translate("saveimage", "Save Image", nullptr));
        label->setText(QCoreApplication::translate("saveimage", "Filename", nullptr));
        label_2->setText(QCoreApplication::translate("saveimage", "Folder ", nullptr));
        accept->setText(QCoreApplication::translate("saveimage", "OK", nullptr));
        reject->setText(QCoreApplication::translate("saveimage", "Cancel", nullptr));
        filename->setText(QCoreApplication::translate("saveimage", "Iteration", nullptr));
        folderBrowser->setText(QCoreApplication::translate("saveimage", "Browse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class saveimage: public Ui_saveimage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEIMAGE_H
