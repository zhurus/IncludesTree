#include "graph.h"

Graph::Graph()
{

}

void Graph::addNode(QString nodeName,Node* node)
{
    m_nodes[nodeName] = node;
}

Node* Graph::node(QString node)
{
    return m_nodes[node];
}

void Graph::addEdge(Edge* edge)
{
    m_edges.append(edge);
}

void Graph::setWidth(double width)
{
    m_width = width;
}

void Graph::setHeight(double height)
{
    m_height = height;
}

double Graph::width()const
{
    return m_width;
}

double Graph::height()const
{
    return m_height;
}

void Graph::setScale(double scale)
{
    m_scale = scale;
}

double Graph::scale()const
{
    return m_scale;
}

QMap<QString,Node*> Graph::nodesVector()const
{
    return m_nodes;
}

QVector<Edge*> Graph::edgesVector()const
{
    return m_edges;
}
