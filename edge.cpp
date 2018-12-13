#include "edge.h"
#include <QGraphicsLineItem>
#include <QGraphicsScene>

Edge::Edge(Node* node1,Node* node2)
{
    m_node1 = node1;
    m_node2 = node2;

    setPen(QPen(Qt::black,2));
    qreal x1 = m_node1->pos().rx();
    qreal y1 = m_node1->pos().ry();
    qreal x2 = m_node2->pos().rx();
    qreal y2 = m_node2->pos().ry();
    setLine(x1,y1,x2,y2);

    connect(m_node1,SIGNAL(xChanged()),
            this,SLOT(anyNodeIsMoved()));
    connect(m_node1,SIGNAL(yChanged()),
            this,SLOT(anyNodeIsMoved()));
    connect(m_node2,SIGNAL(xChanged()),
            this,SLOT(anyNodeIsMoved()));
    connect(m_node2,SIGNAL(yChanged()),
            this,SLOT(anyNodeIsMoved()));
}

void Edge::anyNodeIsMoved()
{
    qreal x1 = m_node1->pos().rx();
    qreal y1 = m_node1->pos().ry();
    qreal x2 = m_node2->pos().rx();
    qreal y2 = m_node2->pos().ry();

    setLine(x1,y1,x2,y2);
}

void Edge::setNode1(Node* node1)
{
    m_node1 = node1;
}

void Edge::setNode2(Node* node2)
{
    m_node2 = node2;
}

Node* Edge::node1()const
{
    return m_node1;
}

Node* Edge::node2()const
{
    return m_node2;
}
