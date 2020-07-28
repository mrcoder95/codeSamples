/**
    mainLineTopology class declaration

    Original Code was developed by Ole Sigmund in MATLAB.
    Source: https://www.topopt.mek.dtu.dk/Apps-and-software/A-99-line-topology-optimization-code-written-in-MATLAB

    The MATLAB code is converted to C++ code.
    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/
#ifndef MTHREAD_H
#define MTHREAD_H


#include <QThread>
#include <QMutex>
#include <QImage>
#include "main_program/main.h"
#include "main_program/src_line/mat_operations.cpp"

class mainLineToplogy : public QThread
{
   Q_OBJECT

public slots:
    void terminateSimulation();

protected:
   virtual void run();

signals:
   void signalValueUpdated(QString);
   void imageUpdate(QImage);

private:

public:
   // Line Topology Parameters
    unsigned int nelx;
    unsigned int nely;
    double volfrac;
    double penal;
    double rmin;
    double E;

    // Save Image
    bool saveImage;
    QString filename;
    QString Ext;
    double imageScale;

    // Simulation Parameters
    bool simulationRunning;
    // Locking mainWindow screen during simulation
    bool mainWindowLock;

};

#endif // MTHREAD_H
