/**
    Line Topology

    Created by: Mohamed Imran Peer Mohamed
    Email: mrmdimran95@gmail.com
*/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGuiApplication::setWindowIcon(QIcon("logo.png"));
    MainWindow w;
    w.show();
    return a.exec();
}
