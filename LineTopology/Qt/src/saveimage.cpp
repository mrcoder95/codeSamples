/**
    saveImage class definition

    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/

#include "saveimage.h"
#include "ui_saveimage.h"

saveimage::saveimage(QWidget *parent, QString currentFilename, QString currentFolder) :
    QWidget(parent),
    ui(new Ui::saveimage)
{
    ui->setupUi(this);

    /*
     * Identifying Save image folder
     * if user provides the folder name then it is used
     * else the system takes present working directory
     * Note: it is used to avoid the user to change the folder during the multiple simulation run
    */

    if (currentFolder.isEmpty()) {
        // Identifying the present working directory
        char *filePath = nullptr;
        QDir Dir = QFileInfo(filePath).absoluteDir();
        FolderDir = Dir.absolutePath();

        delete filePath;
    } else {
        FolderDir = currentFolder;
    }

    ui->folder->setText(FolderDir);

    // Similar to folder name, file name also selected
    if (currentFilename.isEmpty())
        Filename = ui->filename->text();
    else {
        Filename = currentFilename;
        ui->filename->setText(currentFilename);
    }

    this->setFixedSize(670, 147);           // Window size is fixed
}

saveimage::~saveimage()
{
    delete ui;
}

void saveimage::on_folderBrowser_clicked()
{
    // Selection of folder to save image
    QString TempFolderDir = QFileDialog::getExistingDirectory(this, tr("Select Directory"), FolderDir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog);

    // If user has not se;ected the directory, previous directory is used
    if (!TempFolderDir.isEmpty()) {
        FolderDir = TempFolderDir;
        ui->folder->setText(FolderDir);
    }
}

void saveimage::on_accept_clicked()
{
    status = true;
    if (!ui->filename->text().isEmpty())
        Filename = ui->filename->text();
    if (!ui->folder->text().isEmpty()) {
        QDir dir(ui->folder->text());
        if (dir.exists())
            FolderDir = ui->folder->text();
        else {
            QMessageBox::critical(this, tr("Error"), tr("Folder does not exist"));
            return;
        }
    }


    emit    SendStatusToMainWindow(status);
    this->close();
}

void saveimage::on_reject_clicked()
{
    status = false;
    emit    SendStatusToMainWindow(status);
    this->close();
}
