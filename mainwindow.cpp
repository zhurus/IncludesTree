#include "mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    showMaximized();
    m_centralWidget = new CentralWidget(this);
    m_centralWidget->adjustSize();
    setCentralWidget(m_centralWidget);

    m_toolbar = new QToolBar(this);

    QAction* open = new QAction(m_toolbar);
    QAction* home = new QAction(m_toolbar);
    m_toolbar->addAction(open);
    m_toolbar->addAction(home);
    open->setIcon(QIcon(":/topToolbar/open"));
    open->setToolTip("Choose the file");
    home->setToolTip("Return initial state");
    home->setIcon(QIcon(":/topToolbar/home"));

    connect(open,SIGNAL(triggered()),this,SLOT(open()));
    connect(home,SIGNAL(triggered()),this,SLOT(home()));
    addToolBar(Qt::TopToolBarArea,m_toolbar);

    m_statusmessage = new QLabel("Choose file containing main function");
    statusBar()->addWidget(m_statusmessage);

}

MainWindow::~MainWindow()
{
    delete m_centralWidget;
}

void MainWindow::open()
{
//    QString fileToParse = "C:\\Users\\USER\\Desktop\\test\\main.cpp";
    QString fileToParse = QFileDialog::getOpenFileName(
        this,QString("Choose file of graph"));
    QFileInfo fi(fileToParse);
    try
    {
        if(!fi.exists())
        {
            throw wrongFile();
        }
        m_centralWidget->deleteGraphs();

        m_centralWidget->setFile(fi);

        FileHandler fh(m_centralWidget->file());
        QString includes = fh.toGraphviz();

        m_centralWidget->formGraph(includes);
        m_centralWidget->plotGraphs();

    }
    catch(MainWindow::wrongFile)
    {
        QString errMsg("Error: file doesn't match the reqiurements");
        emit changeStatusBarMessage(errMsg);
    }

}

void MainWindow::home()
{
    m_centralWidget->onInitialState();
}

void MainWindow::changeStatusBarMessage(QString message)
{
    m_statusmessage->setText(message);
}
