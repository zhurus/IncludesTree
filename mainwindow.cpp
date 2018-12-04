#include "mainwindow.h"
#include <QFileDialog>
#include "filehandler.h"
#include <iostream>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    showMaximized();
    m_centralWidget = new CentralWidget;
    setCentralWidget(m_centralWidget);
    m_toolbar = new QToolBar;

    QAction* open = new QAction;
    m_toolbar->addAction(open);
    open->setIcon(QIcon(":/topToolbar/open"));
    connect(open,SIGNAL(triggered()),this,SLOT(open()));

    addToolBar(Qt::TopToolBarArea,m_toolbar);
}

MainWindow::~MainWindow()
{
    delete m_centralWidget;
}

void MainWindow::open()
{
    QString fileToParse = "C:\\Users\\USER\\Desktop\\test\\main.cpp";
//    QString fileToParse = QFileDialog::getOpenFileName(
//        this,QString("Choose file of graph"));

    m_centralWidget->deleteGraphs();

    m_centralWidget->setFileName(fileToParse.replace("/","\\"));

    FileHandler fh(m_centralWidget->fileName());
    QString includes = fh.toGraphviz();

    m_centralWidget->readGraph(includes);
    m_centralWidget->plotGraphs();

}

