#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/qtcpserver.h>
#include <QTcpSocket>
#include "qdebug.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <qfiledevice.h>
#include <QApplication>
#include "operation.h"

extern operation ss[144];

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void ServerNewConnection();

    void ServerReadData();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
