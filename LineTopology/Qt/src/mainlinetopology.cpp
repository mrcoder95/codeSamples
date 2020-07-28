/**
    Line Topology simulation execution

    Original Code was developed by Ole Sigmund in MATLAB.
    Source: https://www.topopt.mek.dtu.dk/Apps-and-software/A-99-line-topology-optimization-code-written-in-MATLAB

    The MATLAB code is converted to C++ code.
    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/

#include "mainlinetopology.h"
#include <QColor>
#include <QColorSpace>

void mainLineToplogy::run()
{
    LineToplogy handle(nelx, nely, volfrac, penal, rmin, E);
    std::vector <std::vector <double>> x(handle.nelemY, vector <double> (handle.nelemX, handle.volfrac));
    std::vector <std::vector <double>> x_old;

    unsigned int iteration = 0;

    double residumm = 1.0;

    double tolerance = 1e-2;
    double c = 0.0;
    double sum = 0.0;

    unsigned int n1 = 0;
    unsigned int n2 = 0;

    while (simulationRunning && nelx > 0 && residumm > tolerance)
    {
        mainWindowLock = true;

        iteration++;
        x_old = x;

        handle.FEA(x);

        c = 0.0;

        for (unsigned int j = 0; j < handle.nelemY; j++) {
            for (unsigned int i = 0; i < handle.nelemX; i++) {

                n1 = (handle.nelemY + 1) * (i    ) + j + 1;
                n2 = (handle.nelemY + 1) * (i + 1) + j + 1;

                double Ue[8] = { handle.U[(2 * n1) - 2], handle.U[(2 * n1) - 1], handle.U[(2 * n2) - 2], handle.U[(2 * n2) - 1],
                                 handle.U[ 2 * n2     ], handle.U[(2 * n2) + 1], handle.U[ 2 * n1     ], handle.U[(2 * n1) + 1]
                               };

                double val = VecT_Mat_Vec_Product (handle.KE, Ue);
                c += std::pow(x[j][i], handle.penal) * val;

                handle.DC[j][i] = -handle.penal * std::pow(x[j][i], handle.penal - 1) * val;
            }
        }

        handle.Mesh_Filter(x);

        handle.Opt_Crt_Update(x);

        residumm = std::abs(x[0][0] - x_old[0][0]);

        sum = 0.0;

        for (unsigned int i = 0; i <  x.size(); i++)
            for (unsigned int j = 0; j <  x[i].size(); j++) {
                if (std::abs(x[i][j] - x_old[i][j]) > residumm)
                    residumm = std::abs(x[i][j] - x_old[i][j]);
                sum += x[i][j];
            }

        // Simulation Statistics
        string Text = "It. " + to_string(iteration) + "\tObj.: " + to_string(c) + "\tVol.: " + to_string (sum /(handle.nelemX * handle.nelemY)) + "\tch.: " + to_string(residumm);

        // Image Generation
        QImage img(x[0].size(), x.size(), QImage::Format_RGB16);
        for (decltype(x.size()) i = 0; i < x[0].size(); i++) {
            for (decltype(x.size()) j = 0; j < x.size(); j++) {
                img.setPixel(i, j, qRgb(255 - x[j][i]*255, 255 - x[j][i]*255, 255 - x[j][i]*255));
            }
        }

        // Sending Image to mainWindow form
        emit imageUpdate(img);

        // Saving image to output file
        if (saveImage)
        {
            img = img.scaled(imageScale, imageScale, Qt::KeepAspectRatio);
            img.save(filename + "_" + QString::fromStdString(to_string(iteration)) + Ext);
        }

        // Sending the result to mainWindow
        if (!simulationRunning) {
            emit signalValueUpdated("Simulation Terminated by user.");
            mainWindowLock = false;
            break;
        } else
            emit signalValueUpdated(QString::fromStdString(Text));

        // Incase of Convergence, terminating the simulation.
        if (residumm < tolerance) {
           simulationRunning = false;
           mainWindowLock = false;
           emit signalValueUpdated("Simulation completed successfully.");
           break;
        }
    }
}

// Termination of Simulation
void mainLineToplogy::terminateSimulation()
{
    if (simulationRunning)
        simulationRunning = false;
}
