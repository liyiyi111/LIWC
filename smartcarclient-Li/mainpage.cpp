#include "networkexec.h"
#include "mainpage.h"
#include "ui_mainpage.h"
#include <QMessageBox>
#include "configexec.h"

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
    this->setWindowTitle("智慧交通");
    this->setWindowIcon(QIcon(":/Image/its.ico"));
    NetworkExec *exec = NetworkExec::getObject();
    connect(exec, &NetworkExec::carLightState,
            this, &MainPage::carLightStateSlot);
    connect(exec, &NetworkExec::carAlarmLightState,
            this, &MainPage::carAlarmLightStateSlot);
    connect(exec, &NetworkExec::carLockState,
            this, &MainPage::carLockStateSlot);
    connect(exec, &NetworkExec::carStartState,
            this, &MainPage::carStartStateSlot);
    connect(exec, &NetworkExec::carEndurance,
            this, &MainPage::carEnduranceSlot);
    connect(exec, &NetworkExec::carMileage,
            this, &MainPage::carMileageSlot);
    connect(exec, &NetworkExec::carWarning,
            this, &MainPage::carWarningSlot);
    connect(exec, &NetworkExec::crossingModeChanged,
            this, &MainPage::crossingModeChangedSlot);
    NetworkExec::getObject()->sendClientType(3);
    ui->leServerIP->setText(ConfigExec::getObject()->getServerIp());
    ui->leServerPort->setText(QString("%1")
                                  .arg(ConfigExec::getObject()->getServerPort()));
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::carLightStateSlot(int carId, bool sw)
{
    if(carId == 0)
    {
        ui->lbCarLight->setText(QString("%1").arg(sw ? "开启" : "关闭"));
    }
    else if(carId == 1)
    {
        ui->lbCarLight_2->setText(QString("%1").arg(sw ? "开启" : "关闭"));
    }
}

void MainPage::carAlarmLightStateSlot(int carId, bool sw)
{
    if(carId == 0)
    {
        ui->lbCarAlarmLight->setText(QString("%1").arg(sw ? "开启" : "关闭"));
    }
    else if(carId == 1)
    {
        ui->lbCarAlarmLight_2->setText(QString("%1").arg(sw ? "开启" : "关闭"));
    }
}

void MainPage::carLockStateSlot(int carId, bool sw)
{
    if(carId == 0)
    {
        ui->lbCarLockState->setText(QString("%1").arg(sw ? "上锁" : "解锁"));
    }
    else if(carId == 1)
    {
        ui->lbCarLockState_2->setText(QString("%1").arg(sw ? "上锁" : "解锁"));
    }
}

void MainPage::carStartStateSlot(int carId, bool sw)
{
    if(carId == 0)
    {
        ui->lbCarStartState->setText(QString("%1").arg(sw ? "启动" : "停止"));
    }
    else if(carId == 1)
    {
        ui->lbCarStartState_2->setText(QString("%1").arg(sw ? "启动" : "停止"));
    }
}

void MainPage::carEnduranceSlot(int carId, int endurance)
{
    if(carId == 0)
    {
        ui->lbCarEndurance
            ->setText(QString("%1KM").arg(endurance));
    }
    else if(carId == 1)
    {
        ui->lbCarEndurance_2
            ->setText(QString("%1KM").arg(endurance));
    }
}

void MainPage::carMileageSlot(int carId, int mileage)
{
    if(carId == 0)
    {
        ui->lbCarMileage
            ->setText(QString("%1KM").arg(mileage));
    }
    else if(carId == 1)
    {
        ui->lbCarMileage_2
            ->setText(QString("%1KM").arg(mileage));
    }
}

void MainPage::carWarningSlot(int carId, int warnId, QString warnMsg)
{
    if(carId == 0)
    {
        ui->lbCarWarning
            ->setText(QString("报警：%1").arg(warnMsg));
    }
    else if(carId == 1)
    {
        ui->lbCarWarning_2
            ->setText(QString("报警：%1").arg(warnMsg));
    }
}

void MainPage::crossingModeChangedSlot(int crossingId, int mode)
{
    if(crossingId == 0)
    {
        ui->lbCrossingMode->setText(mode == 0 ? "自动":
                                    mode == 1 ? "水平":
                                    mode == 2 ? "垂直":
                                    mode == 3 ? "禁行":
                                    mode == 4 ? "夜间":"未知");
    }
    else if(crossingId == 1)
    {
        ui->lbCrossingMode_2->setText(mode == 0 ? "自动":
                                    mode == 1 ? "水平":
                                    mode == 2 ? "垂直":
                                    mode == 3 ? "禁行":
                                    mode == 4 ? "夜间":"未知");
    }
}



void MainPage::on_btnMapAll_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->mapPage->setMapShow(true, true, true);
    
}


void MainPage::on_btnMapCar_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->mapPage->setMapShow(false, true, false);
}


void MainPage::on_btnMapCrossing_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->mapPage->setMapShow(false, false, true);
}


void MainPage::on_btnMapRoad_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->mapPage->setMapShow(true, false, false);
}


void MainPage::on_btnCarSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainPage::on_btnCarUnlock_clicked()
{
    NetworkExec::getObject()
        ->carSetLock(0, false, ui->leCarKey->text());
}


void MainPage::on_btnCarStart_clicked()
{
    NetworkExec::getObject()
        ->carSetStart(0, true, ui->leCarKey->text());
}


void MainPage::on_btnCarLock_clicked()
{
    NetworkExec::getObject()
        ->carSetLock(0, true, ui->leCarKey->text());
}


void MainPage::on_btnCarStop_clicked()
{
    NetworkExec::getObject()
        ->carSetStart(0, false, ui->leCarKey->text());
}


void MainPage::on_btnCarLightOpen_clicked()
{
    NetworkExec::getObject()->carSetLight(0, true, ui->leCarKey->text());
}


void MainPage::on_btnCarLightClose_clicked()
{
    NetworkExec::getObject()->carSetLight(0, false, ui->leCarKey->text());
}


void MainPage::on_btnCarAlarmLightOpen_clicked()
{
    NetworkExec::getObject()->carSetAlarmLight(0, true, ui->leCarKey->text());
}


void MainPage::on_btnCarAlarmLightClose_clicked()
{
    NetworkExec::getObject()->carSetAlarmLight(0, false, ui->leCarKey->text());
}

void MainPage::on_btnCarUnlock_2_clicked()
{
    NetworkExec::getObject()
        ->carSetLock(1, false, ui->leCarKey_2->text());
}


void MainPage::on_btnCarStart_2_clicked()
{
    NetworkExec::getObject()
        ->carSetStart(1, true, ui->leCarKey_2->text());
}


void MainPage::on_btnCarLock_2_clicked()
{
    NetworkExec::getObject()
        ->carSetLock(1, true, ui->leCarKey_2->text());
}


void MainPage::on_btnCarStop_2_clicked()
{
    NetworkExec::getObject()
        ->carSetStart(1, false, ui->leCarKey_2->text());
}


void MainPage::on_btnCarLightOpen_2_clicked()
{
    NetworkExec::getObject()->carSetLight(1, true, ui->leCarKey_2->text());
}


void MainPage::on_btnCarLightClose_2_clicked()
{
    NetworkExec::getObject()->carSetLight(1, false, ui->leCarKey_2->text());
}


void MainPage::on_btnCarAlarmLightOpen_2_clicked()
{
    NetworkExec::getObject()->carSetAlarmLight(1, true, ui->leCarKey_2->text());
}


void MainPage::on_btnCarAlarmLightClose_2_clicked()
{
    NetworkExec::getObject()->carSetAlarmLight(1, false, ui->leCarKey_2->text());
}


void MainPage::on_btnSystemSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainPage::on_btnCrossingSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainPage::on_btnCrossingSetAuto_clicked()
{
    if(!managerLoginState)
    {
        QMessageBox::warning(
            this, "警告",
            "未登录，请前往系统设置页面登录");
        return;
    }
    NetworkExec::getObject()->crossingSetMode(0, 0);
}


void MainPage::on_btnCrossingSetHor_clicked()
{
    if(!managerLoginState)
    {
        QMessageBox::warning(
            this, "警告",
            "未登录，请前往系统设置页面登录");
        return;
    }
    NetworkExec::getObject()->crossingSetMode(0, 1);
}


void MainPage::on_btnCrossingSetVor_clicked()
{
    if(!managerLoginState)
    {
        QMessageBox::warning(
            this, "警告",
            "未登录，请前往系统设置页面登录");
        return;
    }
    NetworkExec::getObject()->crossingSetMode(0, 2);
}


void MainPage::on_btnCrossingSetNone_clicked()
{
    if(!managerLoginState)
    {
        QMessageBox::warning(
            this, "警告",
            "未登录，请前往系统设置页面登录");
        return;
    }
    NetworkExec::getObject()->crossingSetMode(0, 3);
}


void MainPage::on_btnCrossingSetNight_clicked()
{
    if(!managerLoginState)
    {
        QMessageBox::warning(
            this, "警告",
            "未登录，请前往系统设置页面登录");
        return;
    }
    NetworkExec::getObject()->crossingSetMode(0, 4);
}

void MainPage::on_btnCrossingSetAuto_2_clicked()
{
    if(!managerLoginState)
    {
        QMessageBox::warning(
            this, "警告",
            "未登录，请前往系统设置页面登录");
        return;
    }
    NetworkExec::getObject()->crossingSetMode(1, 0);
}


void MainPage::on_btnCrossingSetHor_2_clicked()
{
    if(!managerLoginState)
    {
        QMessageBox::warning(
            this, "警告",
            "未登录，请前往系统设置页面登录");
        return;
    }
    NetworkExec::getObject()->crossingSetMode(1, 1);
}


void MainPage::on_btnCrossingSetVor_2_clicked()
{
    if(!managerLoginState)
    {
        QMessageBox::warning(
            this, "警告",
            "未登录，请前往系统设置页面登录");
        return;
    }
    NetworkExec::getObject()->crossingSetMode(1, 2);
}


void MainPage::on_btnCrossingSetNone_2_clicked()
{
    if(!managerLoginState)
    {
        QMessageBox::warning(
            this, "警告",
            "未登录，请前往系统设置页面登录");
        return;
    }
    NetworkExec::getObject()->crossingSetMode(1, 3);
}


void MainPage::on_btnCrossingSetNight_2_clicked()
{
    if(!managerLoginState)
    {
        QMessageBox::warning(
            this, "警告",
            "未登录，请前往系统设置页面登录");
        return;
    }
    NetworkExec::getObject()->crossingSetMode(1, 4);
}

void MainPage::on_btnLogin_clicked()
{
    if(ui->leUsername->text() == "admin" &&
        ui->lePassword->text() == "123")
    {
        QMessageBox::information(this, "提示", "登录成功");
        managerLoginState = true;
        ui->leUsername->setEnabled(false);
        ui->lePassword->setEnabled(false);
        ui->btnLogin->setEnabled(false);
        return;
    }
    QMessageBox::warning(
        this, "警告",
        "用户名或密码错误");
}


void MainPage::on_btnSave_clicked()
{
    QString ip = ui->leServerIP->text();
    int port = ui->leServerPort->text().toInt();
    if(ip.isEmpty() || port <= 0)
    {
        QMessageBox::warning(
            this, "警告",
            "输入有误");
        return;
    }
    ConfigExec::getObject()->setServerConfig(ip, port);
    QMessageBox::information(this, "提示", "保存成功，重启软件生效");
}

