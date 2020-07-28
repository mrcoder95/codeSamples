/**
    mainWindow class declaration

    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIntValidator>
#include <QDoubleValidator>
#include "saveimage.h"
#include "mainlinetopology.h"

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
    void on_start_clicked();

    void on_clearconsole_clicked();

    void main_run();

    void on_ElementX_editingFinished();

    void on_ElementY_editingFinished();

    void on_volfrac_editingFinished();

    void on_penal_editingFinished();

    void on_rmin_editingFinished();

    void on_E_Val_editingFinished();

    void on_saveImage_activated(const QString &arg1);

    void on_stop_clicked();

    void on_imageScale_editingFinished();

public slots:
    void ReceiveStatusFromSaveImageForm(const bool& arg);
    // To update the image
    void updateImage(QImage img);

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;

    // Simulation Parameters
    unsigned int nelx;
    unsigned int nely;
    double volfrac;
    double penal;
    double rmin;
    double E;

    // Save Image Parameters
    bool saveImage;
    saveimage *saveImageHandle;
    QString FolderDir;
    QString Filename;
    QString fileExt;
    double imageScale;
    bool newSimImage;

    // Line Topology Handle
    mainLineToplogy simHandle;

    // Timer to update status bar
    int timerId;

    // To lock all functions of mainWindow during simulation
    void LockAll(bool status);

    // To set the parameters for simulation
    void setParameters();

    // To print the output on console
    void updateconsole(string Text);

    void CreateSimImage();


};
#endif // MAINWINDOW_H
