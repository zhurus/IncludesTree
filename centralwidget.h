#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include "graph.h"
#include <QFileInfo>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
    void deleteGraphs();
    void formGraph(QString);
    void setFile(QFileInfo);
    QFileInfo file()const;
    void plotGraphs();
    QString fromGraphviz()const;
    void onInitialState();

signals:
    void sendStatusMessage(QString message);
private:
    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
    QFileInfo m_file;
    Graph m_graph;
    QString m_fromGraphViz;
};

#endif // CENTRALWIDGET_H
