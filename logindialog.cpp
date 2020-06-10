#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->usrLineEdit->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginPushButton_clicked()
{
    showMainWindow();
}

void LoginDialog::showMainWindow()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //    if (QSqlDatabase::contains("qt_sql_default_connection"))
    //        db = QSqlDatabase::database("qt_sql_default_connection");
    //    else
    //        db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1"); //设置数据库主机名
    db.setDatabaseName("test"); //设置数据库名
    db.setUserName("root"); //设置数据库用户名
    db.setPassword("5246"); //设置数据库密码
    db.open(); //打开连接

    QString uname = ui->usrLineEdit->text();
    QString upwd = ui->pwdLineEdit->text();
    QSqlQuery query;

    query.prepare("select * from UserInfoTest where User_Name=:name and User_Password=:pwd");
    query.bindValue(":pwd", upwd);
    query.bindValue(":name", uname);
    query.exec();

    if (query.first()) {
        QMessageBox::information(this, "Welcome", "Login successfully!!!", QMessageBox::Yes);
        this->close();
        LANMainWindow = new MainWindow(0, uname);
        LANMainWindow->show();
    }

    else {
        QMessageBox::information(this, "Error", "Wrong user name or password!!!", QMessageBox::Yes);
    }
}
