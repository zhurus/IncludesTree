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
#include <QVBoxLayout>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    layout->addWidget(
        m_view = new QGraphicsView(this));

    m_scene = new QGraphicsScene(0,0,1500,550);

    m_view->setScene(m_scene);
    m_view->scale(1,-1);
    m_graph = Graph();

    connect(this,SIGNAL(sendStatusMessage(QString)),
        this->parent(),
        SLOT(changeStatusBarMessage(QString)));
    connect(this,SIGNAL(showErrorMessage(QString)),
        this->parent(),
        SLOT(showErrorMessage(QString)));
}

void CentralWidget::deleteGraphs()
{
    emit sendStatusMessage("Delete graphs...");

    m_graph = Graph();
    m_scene->clear();

    emit sendStatusMessage("Output area clearence completed");
}

void CentralWidget::setFile(QFileInfo file)
{
    m_file = file;
}

void CentralWidget::formGraph(QString includes)
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
//    p.start("dot -Tplain -Gratio=1 ");
    p.start("dot -Tplain -Gfontsize=12 -Gratio=" +
        QString().number(m_scene->height()/m_scene->width())+" ");
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

    m_fromGraphViz = out;
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
            double scale = buff[1].toDouble()*m_scene->width()/buff[2].toDouble();
            m_graph.setScale(scale);
            m_graph.setWidth(buff[2].toDouble()*scale);
            m_graph.setHeight(buff[3].toDouble()*scale);
        }
        if(buff[0]=="node")
        {
            double scale = m_graph.scale();
            m_graph.addNode(buff[1],new Node(buff[6],
                QPointF(buff[2].toDouble()*scale,buff[3].toDouble()*scale)));
            m_graph.node(buff[1])->setWidth(buff[4].toDouble()*scale);
            m_graph.node(buff[1])->setHeight(buff[5].toDouble()*scale);
        }
        if(buff[0]=="edge")
        {
            m_graph.addEdge(new Edge(m_graph.node(buff[1]),
                m_graph.node(buff[2])));
        }
    }
}

void CentralWidget::plotGraphs()
{

    for(auto e:m_graph.edgesVector())
    {
        m_scene->addItem(e);
    }
    for(auto n:m_graph.nodesVector())
    {
        m_scene->addItem(n);
    }

    emit sendStatusMessage("Graph has been plotted");
}

QFileInfo CentralWidget::file()const
{
    return m_file;
}

QString CentralWidget::fromGraphviz()const
{
    return m_fromGraphViz;
}

void CentralWidget::onInitialState()
{
    for(auto n:m_graph.nodesVector())
    {
        n->setPos(n->initialPosition());
    }
}
