#ifndef GRAPHICSVIEWER_H
#define GRAPHICSVIEWER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QColorDialog>
#include <QSettings>
#include <QApplication>

class GraphicsViewer : public QGraphicsView {
    Q_OBJECT
    public :
        GraphicsViewer(int amountWidth,int amountHeight,int width,int height);
        ~GraphicsViewer();

        QList<QList<int> >& state();
        void setState(int x,int y,int s);
        int width();
        int height();

        QColor activeColor();
        QColor inactiveColor();
        QColor recoveredColor();

        void newActiveColor();
        void newInactiveColor();
        void newRecoveredColor();
        void setDefaultColor();
    public slots :
        void clear();
    protected :
        void mouseMoveEvent(QMouseEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
    private :
        QGraphicsRectItem* getNode(const QPoint& pos);
        int* getNodeState(const QPoint& pos);
    private :
        QGraphicsScene* m_scene;
        QList<QList<QGraphicsRectItem*> > m_grid;
        QList<QList<int> > m_state;

        bool m_leftMousePressed;
        bool m_rightMousePressed;

        int m_amountWidth;
        int m_amountHeight;
        int m_width;
        int m_height;

        QColor m_activeColor;
        QColor m_inactiveColor;
        QColor m_recoveredColor;

};

#endif
