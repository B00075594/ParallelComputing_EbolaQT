#ifndef THREAD_H
#define THREAD_H
#include <QtCore>

class thread : public QThread{
public:
    thread();
    void run();
    void runMedicine();
};

#endif // THREAD_H
