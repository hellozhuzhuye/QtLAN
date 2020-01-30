#ifndef FILECNTDLG_H
#define FILECNTDLG_H
#pragma execution_character_set("utf-8")
#include <QDialog>
#include <QFile>
#include <QFileInfo>
#include <QHostAddress> //网络IP地址类库
#include <QTcpSocket> //TCP套接口类库
#include <QTime>
class QTcpSocket; //客户端套接字类

namespace Ui {
class FileCntDialog;
}

class FileCntDialog : public QDialog {
    Q_OBJECT

public:
    explicit FileCntDialog(QWidget* parent = nullptr);
    ~FileCntDialog();
    void getSrvAddr(QHostAddress saddr); //获取服务器（发送端）IP
    void getLocPath(QString lpath); //获取本地文件保存路径
    void setFilePath();
    void setFileInfo(QString fname);

protected:
    void closeEvent(QCloseEvent*);

private slots:
    void createConnToSrv(); //连接到服务器

    void readChatMsg(); //读取服务器发来的文件数据

    void on_cntClosePushButton_clicked(); //“停止”按钮的单击事件过程

    void on_openFilePathPushButton_clicked();

    void on_openFilePushButton_clicked();

private:
    Ui::FileCntDialog* ui;
    QTcpSocket* myCntSocket; //客户端套接字指针
    QHostAddress mySrvAddr; //服务器地址
    qint16 mySrvPort; //服务器端口

    qint64 myTotalBytes; //总共要接收的字节数
    qint64 myRcvedBytes; //已接收的字节数
    QByteArray myInputBlock; //缓存一次收下的数据
    quint16 myBlockSize; //缓存块大小

    QFile* myLocPathFile; //待收文件对象指针
    QString myFileName; //待收文件名
    QString myFilePath; //接收文件保存路径
    qint64 myFileNameSize; //文件名大小
    QFileInfo* myFileInfo; //接收文件信息
    QTime mytime;
};

#endif // FILECNTDLG_H
