#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include "edge.h"
#include <QMap>

class Graph
{
public:
    Graph();
    void addNode(QString,Node*);
    Node* node(QString node);
    QMap<QString,Node*> nodesVector()const;
    QVector<Edge*> edgesVector()const;

    void addEdge(Edge*);
    void setWidth(double width);
    double width()const;
    void setHeight(double height);
    double height()const;
    void setScale(double scale);
    double scale()const;

private:
    QMap<QString,Node*> m_nodes;
    QVector<Edge*> m_edges;
    double m_width;
    double m_height;
    double m_scale;
    bool m_containsEdges;
    bool m_containsNodes;
};

#endif // GRAPH_H
