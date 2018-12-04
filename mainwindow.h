#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "centralwidget.h"
#include <QToolBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();
private:
    CentralWidget* m_centralWidget;
    QToolBar* m_toolbar;
};

#endif // MAINWINDOW_H
