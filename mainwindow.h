#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "centralwidget.h"
#include <QToolBar>
#include "filehandler.h"
#include <QStatusBar>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


    class wrongFile{};
private slots:
    void open();
    void home();
    void changeStatusBarMessage(QString message);
private:
    CentralWidget* m_centralWidget;
    QToolBar* m_toolbar;
    QLabel* m_statusmessage;
};

#endif // MAINWINDOW_H
