/*
 * About Form Class
 * Author: Mohamed Imran Peer Mohamed
 * Email:  mrmdimran95@gmail.com
*/
#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QString>

struct aboutText
{
    QString authorText;
    QString okText;
    QString commercialText;
    QString issueText;
    QString appNameText;
};

namespace Ui {
class about;
}

class about : public QWidget
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);

    void setLabels(aboutText labelText);

    ~about();

private:
    Ui::about *ui;

signals:
    void SendStatusToMainWindow(const bool status_new);

private slots:
    void on_ok_clicked();
};

#endif // ABOUT_H
