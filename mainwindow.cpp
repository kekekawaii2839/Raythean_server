#include "mainwindow.h"
#include "ui_mainwindow.h"

QTcpServer* server;
QTcpSocket* socket;
operation ss[144];
QString version="0.9.2";
int ss_time=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setVisible(false);
    for (int i = 0; i < 144; i++) {
        ss[i].get_information(i + 1);//获取每关的信息
        ss[i].get_pro();//计算每关每种材料的掉落概率
    }
    server=new QTcpServer;
    server->listen(QHostAddress::Any,2839);
    connect(server,SIGNAL(newConnection()),SLOT(ServerNewConnection()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString temp=QString::number(ss_time)+"#";
    temp+=QString::number(ss[ss_time].a[0])+" "+QString::number(ss[ss_time].a[1])+" "+QString::number(ss[ss_time].s)
            +" "+QString::number(ss[ss_time].san)+" "+QString::number(ss[ss_time].t)+" ";
    for(int i = 0; i < 2; i++){
        temp+=QString::number(ss[ss_time].main[i].k)+"+"+QString::number(ss[ss_time].main[i].level)+"+"
                +QString::number(ss[ss_time].main[i].pro)+" ";
    }
    for(int i = 0; i < 11; i++){
        temp+=QString::number(ss[ss_time].by_[i].k)+"+"+QString::number(ss[ss_time].by_[i].level)+"+"
                +QString::number(ss[ss_time].by_[i].pro)+" ";
    }
    temp+=QString::number(ss[ss_time].sp.k)+"+"+QString::number(ss[ss_time].sp.level)+"+"
            +QString::number(ss[ss_time].sp.pro);
    socket->write(temp.toLatin1());
    ss_time++;
}

void MainWindow::ServerNewConnection()
{
    //QMessageBox::information(NULL,"new!","a new connection!");
    ss_time=0;
    socket=server->nextPendingConnection();
    socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption,1024*100);
    ui->textBrowser->setText("new client ip:"+socket->peerAddress().toString());
    connect(socket,SIGNAL(readyRead()),this,SLOT(ServerReadData()));
    socket->write(version.toLatin1());
    //if(write!=0) QMessageBox::information(NULL,"success","check version successfully!");
}

void MainWindow::ServerReadData(){
    QString dat=socket->readAll();
    qDebug()<<"dat:"<<dat;
    ui->textBrowser->setText(dat);
    if(dat=="received"&&ss_time<144){
        on_pushButton_clicked();
    }
    else if(dat[0]=='d'&&dat[1]=='a'&&dat[2]=='t'&&dat[3]=='a'&&dat[4]=='#'){
        //客户端录入的数据
        QStringList list=dat.split("#");
        int which=list[1].toInt();
        QString temp=list[2];//没有叠加原本数据
        QFile file(QCoreApplication::applicationDirPath()+"/log.txt");
        file.open(QIODevice::ReadOnly);
        QTextStream logg(&file);
        QFile file_temp(QCoreApplication::applicationDirPath()+"temp.txt");
        file_temp.open(QIODevice::WriteOnly);
        QTextStream ttemp(&file_temp);
        QString line;
        for(int u = 0; u < 144; u++) {
            logg.readLineInto(&line,100);
            if(u!=which){
                ttemp<<line;
            }
            else{
                QStringList con=temp.split(" ");
                QStringList org=line.split(" ");
                QString fuck;
                for(int i = 0; i < 15; i++){
                    fuck+=QString::number(con[i].toInt()+org[i].toInt());//在这里叠加原数据
                    fuck+=" ";
                }
                ttemp<<fuck;
            }
            ttemp<<"\n";
        }
        logg.flush();
        ttemp.flush();
        file.close();
        file_temp.close();

        file.open(QIODevice::WriteOnly);
        QTextStream loggg(&file);
        file_temp.open(QIODevice::ReadOnly);
        QTextStream tttemp(&file_temp);
        for(int u = 0; u < 144; u++) {
            tttemp.readLineInto(&line,100);
            loggg<<line<<"\n";
        }
        loggg.flush();
        tttemp.flush();
        file.close();
        file_temp.close();

        for (int i = 0; i < 144; i++) {
            ss[i].get_information(i + 1);//获取每关的信息
            ss[i].get_pro();//计算每关每种材料的掉落概率
        }
    }
}
