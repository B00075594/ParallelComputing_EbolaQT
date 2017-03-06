#include "thread.h"
#include <QtCore>
#include <QDebug>
#include "mainwindow.h"


thread::thread(){
}

void thread::run(){
    qDebug() << this->currentThread()<< "Running";

    if (this->objectName()=="Medicine"){
        qDebug() << "Filter working";

    }
}

