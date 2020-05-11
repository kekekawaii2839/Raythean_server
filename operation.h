#ifndef OPERATION_H
#define OPERATION_H

#include "material2.h"

class operation
{
public:
    operation();
    int a[2];//a[0]表示第几章 a[1]表示第几关
    int s;//表示是否为S关
    int san;//表示所需理智
    int t = 0;//总刷关次数
    material2 main[2];//常规掉落
    material2 by_[11];//额外物资
    material2 sp;//特殊掉落
    void get_information(int i) {//获取该关卡的具体信息 i表示第几个关（将S关排在每一章的最后）
        QFile file(QCoreApplication::applicationDirPath()+"/mission.txt");
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        QString line;
        for (int ii = 0; ii < i; ii++) {
            in.readLineInto(&line,100);
        }
        in.flush();
        file.close();
        QStringList list=line.split(" ");
        a[0]=list[0].toInt();
        a[1]=list[1].toInt();
        s=list[2].toInt();
        san=list[3].toInt();
        int f=4;
        for (int n = 0; n < 2; n++) {
            main[n].level=list[f].toInt();
            f++;
            main[n].k=list[f].toInt();
            f++;
            main[n].get_name();
        }
        for (int n = 0; n < 11 ; n++) {
            by_[n].level=list[f].toInt();
            f++;
            by_[n].k=list[f].toInt();
            f++;
            by_[n].get_name();
        }
        sp.level=list[30].toInt();
        sp.k=list[31].toInt();
        sp.get_name();
        return;
    }
    int seq() {//获取每关对应序号
        int res = 0;
        if (a[0] == 0) {
            res = a[1];
        }
        else if (a[0] == 1) {
            res = a[1] + 11;
        }
        else if (a[0] == 2) {
            if (s == false) {
                res = a[1] + 11 + 12;
            }
            else {
                res = a[1] + 11 + 12 + 10;
            }
        }
        else if (a[0] == 3) {
            if (s == false) {
                res = a[1] + 11 + 12 + 22;
            }
            else {
                res = a[1] + 11 + 12 + 22 + 8;
            }
        }
        else if (a[0] == 4) {
            if (s == false) {
                res = a[1] + 11 + 12 + 22 + 14;
            }
            else {
                res = a[1] + 11 + 12 + 22 + 14 + 10;
            }
        }
        else if (a[0] == 5) {
            if (s == false) {
                res = a[1] + 11 + 12 + 22 + 14 + 20;
            }
            else {
                res = a[1] + 11 + 12 + 22 + 14 + 20 + 11;
            }
        }
        else if (a[0] == 6) {
            if (s == false) {
                res = a[1] + 11 + 12 + 22 + 14 + 20 + 19;
            }
            else {
                res = a[1] + 11 + 12 + 22 + 14 + 20 + 19 + 18;
            }
        }
        else if (a[0] == 7) {
            if (s == false) {
                res = a[1] + 11 + 12 + 22 + 14 + 20 + 19 + 22;
            }
            else {
                res = a[1] + 11 + 12 + 22 + 14 + 20 + 19 + 22 + 20;
            }
        }
        return res;
    }
    void get_pro() {
        QFile file(QCoreApplication::applicationDirPath()+"/log.txt");
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        QString line;
        for (int u = 0; u < seq(); u++) {
            in.readLineInto(&line,100);
        }
        in.flush();
        file.close();
        if(line!=""){
            QStringList list=line.split(" ");
            for (int n = 0 ; n < 2 ; n++) {
                main[n].pro=list[n].toDouble();
            }
            for (int n = 0 ; n < 11 ; n++) {
                by_[n].pro=list[n+2].toDouble();
            }
            sp.pro=list[13].toDouble();
            t=list[14].toInt();
            /*if (t != 0) {
                main[0].pro /= t;
                main[1].pro /= t;
                by_[0].pro /= t;
                by_[1].pro /= t;
                by_[2].pro /= t;
                by_[3].pro /= t;
                by_[4].pro /= t;
                by_[5].pro /= t;
                by_[6].pro /= t;
                by_[7].pro /= t;
                by_[8].pro /= t;
                by_[9].pro /= t;
                by_[10].pro /= t;
                sp.pro /= t;
            }*///因为发送数据时的pro表示掉落数量而非掉落概率
        }
        return;
    }
    QString show(){
       QString res;
        if(s==1) res+="S";
        res+=QString::number(a[0])+"-"+QString::number(a[1])+":\n";
        res+="所需理智："+QString::number(san)+"\n";
        if(main[0].kind!=""){
            res+="常规掉落有：\n    ";
            res+=main[0].kind+"("+QString::number(main[0].pro*100)+"%)\n";
        }
        if(main[1].kind!=""){
            res+="    ";
            res+=main[1].kind+"("+QString::number(main[1].pro*100)+"%)\n";
        }
        if(by_[0].kind!=""){
            res+="额外物资可能有：\n";
            for(int i = 0 ;i < 11 ; i++){
                if(by_[i].kind!=""){
                    res+="    ";
                    res+=by_[i].kind+"("+QString::number(by_[i].pro*100)+"%)\n";
                }
            }
        }
        if(sp.kind!="") res+="特殊掉落有：\n    "+sp.kind+"("+QString::number(sp.pro*100)+"%)\n\n";
        else res+="\n";
        return res;
    }
};

#endif // OPERATION_H
