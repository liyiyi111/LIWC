#ifndef TOOLSPAGE_H
#define TOOLSPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ToolsPage; }
QT_END_NAMESPACE
class QSerialPort;
class QTimer;
class QTcpServer;
class QTcpSocket;
class QUdpSocket;
class ToolsPage : public QWidget
{
    Q_OBJECT

public:
    ToolsPage(QWidget *parent = nullptr);
    ~ToolsPage();

protected:
    //初始化串口
    void portInit();

protected slots:
    void serialReadyReadSlot();
    void sendTimerTimeoutSlot();
    void serverNewConnectionSlot();
    void socketReadyReadSlot();
    void socketDisconnectedSlot();
    void udpSocketReadyReadSlot();
    void tcpSocketDisconnectedSlot();

private slots:
    void on_cbName_currentIndexChanged(int index);

    void on_btnOpenSerial_clicked();

    void on_btnSend_clicked();

    void on_cbSendAtTime_clicked(bool checked);

    void on_btnNetStart_clicked();

    void on_btnNetStop_clicked();

    void on_btnClienShow_clicked();

    void on_cbName_activated(const QString &arg1);

private:
    QByteArray readData(QIODevice *io);
    void toPage(QByteArray data);

    Ui::ToolsPage *ui;
    QSerialPort *serial;
    QTimer *sendTimer;
    QTcpServer *server;
    QList<QTcpSocket *> serverConnectList;

    QTcpSocket *clientTcpSocket;
    QUdpSocket *clientUdpSocket;
};
#endif // TOOLSPAGE_H
