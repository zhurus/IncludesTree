#ifndef NODE_H
#define NODE_H
#include <QGraphicsObject>

    class Node : public QGraphicsObject
{
    Q_OBJECT
public:
    Node();
    Node(QString& nodeName, QPointF position);
    ~Node();

    QString nodeName()const;
    void setNodeName(QString nodeName);
    void setWidth(double width);
    void setHeight(double height);
    double width()const;
    double height()const;
    QPointF initialPosition()const;

private:
    QRectF boundingRect()const;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* options,QWidget* widget);
    QPointF m_initialPosition;
    QString m_nodeName;
    double m_width;
    double m_height;
};

#endif // NODE_H
