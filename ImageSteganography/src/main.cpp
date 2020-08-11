/*
 * Main File
 * Author: Mohamed Imran Peer Mohamed
 * Email:  mrmdimran95@gmail.com
*/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
