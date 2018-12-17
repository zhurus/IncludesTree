#include "mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>

#include <QMessageBox>

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
    QString fileToParse = QFileDialog::getOpenFileName(
        this,QString("Choose file of graph"));
    QFileInfo fi(fileToParse);
    try
    {
        if(!fi.exists()&&fi.fileName()!="")
        {
            throw wrongFile();
        }
        if(fi.fileName()=="")
        {
            throw noFileChosen();
        }
        m_centralWidget->deleteGraphs();

        m_centralWidget->setFile(fi);

        FileHandler fh(m_centralWidget->file());
        QString includes = fh.toGraphviz();

        m_centralWidget->formGraph(includes);
        m_centralWidget->plotGraphs();

    }
    catch(wrongFile)
    {
       QString errMsg("Error: file doesn't match the reqiurements");
       showErrorMessage(errMsg);
       changeStatusBarMessage(errMsg);
    }
    catch(noFileChosen)
    {
        changeStatusBarMessage("File is not chosen. Please choose the file.");
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

void MainWindow::showErrorMessage(QString error)
{
    QMessageBox mb;
    mb.critical(nullptr,"Error",error);
    mb.setFixedSize(500,200);
}

