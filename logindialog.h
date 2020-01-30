#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "mainwindow.h"
#include <QDialog>
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();

private slots:
    void on_loginPushButton_clicked();
    void showMainWindow();

private:
    Ui::LoginDialog* ui;
    MainWindow* LANMainWindow;
};

#endif // LOGINDIALOG_H
