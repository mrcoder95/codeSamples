/**
    mainWindow Definition

    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

// Aligning Text to Print on Console
string align_text(string A, int size, string B, int insert_pos)
{
    QString text;
    text.fill(' ', size);
    for (int i = 0; i < A.length(); i++)
        text[i] = A[i];
    for (int i = 0; i < B.length(); i++)
        text[i + insert_pos] = B[i];
    return text.toStdString();
}


QString Qalign_text(QString A, int size, QString B, int insert_pos)
{
    QString text;
    text.fill(' ', size);
    for (int i = 0; i < A.length(); i++)
        text[i] = A[i];
    for (int i = 0; i < B.length(); i++)
        text[i + insert_pos] = B[i];
    return text;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Limiting th user input
    ui->ElementX->setValidator(new QIntValidator(0, 100000, this));
    ui->ElementY->setValidator(new QIntValidator(0, 100000, this));
    ui->volfrac->setValidator(new QDoubleValidator(0, 100000, 8, this));
    ui->penal->setValidator(new QDoubleValidator(0, 100000, 8, this));
    ui->rmin->setValidator(new QDoubleValidator(0, 100000, 8, this));
    ui->E_Val->setValidator(new QDoubleValidator(0, 10000000, 8, this));
    ui->imageScale->setValidator(new QDoubleValidator(0, 10000000, 8, this));
    ui->imageScale->setDisabled(true);


    saveImage = false;                               // Initial flag Setting
    simHandle.simulationRunning = false;             // Initial setting value
    timerId = startTimer(1000);                      // Timer to update the status bar
    Filename = "";
    FolderDir = "";

    this->setParameters();                          // Setting Parameters

    this->setFixedSize(780, 780);                   // MainWindow size is fixed 614

    // Creation of Event handler for the starting of FEM Solver
    connect(ui->start,SIGNAL(clicked()),&simHandle,SLOT(start()), Qt::QueuedConnection);

    // Creation of Event handler for the Termination the FEM Solver
    connect(ui->stop,SIGNAL(clicked()),&simHandle,SLOT(terminateSimulation()), Qt::DirectConnection);

    // Creation of Event handler for the updation the Status
    connect(&simHandle,SIGNAL(signalValueUpdated(const QString&)),ui->commandLine,SLOT(append(const QString&)), Qt::QueuedConnection);

    //
    connect(&simHandle,SIGNAL(imageUpdate(const QImage&)), this,SLOT(updateImage(QImage)), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}


// Locking / unlocking the mainwindow properties
void MainWindow::LockAll(bool status)
{
    ui->ElementX->setDisabled(status);
    ui->ElementY->setDisabled(status);
    ui->volfrac->setDisabled(status);
    ui->penal->setDisabled(status);
    ui->rmin->setDisabled(status);
    ui->E_Val->setDisabled(status);
    if (saveImage && status)
        ui->imageScale->setDisabled(true);
    else if (saveImage && !status)
        ui->imageScale->setDisabled(false);
    else
        ui->imageScale->setDisabled(true);
    ui->start->setDisabled(status);

    ui->saveImage->setDisabled(status);
}

// Receiving the information from the saveimage widget
void MainWindow::ReceiveStatusFromSaveImageForm(const bool& status)
{
    if (status)                                                                         // If the user has selected Ok, then new settings are used else the default settings are utilized.
        ui->commandLine->append("New Folder and Filename");
    else
        ui->commandLine->append("Using default Folder and Filename");

    // Image Name, location, and format are described.
    fileExt = ".jpg";
    Filename = saveImageHandle->Filename;
    FolderDir = saveImageHandle->FolderDir;
    ui->commandLine->append("Filename = " + Filename);
    ui->commandLine->append("Folder = " + FolderDir);

    saveImageHandle->deleteLater();
    // Unlocking the MainWindow properties
    this->LockAll(false);

    this->show();
}


// Configuration of Save Image
void MainWindow::on_saveImage_activated(const QString &arg1)
{
    if (arg1 == "True")
    {
        saveImage = true;
        saveImageHandle = new saveimage(nullptr, Filename, FolderDir);

        // Locking the MainWindow properties to block the user from modifying the values of mainwindow during the saveimage window is popped out.
        this->LockAll(true);

        // Establish an event handler with the saveimage form, to know the terminatation of the form.
        connect(saveImageHandle, SIGNAL(SendStatusToMainWindow(bool)), this, SLOT(ReceiveStatusFromSaveImageForm(bool)));

        saveImageHandle->show();

        this->hide();
    } else {
        saveImage = false;
    }
}

// Setting the Line Topology Parameters
void MainWindow::setParameters()
{
    nelx = ui->ElementX->text().toInt();
    nely = ui->ElementY->text().toInt();
    volfrac = ui->volfrac->text().toDouble();
    penal = ui->penal->text().toDouble();
    rmin = ui->rmin->text().toDouble();
    E = ui->E_Val->text().toDouble();
    imageScale = ui->imageScale->text().toDouble();

    simHandle.nelx = nelx;
    simHandle.nely = nely;
    simHandle.volfrac = volfrac;
    simHandle.penal = penal;
    simHandle.rmin = rmin;
    simHandle.E = E;

    simHandle.saveImage = saveImage;
    simHandle.Ext = fileExt;
    simHandle.filename = FolderDir + "/" + Filename;
    simHandle.imageScale = imageScale;

    this->CreateSimImage();
}

// Starting of the Simulation
void MainWindow::on_start_clicked()
{
    simHandle.simulationRunning = true;

    main_run();
    this->LockAll(true);
}

// Printing the output statement on the console
void MainWindow::updateconsole(string Text)
{
    ui->commandLine->append(QString::fromStdString(Text));
    ui->commandLine->update();
}

// Clearing the console
void MainWindow::on_clearconsole_clicked()
{
    ui->commandLine->clear();
}


// Printing the simulation properties on the console
void MainWindow::main_run()
{
    this->setParameters();

    this->updateconsole(align_text("Number of Elements in X", 100, " = " + to_string(nelx), 35));
    this->updateconsole(align_text("Number of Elements in Y", 100, " = " + to_string(nely), 35));
    this->updateconsole(align_text("Volume Fraction", 100, " = " + to_string(volfrac), 44));
    this->updateconsole(align_text("Penal Value", 100, " = " + to_string(penal), 49));
    this->updateconsole(align_text("R Minimum", 100, " = " + to_string(rmin), 48));
    this->updateconsole(align_text("Young's Modulus", 100, " = " + to_string(E), 43));
}

// Whenever a parameter is edited in mainwindow, it is immidiately updated in the class
void MainWindow::on_ElementX_editingFinished()
{
    if (ui->ElementX->text().toInt() > 0)
        this->setParameters();
}

void MainWindow::on_ElementY_editingFinished()
{
    if (ui->ElementY->text().toInt() > 0)
        this->setParameters();
}

void MainWindow::on_volfrac_editingFinished()
{
    this->setParameters();
}

void MainWindow::on_penal_editingFinished()
{
    this->setParameters();
}

void MainWindow::on_rmin_editingFinished()
{
    this->setParameters();
}

void MainWindow::on_E_Val_editingFinished()
{
    this->setParameters();
}

// Printing the status of the simulation on the status bar
void MainWindow::timerEvent(QTimerEvent *event)
{
    switch (simHandle.simulationRunning)
    {
        case true:  ui->statusbar->showMessage(Qalign_text("Simulation Status", 200, "Running", 180), 0);
                    this->LockAll(true);
                    break;
        default: ui->statusbar->showMessage(Qalign_text("Simulation Status", 200, "Not Running", 175), 0);
                 if (!simHandle.mainWindowLock)
                    this->LockAll(false);
        break;
    }
}

void MainWindow::on_stop_clicked()
{
    if (simHandle.simulationRunning)
        updateconsole("Simulation is going to be terminated.");
}

void MainWindow::on_imageScale_editingFinished()
{
    this->setParameters();
}

void MainWindow::updateImage(QImage img)
{
    // Identifying the size of image box (label)
    unsigned int scaleWidth = ui->imageoutput->geometry().width();
    unsigned int scaleHeight = ui->imageoutput->geometry().height();

    // Scaling the image to fix the image box
    img = img.scaled(scaleWidth, scaleHeight);

    // Grid Generation
    if (newSimImage)
    {
        QRgb colorVal = qRgb(255, 0, 0);

        double divisor = (double)scaleWidth/nelx;

        unsigned int count = 0;
        for (double i = divisor; i < scaleWidth; i += divisor)          // double data type is used to include the decimal numbers while splitting the grid
            if (count++ < nelx - 1)
                for (unsigned int j = 0; j < scaleHeight; j++)
                    img.setPixel(int(i), j, colorVal);


        divisor = (double)scaleHeight/nely;

        count  = 0;
        for (double j = divisor; j < scaleHeight; j += divisor)
            if (count++ < nely - 1)
                for (unsigned int i = 0; i < scaleWidth; i++)
                    img.setPixel(int(i), j, colorVal);

        newSimImage = false;
    }

    // Updation of Image
    ui->imageoutput->setPixmap(QPixmap::fromImage(img));
}

//
void MainWindow::CreateSimImage()
{
    // Creation of Image and filling with black
    QImage img(nelx, nely, QImage::Format_RGB16);
    img.fill(Qt::black);
    newSimImage = true;
    updateImage(img);
}
