
#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>



QT_BEGIN_NAMESPACE
namespace Ui { class MainPage; }
QT_END_NAMESPACE

class MainPage : public QWidget

{
    Q_OBJECT

public:
    MainPage(QWidget *parent = nullptr);
    ~MainPage();

private slots:
    void carLightStateSlot(int carId, bool sw);
    void carAlarmLightStateSlot(int carId, bool sw);
    void carLockStateSlot(int carId, bool sw);
    void carStartStateSlot(int carId, bool sw);
    void carEnduranceSlot(int carId, int endurance);
    void carMileageSlot(int carId, int mileage);
    void carWarningSlot(int carId, int warnId,
                    QString warnMsg);
    void crossingModeChangedSlot(int crossingId, int mode);

    void on_btnMapAll_clicked();

    void on_btnMapCar_clicked();

    void on_btnMapCrossing_clicked();

    void on_btnMapRoad_clicked();

    void on_btnCarSet_clicked();

    void on_btnCarUnlock_clicked();

    void on_btnCarStart_clicked();

    void on_btnCarLock_clicked();

    void on_btnCarStop_clicked();

    void on_btnCarLightOpen_clicked();

    void on_btnCarLightClose_clicked();

    void on_btnCarAlarmLightOpen_clicked();

    void on_btnCarAlarmLightClose_clicked();

    void on_btnCarUnlock_2_clicked();

    void on_btnCarStart_2_clicked();

    void on_btnCarLock_2_clicked();

    void on_btnCarStop_2_clicked();

    void on_btnCarLightOpen_2_clicked();

    void on_btnCarLightClose_2_clicked();

    void on_btnCarAlarmLightOpen_2_clicked();

    void on_btnCarAlarmLightClose_2_clicked();

    void on_btnSystemSet_clicked();

    void on_btnCrossingSet_clicked();

    void on_btnCrossingSetAuto_clicked();

    void on_btnCrossingSetHor_clicked();

    void on_btnCrossingSetVor_clicked();

    void on_btnCrossingSetNone_clicked();

    void on_btnCrossingSetNight_clicked();

    void on_btnCrossingSetAuto_2_clicked();

    void on_btnCrossingSetHor_2_clicked();

    void on_btnCrossingSetVor_2_clicked();

    void on_btnCrossingSetNone_2_clicked();

    void on_btnCrossingSetNight_2_clicked();

    void on_btnLogin_clicked();

    void on_btnSave_clicked();

private:
    Ui::MainPage *ui;
    bool managerLoginState = false;
};

#endif // MAINPAGE_H
