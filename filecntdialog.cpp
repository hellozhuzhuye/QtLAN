#include "filecntdialog.h"
#include "ui_filecntdialog.h"
#include <QDesktopServices>
#include <QFileInfo>
#include <QUrl>
FileCntDialog::FileCntDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::FileCntDialog)
{
    ui->setupUi(this);
    myCntSocket = new QTcpSocket(this);
    mySrvPort = 5555;
    connect(myCntSocket, SIGNAL(readyRead()), this, SLOT(readChatMsg()));
    myFileNameSize = 0;
    myTotalBytes = 0;
    myRcvedBytes = 0;
}

FileCntDialog::~FileCntDialog()
{
    delete ui;
}

void FileCntDialog::createConnToSrv()
{
    myBlockSize = 0;
    myCntSocket->abort();
    myCntSocket->connectToHost(mySrvAddr, mySrvPort);
    mytime.start();
}

void FileCntDialog::readChatMsg()
{
    QDataStream in(myCntSocket);
    in.setVersion(QDataStream::Qt_5_11);
    float usedTime = mytime.elapsed();
    if (myRcvedBytes <= sizeof(qint64) * 2) {
        if ((myCntSocket->bytesAvailable() >= sizeof(qint64) * 2) && (myFileNameSize == 0)) {
            in >> myTotalBytes >> myFileNameSize;
            myRcvedBytes += sizeof(qint64) * 2;
        }
        if ((myCntSocket->bytesAvailable() >= myFileNameSize) && (myFileNameSize != 0)) {
            in >> myFileName;
            myRcvedBytes += myFileNameSize;
            myLocPathFile->open(QFile::WriteOnly);
            ui->rfileNameLineEdit->setText(myFileName);
            ui->rfilePathLineEdit->setText(myFilePath);
        } else {
            return;
        }
    }
    if (myRcvedBytes < myTotalBytes) {
        myRcvedBytes += myCntSocket->bytesAvailable();
        myInputBlock = myCntSocket->readAll();
        myLocPathFile->write(myInputBlock);
        myInputBlock.resize(0);
    }
    ui->recvProgressBar->setMaximum(myTotalBytes);
    ui->recvProgressBar->setValue(myRcvedBytes);
    double transpeed = myRcvedBytes / usedTime;
    ui->rfileSizeLineEdit->setText(tr("%1").arg(myTotalBytes / (1024 * 1024)) + " MB"); //填写文件大小栏
    ui->recvSizeLineEdit->setText(tr("%1").arg(myRcvedBytes / (1024 * 1024)) + " MB"); //填写已接收栏
    ui->rateLabel->setText(tr("%1").arg(transpeed * 1000 / (1024 * 1024), 0, 'f', 2) + QString(" MB/秒")); //计算并显示传输速率
    if (myRcvedBytes == myTotalBytes) {
        myLocPathFile->close();
        myCntSocket->close();
        ui->rateLabel->setText(QString("接收完毕！"));
    }
}

void FileCntDialog::on_cntClosePushButton_clicked()
{
    myCntSocket->abort();
    myLocPathFile->close();
    close();
}

void FileCntDialog::closeEvent(QCloseEvent*)
{
    on_cntClosePushButton_clicked();
}

void FileCntDialog::getLocPath(QString lpath)
{
    myLocPathFile = new QFile(lpath);
}
void FileCntDialog::setFileInfo(QString fname)
{
    myFileInfo = new QFileInfo(fname);
}
void FileCntDialog::setFilePath()
{
    myFilePath = myFileInfo->absolutePath();
}
void FileCntDialog::getSrvAddr(QHostAddress saddr)
{
    mySrvAddr = saddr;
    createConnToSrv();
}

void FileCntDialog::on_openFilePathPushButton_clicked()
{

    QDesktopServices::openUrl(QUrl(myFilePath));
}

void FileCntDialog::on_openFilePushButton_clicked()
{

    QString fullpath = myFilePath + '/' + myFileName;
    QDesktopServices::openUrl(QUrl(fullpath));
}
