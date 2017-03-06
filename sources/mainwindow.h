#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QGraphicsView>
#include <QLabel>
#include <QTimer>
#include <QSpinBox>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QSettings>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "graphicsviewer.h"

    class MainWindow : public QMainWindow {
        Q_OBJECT
        public :
            MainWindow(QWidget* parent = 0);

    public slots :
            void saveSettings();
            void setInterval(int value);
            void stateChange();
            void nextTurn();
            void nextTurnMedicine();
            void reset(bool isAtStartup = false);
            void callNAColor();
            void callAColor();
            void callRColor();

        private :
            int numberOfNeighboor(int x,int y,const QList<QList<int> >& state);
        private :
            GraphicsViewer* m_view;
            QLabel* m_numXLabel;
            QLabel* m_numYLabel;
            QLabel* m_speedLabel;
            QSpinBox* m_numX;
            QSpinBox* m_numY;
            QPushButton* m_reset;
            QPushButton* m_state;
            QPushButton* m_fill;
            QPushButton* m_next;
            QPushButton* m_nextM;
            QPushButton* m_reverse;
            QPushButton* m_clear;
            QSlider* m_speed;
            QTimer* m_timer;
            bool m_active;
    };

#endif
