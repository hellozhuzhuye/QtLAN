#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")
#include <QDateTime> //时间日期库
#include <QFile> //系统文件类库
#include <QFileDialog> //文件对话框库
#include <QMainWindow>
#include <QMessageBox>
#include <QNetworkInterface> //网络（IP地址）接口类库
#include <QUdpSocket> //使用UDP套接口的类库
#include <filecntdialog.h>
#include <filesrvdialog.h>
class FileSrvDialog;

namespace Ui {
class MainWindow;
}

enum ChatMsgType { ChatMsg,
    OnLine,
    OffLine,
    SfileName,
    RefFile };

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent, QString uname);
    ~MainWindow();
    void initMainWindow(); //窗口初始化方法
    void onLine(QString name, QString time); //新用户上线方法
    void offLine(QString name, QString time); //用户离线方法
    void sendChatMsg(ChatMsgType msgType, QString rmtName = ""); //发送UDP消息
    QString getLocHostIp(); //获取本端的IP地址
    QString getLocChatMsg(); //获取本端的聊天信息内容
    void recvFileName(QString name, QString hostip, QString rmtname, QString filename);

protected:
    void closeEvent(QCloseEvent* event); //重写关闭窗口方法以便发送通知离线消息

private slots:
    void on_sendPushButton_clicked(); //“发送”按钮的单击事件方法

    void recvAndProcessChatMsg(); //接收并处理UDP数据报

    void on_searchPushButton_clicked(); //搜索线上所有用户

    void getSfileName(QString);

    void on_transPushButton_clicked();

private:
    Ui::MainWindow* ui;
    QString myname = ""; //本端当前的用户名
    QUdpSocket* myUdpSocket; //UDP套接口指针
    quint16 myUdpPort; //UDP端口号

    QString myFileName;
    FileSrvDialog* myfsrv;
};

#endif // MAINWINDOW_H
