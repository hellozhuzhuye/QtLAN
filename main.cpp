#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <logindialog.h>
int main(int argc, char* argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QApplication a(argc, argv);

    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    LoginDialog ld;
    ld.show();
    //    MainWindow w;
    //    w.show();
    //    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    //    QTextCodec::setCodecForTr(codec);

    return a.exec();
}
