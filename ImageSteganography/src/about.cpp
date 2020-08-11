/*
 * Definition of about Class.
 * Author: Mohamed Imran Peer Mohamed
 * Email:  mrmdimran95@gmail.com
*/
#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->setFixedSize(480, 280);
}

about::~about()
{
    delete ui;
}

void about::on_ok_clicked()
{
    emit    SendStatusToMainWindow(true);
    this->close();
}

void about::setLabels(aboutText labelText)
{
    ui->appNameLabel->setText(labelText.appNameText);
    ui->authorLabel->setText(labelText.authorText);
    ui->commercialLabel->setText(labelText.commercialText);
    ui->commercialLabel->setAlignment(Qt::AlignCenter);
    ui->commercialLabel->setStyleSheet("font-size:10pt;"
                                       "font-weight:600;");
    ui->issueLabel->setText(labelText.issueText);
    ui->issueLabel->setAlignment(Qt::AlignCenter);
    ui->issueLabel->setStyleSheet("font-size:10pt;");
    ui->ok->setText(labelText.okText);
}
