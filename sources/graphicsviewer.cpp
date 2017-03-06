#include "graphicsviewer.h"

GraphicsViewer::GraphicsViewer(int amountWidth,int amountHeight,int width,int height) {
    QSettings settings(qApp->organizationName(),qApp->applicationName());
    if (settings.contains("a_color"))
        m_activeColor = settings.value("a_color").value<QColor>();
    else m_activeColor = QColor("red");
    if (settings.contains("na_color"))
        m_inactiveColor = settings.value("na_color").value<QColor>();
    else m_inactiveColor = QColor("black");
    if (settings.contains("r_color"))
        m_recoveredColor = settings.value("r_color").value<QColor>();
    else m_recoveredColor = QColor("blue");


    m_amountWidth = amountWidth;
    m_amountHeight = amountHeight;
    m_width = width;
    m_height = height;

    m_leftMousePressed = false;
    m_rightMousePressed = false;
    m_scene = new QGraphicsScene;

    setScene(m_scene);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setFixedSize((m_amountWidth*m_width)+3,(m_amountHeight*m_height)+3);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int x = 0; x < m_amountWidth; x++) {
        QList<QGraphicsRectItem*> line;
        QList<int> stateLine;
        for (int y = 0; y < m_amountHeight; y++) {
            line << m_scene->addRect(m_width*x,m_height*y,m_width,m_height,QPen(),QBrush(m_inactiveColor,Qt::SolidPattern));
            stateLine << 0;
        }
        m_grid << line;
        m_state << stateLine;
    }
}

GraphicsViewer::~GraphicsViewer() {
    delete m_scene;
}

QColor GraphicsViewer::activeColor() {
    return m_activeColor;
}

QColor GraphicsViewer::inactiveColor() {
    return m_inactiveColor;
}

QColor GraphicsViewer::recoveredColor() {
    return m_recoveredColor;
}

void GraphicsViewer::newActiveColor() {
    QColor color = QColorDialog::getColor(m_activeColor);
    if (color.isValid() && color != m_activeColor) {
        m_activeColor = color;
        for (int y = 0; y < m_amountHeight; y++)
            for (int x = 0; x < m_amountWidth; x++)
                setState(x,y,m_state[x][y]);
    }
}

void GraphicsViewer::newInactiveColor() {
    QColor color = QColorDialog::getColor(m_inactiveColor);
    if (color.isValid() && color != m_inactiveColor) {
        m_inactiveColor = color;
        for (int y = 0; y < m_amountHeight; y++)
            for (int x = 0; x < m_amountWidth; x++)
                setState(x,y,m_state[x][y]);
    }
}

void GraphicsViewer::newRecoveredColor() {
    QColor color = QColorDialog::getColor(m_recoveredColor);
    if (color.isValid() && color != m_recoveredColor) {
        m_recoveredColor = color;
        for (int y = 0; y < m_amountHeight; y++)
            for (int x = 0; x < m_amountWidth; x++)
                setState(x,y,m_state[x][y]);
    }
}


void GraphicsViewer::setDefaultColor() {
    m_activeColor = QColor("red");
    m_inactiveColor = QColor("black");
    m_recoveredColor = QColor("blue");
    for (int y = 0; y < m_amountHeight; y++)
        for (int x = 0; x < m_amountWidth; x++)
            setState(x,y,m_state[x][y]);
}

void GraphicsViewer::clear() {
    for (int y = 0; y < m_amountHeight; y++)
        for (int x = 0; x < m_amountWidth; x++)
            setState(x,y,1);
}

QList<QList<int> >& GraphicsViewer::state() {
    return m_state;
}

void GraphicsViewer::setState(int x,int y,int s) {

    if (s == 0 ){ //If state is infected
        m_grid[x][y]->setBrush(QBrush(m_activeColor,Qt::SolidPattern));
    }else if (s == 1){// If state is Susceptible/Alive
        m_grid[x][y]->setBrush(QBrush(m_inactiveColor,Qt::SolidPattern));
    }else if (s == 2){ // if state is Recovered
        m_grid[x][y]->setBrush(QBrush(m_recoveredColor,Qt::SolidPattern));
    }

    m_state[x][y] = s;
}

int GraphicsViewer::width() {
    return m_amountWidth;
}

int GraphicsViewer::height() {
    return m_amountHeight;
}

void GraphicsViewer::mouseMoveEvent(QMouseEvent* event) {
    if (!m_leftMousePressed && !m_rightMousePressed) return;

    QGraphicsRectItem* item = getNode(event->pos());
    if (item == 0) return;

    if (m_leftMousePressed)
        item->setBrush(QBrush(m_activeColor,Qt::SolidPattern));
    if (m_rightMousePressed)
        item->setBrush(QBrush(m_inactiveColor,Qt::SolidPattern));

    int* state = getNodeState(event->pos());
    *state = m_leftMousePressed;
}

void GraphicsViewer::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
        m_leftMousePressed = true;
    if (event->button() == Qt::RightButton)
        m_rightMousePressed = true;

    QGraphicsRectItem* item = getNode(event->pos());
    if (item == 0) return;

    if (m_leftMousePressed)
        item->setBrush(QBrush(m_activeColor,Qt::SolidPattern));
    if (m_rightMousePressed)
        item->setBrush(QBrush(m_inactiveColor,Qt::SolidPattern));

    int* state = getNodeState(event->pos());
    *state = m_leftMousePressed;

}

void GraphicsViewer::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
        m_leftMousePressed = false;
    if (event->button() == Qt::RightButton)
        m_rightMousePressed = false;
}

QGraphicsRectItem* GraphicsViewer::getNode(const QPoint& pos) {
    int x = pos.x();
    int y = pos.y();
    if (x <= 0 || x >= m_width*m_amountWidth || y <= 0 || y >= m_height*m_amountHeight)
        return 0;
    x = x/m_width;
    y = y/m_height;
    return m_grid[x][y];
}

int* GraphicsViewer::getNodeState(const QPoint& pos) {
    int x = pos.x();
    int y = pos.y();
    if (x <= 0 || x >= m_width*m_amountWidth || y <= 0 || y >= m_height*m_amountHeight)
        return 0;
    x = x/m_width;
    y = y/m_height;
    return &m_state[x][y];
}


