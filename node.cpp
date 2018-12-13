#include "node.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QFontMetrics>

Node::Node()
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

Node::Node(QString& nodeName, QPointF position)
{
    m_nodeName = nodeName;
    m_initialPosition = position;
    setPos(position.rx(),position.ry());
    setFlag(QGraphicsItem::ItemIsMovable);
}

Node::~Node(){}

QRectF Node::boundingRect()const
{
    return QRectF(-m_width/2-0.5,-m_height/2-0.5,m_width+1,m_height+1);
}

void Node::paint(QPainter* painter,
                     const QStyleOptionGraphicsItem* options,QWidget* widget)
{

    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(Qt::green);
    painter->drawRect(-m_width/2,-m_height/2,m_width,m_height);

    QFontMetrics fm(painter->font());
    painter->setFont(QFont("Times New Roman",12));
    int textWidth = fm.width(m_nodeName);
    int textHeight = painter->font().pixelSize();
    painter->scale(1,-1);
    if(textHeight+4<m_height || textWidth<m_width)
    {
        painter->drawText(QPointF(-textWidth/2,-textHeight+2),m_nodeName);
    }
    setToolTip(m_nodeName);

    Q_UNUSED(options);
    Q_UNUSED(widget);
}

void Node::setWidth(double width)
{
    m_width = width;
}

void Node::setHeight(double height)
{
    m_height = height;
}

double Node::width()const
{
    return m_width;
}

double Node::height()const
{
    return m_height;
}

QPointF Node::initialPosition()const
{
    return m_initialPosition;
}
