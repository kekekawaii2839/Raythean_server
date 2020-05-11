#ifndef MATERIAL2_H
#define MATERIAL2_H

#include <QFile>
#include <QWidget>
#include <QTextStream>
#include <QDebug>
#include <qdebug.h>
#include <qfiledevice.h>
#include <QMessageBox>
#include <QApplication>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/qtcpsocket.h>
#include <QtNetwork>

class material2
{
public:
    int k, level;//材料种类
    double pro = 0;//掉落概率
    QString kind;
    material2();
    void get_name(){
        if (k == -1 || level == -1) {
            kind = "";
            return;
        }
        int c = 0, d = 0;
        QFile file(QCoreApplication::applicationDirPath()+"/material.txt");
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        QString line;
        for (int p = 0; p < 51; p++) {
            in.readLineInto(&line,100);
            QStringList list=line.split(" ");
            c=list[0].toInt();
            d=list[1].toInt();
            if (level == c && k == d) {
                kind=list[2];
                in.flush();
                file.close();
                break;
            }
        }
        in.flush();
        file.close();
        return;
    }
};

#endif // MATERIAL2_H
