#ifndef EDGE_H
#define EDGE_H
#include "node.h"
#include <QGraphicsLineItem>

class Edge: public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    Edge(Node* node1, Node* node2);
    ~Edge();

    void setNode1(Node*);
    void setNode2(Node*);
    Node* node1()const;
    Node* node2()const;

public slots:
    void anyNodeIsMoved();
private:
    Node* m_node1;
    Node* m_node2;
};

#endif // EDGE_H
