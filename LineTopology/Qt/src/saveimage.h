/**
    saveImage class declaration

    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/

#ifndef SAVEIMAGE_H
#define SAVEIMAGE_H

#include <QWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <iostream>
#include <QMessageBox>

namespace Ui {
class saveimage;
}

class saveimage : public QWidget
{
    Q_OBJECT

public:
    explicit saveimage(QWidget *parent = nullptr, QString currentFilename = "", QString currentFolder = "");

    QString FolderDir;

    QString Filename;

    bool status;

    ~saveimage();

private slots:
    void on_folderBrowser_clicked();

    void on_accept_clicked();

    void on_reject_clicked();

private:
    Ui::saveimage *ui;

signals:
    void SendStatusToMainWindow(const bool status_new);
};

#endif // SAVEIMAGE_H
