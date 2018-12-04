#include "centralwidget.h"
#include <QGraphicsRectItem>
#include "edge.h"
#include <QProcess>
#include <QFileDialog>
#include <QFile>
#include <QScreen>
#include <QProcess>
#include <QVector>
#include <QTextStream>
#include <QFile>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{

    m_view = new QGraphicsView(this);
    m_scene = new QGraphicsScene(0,0,1023,574);
    m_view->scale(1,-1);
    m_view->setScene(m_scene);
}

CentralWidget::~CentralWidget()
{
    delete m_view;
    delete m_scene;
}

void CentralWidget::deleteGraphs()
{
    for(auto g:m_graphs)
    {
        for(auto e:g->edgesVector())
        {
            m_scene->removeItem(e);
        }
        for(auto n:g->nodesVector())
        {
            m_scene->removeItem(n);
        }
    }
    m_graphs.remove(0,m_graphs.length());
}

void CentralWidget::setFileName(QString fileName)
{
    m_fileName = fileName;
}

void CentralWidget::readGraph(QString includes)
{
    QString str(includes);

// трансляция запрещенных в graphViz символов
    QString forbiddenChars = "+.!@$%^&()'/\\|<>";
    for(auto ch:forbiddenChars)
    {
        int unicodeKey = ch.unicode();
        str = str.replace(ch,"uni"+ QString::number(unicodeKey));
    }
    str = str.replace("---","--uni45");
    str = str.replace("--","-uni45");
    str = str.replace(QRegExp("-(?!uni45)"),"uni45");
    str = str.replace("-uni45","--");

    QByteArray ba1;
    ba1+=str;

// запись в файл для контроля при отладке
    QFile f1("C:\\Users\\USER\\Desktop\\test\\afterTranslation.txt");
    if(f1.open(QIODevice::WriteOnly)){
        f1.write(ba1);
    }
    f1.close();


// получение файла из graphViz
    QProcess p;
    p.start("dot -Tplain -Gratio=1 ");
    p.write(ba1);
    p.waitForBytesWritten();
    p.closeWriteChannel();
    p.waitForFinished();
    QString out(p.readAllStandardOutput());
    QString err(p.readAllStandardError());
    p.close();

// ретрансляция
    forbiddenChars += "-";

    for(auto ch:forbiddenChars)
    {
        int unicodeKey = ch.unicode();
        out = out.replace("uni"+ QString::number(unicodeKey),ch);
    }

// запись в файл для промежуточного контроля при отладке
    QFile f2("C:\\Users\\USER\\Desktop\\test\\afterGraphViz.txt");
    QByteArray ba2;
    ba2+=out;
    if(f2.open(QIODevice::WriteOnly))
    {
        f2.write(ba2);
    }
    f2.close();

// составление графа из полученных данных
    QStringList sl = out.split("\r\n");

    QStringList buff;

    for(int i = 0;i<sl.length();++i)
    {
        buff = sl[i].split(" ");

        if(buff[0]=="graph")
        {
            m_graphs.append(new Graph());
            double scale = buff[1].toDouble()*500/buff[2].toDouble();
            m_graphs.last()->setScale(scale);
            m_graphs.last()->setWidth(buff[2].toDouble()*scale);
            m_graphs.last()->setHeight(buff[3].toDouble()*scale);
        }
        if(buff[0]=="node")
        {
            Graph* g = m_graphs.last();
            double scale = g->scale();
            g->addNode(buff[1],new Node(buff[6],
                QPointF(buff[2].toDouble()*scale,buff[3].toDouble()*scale)));
            g->node(buff[1])->setWidth(buff[4].toDouble()*scale);
            g->node(buff[1])->setHeight(buff[5].toDouble()*scale);
        }
        if(buff[0]=="edge")
        {
            Graph* g = m_graphs.last();
            g->addEdge(new Edge(g->node(buff[1]),g->node(buff[2])));
        }
    }
}

void CentralWidget::plotGraphs()
{
    for(auto g:m_graphs)
    {
        for(auto e:g->edgesVector())
        {
            m_scene->addItem(e);
        }
        for(auto n:g->nodesVector())
        {
            m_scene->addItem(n);
        }

    }

}

QString CentralWidget::fileName()const
{
    return m_fileName;
}
