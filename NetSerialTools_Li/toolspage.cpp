#include "toolspage.h"
#include "ui_toolspage.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QComboBox>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

ToolsPage::ToolsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolsPage)
    , serial(new QSerialPort)
    , sendTimer(new QTimer)
    , server(new QTcpServer)
    , clientTcpSocket(new QTcpSocket)
    , clientUdpSocket(new QUdpSocket)
{
    ui->setupUi(this);
    this->setWindowTitle("串口网络工具");
    portInit();
    on_cbName_currentIndexChanged(ui->cbName->currentIndex());

    connect(serial, &QSerialPort::readyRead,
            this, &ToolsPage::serialReadyReadSlot);
    connect(sendTimer, &QTimer::timeout,
            this, &ToolsPage::sendTimerTimeoutSlot);
    connect(server, &QTcpServer::newConnection,
            this, &ToolsPage::serverNewConnectionSlot);
    connect(clientTcpSocket, &QTcpSocket::readyRead,
            this, &ToolsPage::socketReadyReadSlot);
    connect(clientTcpSocket, &QTcpSocket::disconnected,
            this, &ToolsPage::tcpSocketDisconnectedSlot);
    connect(clientUdpSocket, &QTcpSocket::readyRead,
            this, &ToolsPage::udpSocketReadyReadSlot);
}

ToolsPage::~ToolsPage()
{
    delete ui;
}

void ToolsPage::portInit()
{
    ui->cbName->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->cbName->addItem(info.portName());
    }
    ui->cbName->addItem("TCP Server");
    ui->cbName->addItem("TCP Client");
    ui->cbName->addItem("UDP");
}

void ToolsPage::serialReadyReadSlot()
{
    toPage(readData(serial));
}

void ToolsPage::sendTimerTimeoutSlot()
{
    on_btnSend_clicked();
}

void ToolsPage::on_cbName_currentIndexChanged(int index)
{
    if(index < 0)
        ui->stackedWidget->setCurrentIndex(0);
    int len = ui->cbName->count();
    if(len <= 0)
        ui->stackedWidget->setCurrentIndex(0);
    if(index >= len - 3){
        ui->stackedWidget->setCurrentIndex(1);
        if(index == len - 3){
            ui->btnNetStart->setText("侦听");
            ui->cbName->setEnabled(true);
            ui->leLocalIp->setEnabled(false);
            ui->leLocalPort->setEnabled(true);
            ui->lePeerIp->setEnabled(false);
            ui->lePeerPort->setEnabled(false);
            ui->btnNetStart->setEnabled(true);
            ui->btnNetStop->setEnabled(false);
        }
        else if(index == len - 2){//tcp cloent
            ui->btnNetStart->setText("连接");
            ui->cbName->setEnabled(true);
            ui->leLocalIp->setEnabled(false);
            ui->leLocalPort->setEnabled(false);
            ui->lePeerIp->setEnabled(true);
            ui->lePeerPort->setEnabled(true);
            ui->btnNetStart->setEnabled(true);
            ui->btnNetStop->setEnabled(false);
        }
        else
        {//udp
            ui->btnNetStart->setText("连接");
            ui->cbName->setEnabled(true);
            ui->leLocalIp->setEnabled(false);
            ui->leLocalPort->setEnabled(true);
            ui->lePeerIp->setEnabled(true);
            ui->lePeerPort->setEnabled(true);
            ui->btnNetStart->setEnabled(true);
            ui->btnNetStop->setEnabled(false);
        }
    }
    else
        ui->stackedWidget->setCurrentIndex(0);
}

void ToolsPage::on_btnOpenSerial_clicked()
{
    if(ui->btnOpenSerial->text() == "打开串口"){
        if(serial->isOpen())
            serial->close();
        serial->setPortName(ui->cbName->currentText());
        serial->setBaudRate(ui->cbBaudRate->currentText().toUInt());
        serial->setDataBits(
            static_cast<QSerialPort::DataBits>
                (ui->cbDataBit->currentIndex()
                 + QSerialPort::Data5));
        serial->setStopBits(
            static_cast<QSerialPort::StopBits>
                (ui->cbStopBit->currentIndex()
                 + QSerialPort::OneStop));
        //设置奇偶校验
        serial->setParity(QSerialPort::NoParity);
        //设置流量控制
        serial->setFlowControl(QSerialPort::NoFlowControl);
        bool ok = serial->open(QIODevice::ReadWrite);
        if(!ok)
        {
            QMessageBox::warning(
                this, "警告",
                "串口打卡失败！");
            return;
        }
        ui->btnOpenSerial->setText("关闭串口");
        ui->cbName->setEnabled(false);
        ui->cbBaudRate->setEnabled(false);
        ui->cbDataBit->setEnabled(false);
        ui->cbStopBit->setEnabled(false);
    }
    else{//关闭串口
        if(serial->isOpen())
            serial->close();
        ui->btnOpenSerial->setText("打开串口");
        ui->cbName->setEnabled(true);
        ui->cbBaudRate->setEnabled(true);
        ui->cbDataBit->setEnabled(true);
        ui->cbStopBit->setEnabled(true);
    }
}

void ToolsPage::on_btnSend_clicked()
{
    QString data = ui->teSendData->toPlainText();
    QByteArray baData;
    if(ui->cbHexSend->isChecked()){
        baData = QByteArray::fromHex(
                    data.toLatin1());
    }
    else{
        baData = data.toLocal8Bit();
        if(ui->cbAddReturn->isChecked()){//加回车
            baData.append('\r');
            baData.append('\n');
        }
    }
    if(baData.isEmpty())
    {
        QMessageBox::warning(
            this, "警告",
            "输入为空或HEX格式有问题！");
        return;
    }
    int len = ui->cbName->count();
    if(ui->cbName->currentIndex() >= len - 3)
    {
        //网络
        if(ui->cbName->currentIndex() == len - 3)
        {//tcp server
            if(serverConnectList.isEmpty()){
                QMessageBox::warning(
                    this, "警告",
                    "没有连接上的客户端");
                return;
            }
            for(int i = 0; i < serverConnectList.length(); i++)
            {
                serverConnectList.at(i)->write(baData);
            }
        }
        else if(ui->cbName->currentIndex() == len - 2)
        {//tcp client
            if(clientTcpSocket->state() !=
                    QTcpSocket::ConnectedState)
            {
                QMessageBox::warning(
                    this, "警告",
                    "未连接！");
                return;
            }
            clientTcpSocket->write(baData);
        }
        else
        {//udp
            QString ip = ui->lePeerIp->text();
            int port = ui->lePeerPort->text().toInt();
            if(ip.isEmpty() || port <= 0)
            {
                QMessageBox::warning(
                    this, "警告",
                    "ip端口输入有误");
                return;
            }
            clientUdpSocket->writeDatagram(baData,
                        QHostAddress(ip), port);
        }
    }
    else
    {
        //串口
        if(!serial->isOpen())
        {
            QMessageBox::warning(
                this, "警告",
                "串口未打开！");
            return;
        }
        serial->write(baData);
    }
    if(ui->cbAddTime->isChecked())
    {
        QString temp =
            QString("[%1]->:%2")
            .arg(QDateTime::currentDateTime()
                 .toString("yyyy-MM-dd hh:mm:ss"))
            .arg(data);
        ui->tbShow->append(temp);
    }
}

void ToolsPage::on_cbSendAtTime_clicked(bool checked)
{
    if(checked)
    {
        int time = ui->leTime->text().toInt();
        if(time <= 0)
        {
            QMessageBox::warning(
                this, "警告",
                "时间输入有误");
            return;
        }
        if(sendTimer->isActive())
            sendTimer->stop();
        sendTimer->start(time);
    }
    else
    {
        if(sendTimer->isActive())
            sendTimer->stop();
    }
}

void ToolsPage::on_btnNetStart_clicked()
{
    int index = ui->cbName->currentIndex();
    if(index == ui->cbName->count() - 3)
    {//tcp server
        int port = ui->leLocalPort->text().toInt();
        if(port <= 0)
        {
            QMessageBox::warning(this,
                "警告", "请输入要监听的端口");
            return;
        }
        if(server->isListening())
            server->close();
        //列表里面，我们也可以判断一下
        while(!serverConnectList.isEmpty())
        {

            QTcpSocket *socket = serverConnectList.at(0);
            serverConnectList.removeFirst();
            //强制终止
            socket->abort();
        }
        bool ok = server->listen(QHostAddress::Any,
                       port);
        if(!ok)
        {
            QMessageBox::warning(this,
                "警告", "端口被占用");
            return;
        }
        ui->cbName->setEnabled(false);
        ui->leLocalIp->setEnabled(false);
        ui->leLocalPort->setEnabled(false);
        ui->lePeerIp->setEnabled(false);
        ui->lePeerPort->setEnabled(false);
        ui->btnNetStart->setEnabled(false);
        ui->btnNetStop->setEnabled(true);
    }
    else if(index == ui->cbName->count() - 2)
    {//tcp client
        if(clientTcpSocket->state() ==
                QTcpSocket::ConnectedState)
        {
            clientTcpSocket->disconnectFromHost();
        }
        QString ip = ui->lePeerIp->text();
        int port = ui->lePeerPort->text().toInt();
        if(ip.isEmpty() || port <= 0)
        {
            QMessageBox::warning(this,
                "警告", "输入ip和端口！");
            return;
        }
        clientTcpSocket->connectToHost(ip, port);
        bool ok = clientTcpSocket->waitForConnected(1000);
        if(!ok)
        {
            QMessageBox::warning(this,
                "警告", "连接失败");
            return;
        }
        ui->cbName->setEnabled(false);
        ui->leLocalIp->setEnabled(false);
        ui->leLocalPort->setEnabled(false);
        ui->lePeerIp->setEnabled(false);
        ui->lePeerPort->setEnabled(false);
        ui->btnNetStart->setEnabled(false);
        ui->btnNetStop->setEnabled(true);
    }
    else
    {//udp
        int port = ui->leLocalPort->text().toInt();
        if(port <= 0)
        {
            QMessageBox::warning(this,
                "警告", "请输入要监听的端口");
            return;
        }
        bool ok = clientUdpSocket->bind(QHostAddress::Any,
                              port);
        if(!ok)
        {
            QMessageBox::warning(this,
                "警告", "端口被占用");
            return;
        }
        ui->cbName->setEnabled(false);
        ui->leLocalIp->setEnabled(false);
        ui->leLocalPort->setEnabled(false);
        ui->lePeerIp->setEnabled(true);
        ui->lePeerPort->setEnabled(true);
        ui->btnNetStart->setEnabled(false);
        ui->btnNetStop->setEnabled(true);
    }
}

void ToolsPage::on_btnNetStop_clicked()
{
    int index = ui->cbName->currentIndex();
    if(index == ui->cbName->count() - 3)
    {//tcp server
        if(server->isListening())
            server->close();
        while(!serverConnectList.isEmpty())
        {
            QTcpSocket *socket = serverConnectList.at(0);
            serverConnectList.removeFirst();
            socket->abort();
        }
        ui->cbName->setEnabled(true);
        ui->leLocalIp->setEnabled(false);
        ui->leLocalPort->setEnabled(true);
        ui->lePeerIp->setEnabled(false);
        ui->lePeerPort->setEnabled(false);
        ui->btnNetStart->setEnabled(true);
        ui->btnNetStop->setEnabled(false);
    }
    else if(index == ui->cbName->count() - 2)
    {//tcp client
        if(clientTcpSocket->state() ==
                QTcpSocket::ConnectedState)
        {
            clientTcpSocket->disconnectFromHost();
        }
        ui->cbName->setEnabled(true);
        ui->leLocalIp->setEnabled(false);
        ui->leLocalPort->setEnabled(false);
        ui->lePeerIp->setEnabled(true);
        ui->lePeerPort->setEnabled(true);
        ui->btnNetStart->setEnabled(true);
        ui->btnNetStop->setEnabled(false);
    }
    else
    {
        clientUdpSocket->abort();
        ui->cbName->setEnabled(true);
        ui->leLocalIp->setEnabled(false);
        ui->leLocalPort->setEnabled(true);
        ui->lePeerIp->setEnabled(true);
        ui->lePeerPort->setEnabled(true);
        ui->btnNetStart->setEnabled(true);
        ui->btnNetStop->setEnabled(false);
    }
}

void ToolsPage::serverNewConnectionSlot()
{
    //连接发送与接收
    QTcpSocket *socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead,
            this, &ToolsPage::socketReadyReadSlot);
    connect(socket, &QTcpSocket::disconnected,
            this, &ToolsPage::socketDisconnectedSlot);
    serverConnectList.append(socket);
}

void ToolsPage::socketReadyReadSlot()
{

    QTcpSocket *socket = qobject_cast<QTcpSocket *>
            (sender());
    toPage(readData(socket));
}

void ToolsPage::socketDisconnectedSlot()
{
    //断开槽 记得qobject_cast；
    QTcpSocket *socket = qobject_cast<QTcpSocket *>
            (sender());
    serverConnectList.removeOne(socket);
}

void ToolsPage::udpSocketReadyReadSlot()
{
    char buff[2048];
    qint64 len = clientUdpSocket->readDatagram(buff, 2048);
    QByteArray baData;
    baData.append(buff, len);
    toPage(baData);
}

void ToolsPage::tcpSocketDisconnectedSlot()
{
    ui->cbName->setEnabled(true);
    ui->leLocalIp->setEnabled(false);
    ui->leLocalPort->setEnabled(false);
    ui->lePeerIp->setEnabled(true);
    ui->lePeerPort->setEnabled(true);
    ui->btnNetStart->setEnabled(true);
    ui->btnNetStop->setEnabled(false);
}

QByteArray ToolsPage::readData(QIODevice *io)
{
    //讲多态的适合演讲过，添加一个内部函数用来接收、QIODevice *io显示到界面上
    return io->readAll();
}

void ToolsPage::toPage(QByteArray baData)
{
    QString data;
    if(ui->cbHexShow->isChecked())//hex
    {
        data = baData.toHex(' ').toUpper();
    }
    else
    {
        data = QString::fromLocal8Bit(baData);
    }
    QString temp;
    if(ui->cbAddTime->isChecked())//时间戳
    {
        temp = QString("[%1]<-:%2")
            .arg(QDateTime::currentDateTime()
                 .toString("yyyy-MM-dd hh:mm:ss"))
            .arg(data);
        ui->tbShow->append(temp);
    }
    else
    {
        temp = ui->tbShow->toPlainText() + data;
        ui->tbShow->setPlainText(temp);
    }
}









void ToolsPage::on_btnClienShow_clicked()
{
    ui->tbShow->clear();
}

void ToolsPage::on_cbName_activated(const QString &arg1)
{

}
