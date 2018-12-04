#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include "graph.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget();
    void deleteGraphs();
    void readGraph(QString);
    void setFileName(QString);
    QString fileName()const;
    void plotGraphs();
private:
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
    QString m_fileName;
    QVector <Graph*> m_graphs;
};

#endif // CENTRALWIDGET_H
