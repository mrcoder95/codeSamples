/*
 * Definition of MainWindow Class.
 * Author: Mohamed Imran Peer Mohamed
 * Email:  mrmdimran95@gmail.com
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

void pixelUpdate(QRgb &Pixel);
void pixelCheck(int *numPixel, QRgb &Pixel);
void combinePixels(int *numPixel, QRgb &Pixel);
void pixelLastDigit(QRgb &Pixel);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowIcon(QIcon("main.ico"));
    ui->setupUi(this);

    // Set Initialize Parameters
    imageWidth = 0;
    imageHeight = 0;
    totalChar = 0;
    totalCharLeft = totalChar;
    FileName = "";


    ui->startIndex->setValidator(new QIntValidator(0, 100000000, this));

    disableAll(true);

    // Status Bar
    statusText = new QLabel();
    statusText->setText("Progress");
    ui->statusbar->addWidget(statusText);
    ui->statusbar->addPermanentWidget(ui->progressBar);

    // Language Setting
    language = ENGLISH;
    setEnglishInterface();
    stegHandle.setLanguage(language);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Update the characters count
void MainWindow::updateCharactersLeft(int num)
{
    ui->charLeft->setText(QString(QString::number(num) + "\\" + QString::number(totalChar)));
}

// Check the number of characters that can be encrypted, if the characters exceed the limit
// delete the final character
void MainWindow::on_textEdit_textChanged()
{
    if (ui->textEdit->toPlainText().length() > 0)
    {
        if (totalChar - (ui->textEdit->toPlainText()).length() + 1 > 0)
            updateCharactersLeft(totalChar - (ui->textEdit->toPlainText()).length());
        else {
            QMessageBox::critical(this, errorText, maxLengthText);
            ui->textEdit->setPlainText(ui->textEdit->toPlainText().remove(ui->textEdit->toPlainText().size() - 1, 1));
        }

        // Illegal Characters Check
        QChar c = ui->textEdit->toPlainText().at(ui->textEdit->toPlainText().size() - 1);
        if (!stegHandle.Characters.contains(c))
        {
            ui->textEdit->setPlainText(ui->textEdit->toPlainText().remove(ui->textEdit->toPlainText().size() - 1, 1));
            QMessageBox::critical(this, errorText, QString(c) + charNotAllowedText);
        }

    }
}

// Clear the textEdit
void MainWindow::on_clearButton_clicked()
{
    ui->textEdit->clear();
    CalculateCharacters();
}

// Start Index changed, reevaluate the maximum number of characters that can be encrypted in the image
void MainWindow::on_startIndex_textEdited(const QString &arg1)
{
    // Calculate the maximum characters that can be encrypted in the image
    totalChar = imageWidth * imageHeight - 15;

    // Verify the whether the start index suits the current information
    if (totalChar - arg1.toInt() - ui->textEdit->toPlainText().length() < 0)
    {
        ui->startIndex->setText(ui->startIndex->text().remove(arg1.size() - 1, 1));
        QMessageBox::critical(this, errorText, decStartIndexText);
        return;
    }

    // Calculate the maximum characters that can be encrypted in the image with the inclusion of start index
    totalChar = imageWidth * imageHeight - 15 - arg1.toInt();

    // Update the actual characters that can be encrypted
    totalCharLeft = totalChar - (ui->textEdit->toPlainText()).length();

    // Update the characters count in the MainWindow
    updateCharactersLeft(totalCharLeft);
}

void MainWindow::on_loadImage_clicked()
{
    // Load the Image
    QString FileNameNew = QFileDialog::getOpenFileName(this, openImageText, "", tr("Image Files (*.png *.jpg *.bmp)"));

    if (FileNameNew.isEmpty() && FileName.isEmpty()) {
       QMessageBox::warning(this, warningText, selectImageText);
    } else if (!FileNameNew.isEmpty()) {

       // Clear the textEdit
       ui->textEdit->clear();

       FileName = FileNameNew;

       // Load Image to variable
       QImage imageTemp(FileNameNew);

       image = imageTemp;

       // Set the image parameters
       CalculateCharacters();

       // Check Image Pixel
       // If Image Pixel is less than 20, display error
       if (imageWidth * imageHeight < 20)
       {
           QMessageBox::critical(this, errorText, imagePixelErrorText);
           disableAll(true);
           return;
       } else {
            // Load the Image in Graphic View
            UpdateImage();
            disableAll(false);
            updateCharactersLeft(totalCharLeft);
       }
    }
}

// Update Image in the Graphic View
void MainWindow::UpdateImage()
{
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);
    ui->imageView->setScene(scene);

}

// Disable / Enable all the functions before / after image loading
void MainWindow::disableAll(bool status)
{
    ui->textEdit->setDisabled(status);
    ui->startIndex->setDisabled(status);
    ui->clearButton->setDisabled(status);
    ui->encryptSave->setDisabled(status);
    ui->decrypt->setDisabled(status);
}

// Encrypt the Information
void MainWindow::on_encryptSave_clicked()
{
    // Calculate the Starting Index.
    indexI = int(ui->startIndex->text().toInt() / imageHeight);
    indexJ = ui->startIndex->text().toInt() % imageHeight;

    // Extract the information required to encrypt
    QString Text = ui->textEdit->toPlainText();
    if (Text.isEmpty())
    {
        QMessageBox::critical(this, errorText, noTextAvailableText);
        return;
    }

    // Check whether the information can be encrypted within the image
    if ((indexI * indexJ + Text.length() + 15) > (imageWidth * imageHeight))
    {
            QMessageBox::critical(this, errorText, alterStartingPixelText);
            return;
    }

    // Save Image Location
    QString saveImageName = QFileDialog::getSaveFileName(this, saveImageText, "", tr("Images (*.png)"));
    if (saveImageName.isEmpty())
    {
        QMessageBox::critical(this, errorText, saveFilenameText);
        return;
    }

    // Set progressBar
    ui->progressBar->setRange(0, Text.length() + 15);
    ui->progressBar->setValue(0);


    // Insert Start Tags into the image
    insertTag(stegHandle.start_tag, indexI, indexJ);

    // Update the indexes if the last column of the row is reached
    indexJ++;
    if (indexJ >= imageHeight)
    {
        indexJ = 0;
        indexI++;
    }

    // Calculate the Length of the information
    unsigned int Length = (ui->textEdit->toPlainText()).length();

    int m = 0;
    int n = 0;
    int o = 0;

    // Encryption of information character-by-character
    for (unsigned int i = 0; i < Length; i++)
    {
        // Extract the pixel
        QRgb pixel = image.pixel(indexI, indexJ);

        // Encode the Character
        stegHandle.encodeText(m, n, o, Text[i]);

        int numPixel[3] = {m, n, o};

        // Reset the pixel last digit to zero
        pixelUpdate(pixel);

        // Verify the pixel and tag to limit the final pixel value to be less than or equal to 255
        pixelCheck(&numPixel[0], pixel);

        // Combine the tag and pixel
        combinePixels(&numPixel[0], pixel);

        // Update the image pixel
        image.setPixel(indexI, indexJ, pixel);

        // update the progressBar
        ui->progressBar->setValue(ui->progressBar->value() + 1);

        indexJ++;

        // Update the indexes if the last column of the row is reached
        if (indexJ >= imageHeight)
        {
            indexI++;
            indexJ = 0;
        }

    }

    // Insert End Tags
    insertTag(stegHandle.end_tag, indexI, indexJ);

    // Save the Image
    if (saveImageName.contains(".png"))
        image.save(saveImageName, "PNG", -1);
    else
        image.save(saveImageName + ".png", "PNG", -1);

    QMessageBox::information(this, resultText, encryptSuccessText);
}

// During the encryption, insertion of start and end tag.
void MainWindow::insertTag(std::vector <std::vector <int>> &tag, int &indexi, int &indexj)
{
    // Initialize the Tag Index
    unsigned int tagIndex = 0;

    // Access the image pixel-by-pixel
    for (int i = indexi; i < imageWidth; i++)
        for (int j = indexj; j < imageHeight; j++)
        {
            // Extract the pixel
            QRgb pixel = image.pixel(i, j);

            // Reset the pixel last digit to zero
            pixelUpdate(pixel);

            // Verify the pixel and tag to limit the final pixel value to be less than or equal to 255
            pixelCheck(&tag[tagIndex][0], pixel);

            // Combine the tag and pixel
            combinePixels(&tag[tagIndex][0], pixel);

            // set the pixel
            image.setPixel(i, j, pixel);

            // Update the progressBar
            ui->progressBar->setValue(ui->progressBar->value() + 1);

            // Update the tagIndex
            tagIndex++;
            indexj = 0;

            // If all the start tag is added to the image, then exit the function
            if (tag.size() == tagIndex)
            {
                indexi = i;
                indexj = j;
                return;
            }
        }

}

// Verify the Strat Tag Position
bool MainWindow::VerifyStartTag(int &indexi, int &indexj, bool &lanError)
{
    // Initialize the startTag Index
    unsigned int tagIndex = 0;

    // Access the image pixel-by-pixel
    for (int i = indexi; i < imageWidth; i++)
        for (int j = indexj; j < imageHeight; j++)
        {
            // Extract the pixel
            QRgb pixel = image.pixel(i, j);

            // Exract the Last Digit of the pixel
            pixelLastDigit(pixel);

            // If the start tag is not matching, exit the function
            if (qRed(pixel) != stegHandle.start_tag[tagIndex][0] || qGreen(pixel) != stegHandle.start_tag[tagIndex][1] || qBlue(pixel) != stegHandle.start_tag[tagIndex][2])
            {
                // For Different Language
                if (tagIndex >= 5)
                    lanError = true;
                return false;
            }

            // Update the tagIndex
            tagIndex++;

            // Reset the indexJ = 0 to start the next row column from beginning
            indexj = 0;

            // If the start tag is matching, exit the function
            if (tagIndex == stegHandle.start_tag.size())
            {
                indexi = i;
                indexj = j;
                return true;
            }
        }
    return true;
}

// Decode the Information
void MainWindow::startDecoding(int &indexi, int &indexj)
{
    // Store Extracted Information.
    QString Text = "";

    // Access the image pixel-by-pixel
    for (int i = indexi; i < imageWidth; i++)
        for (int j = indexj; j < imageHeight; j++)
        {
            // Extract the pixel
            QRgb pixel = image.pixel(i, j);

            // Exract the Last Digit of the pixel
            pixelLastDigit(pixel);

            // Identify the End Tag and the display the information
            if (qRed(pixel) == stegHandle.end_tag[0][0] && qGreen(pixel) == stegHandle.end_tag[0][1] && qBlue(pixel) == stegHandle.end_tag[0][2])
            {
                ui->textEdit->setPlainText(Text);
                QMessageBox::information(this, resultText, successDecryptText);
                return;
            }

            // Update the progressBar
            ui->progressBar->setValue(ui->progressBar->value() + 1);

            // Update the Text
            Text += stegHandle.decodeText(qRed(pixel), qGreen(pixel), qBlue(pixel));

            // Reset the indexJ = 0 to start the next row column from beginning
            indexj = 0;
        }
}

void MainWindow::on_decrypt_clicked()
{
    // Clear the textEdit for output.
    ui->textEdit->clear();

    // Check whether startIndex is empty.
    if (ui->startIndex->text().isEmpty())
    {
        QMessageBox::critical(this, errorText, startingPixelEmptyText);
        return;
    }

    // Calculate the Starting Index.
    indexI = int(ui->startIndex->text().toInt() / imageHeight);
    indexJ = ui->startIndex->text().toInt() % imageHeight;

    // Verify the Starting Index.
    bool lanError = false;
    bool ValidIndex = VerifyStartTag(indexI, indexJ, lanError);
    if (!ValidIndex)
    {
        if (lanError)
            QMessageBox::critical(this, errorText, lanNotCorrectText);
        else
            QMessageBox::critical(this, errorText, startingPixelIncorrectText);
        return;
    }

    // Update the indexes if the last column of the row is reached
    indexJ++;
    if (indexJ >= imageHeight)
    {
        indexI++;
        indexJ = 0;
    }

    // Set Progressbar
    ui->progressBar->setRange(0, imageWidth * imageHeight);
    ui->progressBar->setValue(0);

    // Decode the Information
    startDecoding(indexI, indexJ);

    // Finish the Progressbar
    ui->progressBar->setValue(imageWidth * imageHeight);
}

// Remove Pixel last digit and set it to zero.
void pixelUpdate(QRgb &Pixel)
{
    Pixel -= qRgb(qRed(Pixel) % 10, qGreen(Pixel) % 10, qBlue(Pixel) % 10);
}

/*
 * Check Image Pixel
 * When the Image pixel is above 250 and encode text number is greater than 5,
 * then when both are combined it will exceed the maximum pixel value of 255,
 * to avoid that instance the image pixel value is changed to 240.
*/
void pixelCheck(int *numPixel, QRgb &Pixel)
{
    if (*numPixel > 5 && qRed(Pixel) >= 250)
        Pixel = qRgb(240, qGreen(Pixel), qBlue(Pixel));
    if (*(numPixel + 1) > 5 && qGreen(Pixel) >= 250)
        Pixel = qRgb(qRed(Pixel), 240, qBlue(Pixel));
    if (*(numPixel + 2) > 5 && qBlue(Pixel) >= 250)
        Pixel = qRgb(qRed(Pixel), qGreen(Pixel), 240);

}

// Combine the Image Pixel and Number Pixel.
void combinePixels(int *numPixel, QRgb &Pixel)
{
    Pixel += qRgb(*numPixel, *(numPixel + 1), *(numPixel + 2));
}

// Get the Last Digit of the Pixel.
void pixelLastDigit(QRgb &Pixel)
{
    Pixel = qRgb(qRed(Pixel) % 10, qGreen(Pixel) % 10, qBlue(Pixel) % 10);
}

// Receiving the information from about widget
void MainWindow::ReceiveStatusFromAbout(const bool& status)
{
    this->show();
}

// Display about form
void MainWindow::on_about_clicked()
{
    aboutHandle = new about(nullptr);

    // Set Language
    aboutHandle->setLabels(aboutTextHandle);

    // Establish an event handler with the about form, to know the terminatation of the form.
    connect(aboutHandle, SIGNAL(SendStatusToMainWindow(bool)), this, SLOT(ReceiveStatusFromAbout(bool)));

    // Display the about form.
    aboutHandle->show();

    // Hide the MainWindow form
    this->hide();
}

// Calculate the number of characters that can be encrypted in the image
void MainWindow::CalculateCharacters()
{
    // Set the image parameters
    imageWidth = image.size().width();
    imageHeight = image.size().height();
    totalChar = imageWidth * imageHeight - 10 - 5;       // Start Tag = 10 | Eng Tag = 5

    totalCharLeft = totalChar;
    updateCharactersLeft(totalCharLeft);
}

// Language Update
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (language != index)
        ui->textEdit->clear();
    switch (index)
    {
        case 0: language = ENGLISH;
                setEnglishInterface();
                break;
        case 1: language = DEUTSCH;
                setDeutschInterface();
                break;
    }
    stegHandle.setLanguage(language);
    if (!image.isNull())
        CalculateCharacters();
}

// Set Parameters for English Interface
void MainWindow::setEnglishInterface()
{
    ui->loadImage->setText("Load Image");
    ui->clearButton->setText("Clear Text");
    ui->encryptSave->setText("Encrypt and Save");
    ui->decrypt->setText("Decrypt");
    ui->about->setText("About");
    ui->languageLabel->setText("Select Language");
    ui->textLabel->setText("Enter the Text");
    ui->charCountLabel->setText("Number of Characters");
    ui->startingPixelLabel->setText("Enter the Starting Pixel");
    statusText->setText("Progress");
    ui->statusbar->addWidget(statusText);

    maxLengthText = "More than Maximum Length.";
    charNotAllowedText = " Character is Not Allowed";
    decStartIndexText = "Decrease the Start Index.";
    openImageText = "Open Image";
    warningText = "Warning";
    selectImageText = "Select an Image.";
    imagePixelErrorText = "Image is Less than 20px.\nSelect an Image which contains more than 20px.";
    noTextAvailableText  = "No Text is available to Encrypt.";
    alterStartingPixelText = "Change the Starting Pixel or reduce the text.";
    saveImageText = "Save Image";
    saveFilenameText = "Enter the Filename to Save.";
    resultText = "Result";
    successDecryptText = "Data has been successfully decrypted.";
    startingPixelEmptyText = "Starting Pixel is empty.";
    startingPixelIncorrectText = "Value of Starting Pixel is Incorrect.";
    lanNotCorrectText = "Encrypted Language is different.";
    encryptSuccessText = "Data has been encrypted and saved.";
    errorText = "Error";

    aboutTextHandle.okText = "OK";
    aboutTextHandle.appNameText = "Application:";
    aboutTextHandle.authorText = "Author:";
    aboutTextHandle.issueText = "Any Issues report to Email || GitHub Link.";
    aboutTextHandle.commercialText = "Non Commercial Use";

}

// Set Parameters for Deutsch Interface
void MainWindow::setDeutschInterface()
{
    ui->loadImage->setText("Bild Laden");
    ui->clearButton->setText("Klartext");
    ui->encryptSave->setText("Verschlüsseln und Speichern");
    ui->decrypt->setText("Entschlüsseln");
    ui->about->setText("Über");
    ui->languageLabel->setText("Sprache auswählen");
    ui->textLabel->setText("Geben Sie den Text ein");
    ui->charCountLabel->setText("Anzahl von Charakteren");
    ui->startingPixelLabel->setText("Geben Sie das Startpixel ein");
    statusText->setText("Fortschritt");
    ui->statusbar->addWidget(statusText);

    maxLengthText = "Mehr als maximale Länge.";
    charNotAllowedText = " Zeichen ist nicht erlaubt";
    decStartIndexText = "Startindex verringern.";
    openImageText = "Bild öffnen";
    warningText = "Warnung";
    selectImageText = "Bild auswählen.";
    imagePixelErrorText = "Bild ist kleiner als 20px.\nWählen Sie ein Bild aus, das mehr als 20px enthält.";
    noTextAvailableText  = "Zum Verschlüsseln steht kein Text zur Verfügung.";
    alterStartingPixelText = "Ändere das Startpixel oder reduziere den Text..";
    saveImageText = "Bild speichern";
    saveFilenameText = "Geben Sie den zu speichernden Dateinamen ein.";
    resultText = "Ergebnis";
    successDecryptText = "Daten wurden erfolgreich entschlüsselt.";
    startingPixelEmptyText = "Startpixel ist leer.";
    startingPixelIncorrectText = "Wert des Startpixels ist falsch.";
    lanNotCorrectText = "Die verschlüsselte Sprache ist anders.";
    encryptSuccessText = "Daten wurden verschlüsselt und gespeichert.";
    errorText = "Error";

    aboutTextHandle.okText = "OK";
    aboutTextHandle.appNameText = "Anwendung:";
    aboutTextHandle.authorText = "Autor:";
    aboutTextHandle.issueText = "Alle Probleme werden an E-Mail || GitHub Link gemeldet.";
    aboutTextHandle.commercialText = "Nichtkommerzielle Nutzung";
}
