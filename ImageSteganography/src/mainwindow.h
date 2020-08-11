/*
 * MainWindow Form Class
 * Author: Mohamed Imran Peer Mohamed
 * Email:  mrmdimran95@gmail.com
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QIntValidator>
#include <QProgressBar>
#include <QLabel>

#include <iostream>
#include <vector>

#include "Steganograpy.h"

#include "about.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_textEdit_textChanged();

    void on_clearButton_clicked();

    void on_startIndex_textEdited(const QString &arg1);

    void on_loadImage_clicked();

    void on_encryptSave_clicked();

    void on_decrypt_clicked();

    void on_about_clicked();

    void on_comboBox_currentIndexChanged(int index);

public slots:
    void ReceiveStatusFromAbout(const bool& arg);

private:
    Ui::MainWindow *ui;
    int totalChar;                          // Total Characters that can be encrypted in the image
    int totalCharLeft;                      // Characters left to encrypt

    QImage image;
    int imageWidth;
    int imageHeight;
    QString FileName;
    Language_English lanEng;
    SteganographyClass stegHandle;

    // Stegnography
    int indexI;
    int indexJ;

    //StatusBar
    QProgressBar *progressBar;
    QLabel *statusText;

    //About
    bool aboutStatus;
    about* aboutHandle;
    aboutText aboutTextHandle;

    // Language
    Languages language;
    QString maxLengthText;
    QString charNotAllowedText;
    QString decStartIndexText;
    QString openImageText;
    QString warningText;
    QString selectImageText;
    QString imagePixelErrorText;
    QString noTextAvailableText;
    QString alterStartingPixelText;
    QString saveImageText;
    QString saveFilenameText;
    QString resultText;
    QString successDecryptText;
    QString startingPixelEmptyText;
    QString startingPixelIncorrectText;
    QString lanNotCorrectText;
    QString encryptSuccessText;
    QString errorText;

    void updateCharactersLeft(int num);

    void UpdateImage();

    void disableAll(bool status);

    void insertTag(std::vector <std::vector <int>> &tag, int &indexi, int &indexj);

    bool VerifyStartTag(int &indexI, int &indexJ, bool &lanError);

    void startDecoding(int &indexi, int &indexj);

    void setEnglishInterface();

    void setDeutschInterface();

    void CalculateCharacters();
};
#endif // MAINWINDOW_H
