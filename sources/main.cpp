#include <QApplication>
#include "mainwindow.h"
#include "thread.h"
#include <QtConcurrent/QtConcurrent>

int main(int argc,char** argv) {
    QApplication app(argc, argv);
	
    app.setApplicationName("Cellular Automata");
    app.setOrganizationDomain("http://www.itb.ie/");
    app.setOrganizationName("ITB");
    app.setApplicationVersion("0.1a");

    MainWindow w;
    w.show();

    thread mThread1;
    mThread1.setObjectName("Infection");
    mThread1.start();

    thread mThread2;
    mThread2.setObjectName("Medicine");
    mThread2.start();


    return app.exec();
}

