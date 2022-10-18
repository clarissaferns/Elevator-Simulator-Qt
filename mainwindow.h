#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <session.h>
#include <Device.h>
#include <records.h>
#include <QTimer>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Session currSession;
    Session lastSession;
    Device device;
    Records* records;

    bool power;
    bool skin;
    float connectionLevel;
    int chosenTime;
    int seconds;
    int timeScale;
    bool isRunningSession;
    int retrieveGroup();
    void initRecordList();
    void shutOffRecordList();
    void showSaveSessionPrompt();
    void reset();
    void initTimer(QTimer*);
    void updateInfo();
    void updateBat();
    void setTimeToggleState(bool);
    void handleReplaceBattery();
    void determineStartState();
    void setLastSession(Session);
    void toggleSessionSelection(bool);

private slots:
    void group1Selected();
    void group2Selected();
    void group3Selected();
    void alphaSelected();
    void betaSelected();
    void deltaSelected();
    void thetaSelected();
    void powerClicked();
    void moveUp();
    void moveDown();
    void startSession();
    void skinConnected();
    void connectTest();
    void endSession();
    void recordListUp();
    void recordListDown();
    void handleSaveRecord();
    void handleCancelSaveRecord();
    void setRealtime();
    void setRelativeTime();
    void handleClearRecords();
    void setUserDesignatedTime();
    void rechargeBattery();
    void resetIntensityList();
    void hideRechargeWarnLabel();
    void startTimer();
};
#endif // MAINWINDOW_H
