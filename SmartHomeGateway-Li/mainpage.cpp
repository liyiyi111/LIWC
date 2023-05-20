#include "mainpage.h"
#include "ui_mainpage.h"
#include "zigbeedriver.h"
#include "zigbeeprotocol.h"
#include <QMessageBox>
#include <QByteArray>
#include <QComboBox>
#include <QColorDialog>

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    ui->cbPortName->addItems(ZigbeeDriver::getObject()->getSerialPortList());
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::on_btnOpenSerial_clicked()
{
    if(ui->btnOpenSerial->text() == "打开串口"){
        if(!ZigbeeDriver::getObject()->openSerialPort(ui->cbPortName->currentText(),ui->cbBaudRate->currentText().toUInt()))
        {
            QMessageBox::warning(this,
                                 "警告",
                                 "抱歉串口没打开");
        }
        else{
            ui->btnOpenSerial->setText("关闭串口");
        }


    }
    else if(ui->btnOpenSerial->text() == "关闭串口"){
        ZigbeeDriver::getObject()->closeSerialPort();
        ui->btnOpenSerial->setText("打开串口");
    }



}

void MainPage::on_btnSend_clicked()
{
    QString data = ui->leText->text();
    QByteArray Data;
    Data = data.toLocal8Bit();
    if(!ZigbeeDriver::getObject()->sendToSerialPort(Data))
    {
        QMessageBox::warning(this,
                             "警告",
                             "发送失败");
    }
}

void MainPage::on_hsLight3_sliderReleased()
{
    ZigbeeProtocol::getObject()
            ->openLight3(ui->hsLight3->value());
}

void MainPage::on_hsLight1_sliderReleased()
{
    ZigbeeProtocol::getObject()
            ->openLight1(ui->hsLight1->value());
}

void MainPage::on_hsLight2_sliderReleased()
{
    ZigbeeProtocol::getObject()
            ->openLight2(ui->hsLight2->value());
}

void MainPage::on_hsLight4_sliderReleased()
{
    ZigbeeProtocol::getObject()
            ->openLight4(ui->hsLight4->value());
}

void MainPage::on_btnAlarmOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->alarmControl(1);
}

void MainPage::on_btnAlarmClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->alarmControl(2);
}

void MainPage::on_btnAlarmLedOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->alarmLedControl(1);
}

void MainPage::on_btnAlarmLedClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->alarmLedControl(2);
}

void MainPage::on_btnSteerengineOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->steerengineControl(1);
}

void MainPage::on_btnSteerengineClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->steerengineControl(2);
}

void MainPage::on_btnStepmotorOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->stepmotorControl(1);
}

void MainPage::on_btnStepmotorClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->stepmotorControl(2);
}

void MainPage::on_btnFanOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->fanControl(1);
}

void MainPage::on_btnFanClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->fanControl(2);
}

void MainPage::on_btnRelay1Open_clicked()
{
    ZigbeeProtocol::getObject()
            ->relay1Control(1);
}

void MainPage::on_btnRelay1Close_clicked()
{
    ZigbeeProtocol::getObject()
            ->relay1Control(2);
}

void MainPage::on_btnRelay2Open_clicked()
{
    ZigbeeProtocol::getObject()
            ->relay2Control(1);
}

void MainPage::on_btnRelay2Close_clicked()
{
    ZigbeeProtocol::getObject()
            ->relay2Control(2);
}

void MainPage::on_btnLockOpen_clicked()
{
    ZigbeeProtocol::getObject()
            ->lockControl(1);
}

void MainPage::on_btnLockClose_clicked()
{
    ZigbeeProtocol::getObject()
            ->lockControl(2);
}

void MainPage::on_btnColor_clicked()
{
    auto color = QColorDialog::getColor(Qt::black,this,"颜色");
    ZigbeeProtocol::getObject()
            ->openRGBLight(color);
}
