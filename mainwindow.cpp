#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "record.h"
#include "mainwindow.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QListWidgetItem>
#include <QColor>
#include <QTimer>
#include <QDateTime>
//---------------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create records
    records = new Records();

    // init running session, false
    isRunningSession = false;

    //connecting all signals to slots
    connect(ui->powerButton,SIGNAL(released()), this, SLOT (powerClicked()));
    connect(ui->group1Button,SIGNAL(released()), this, SLOT (group1Selected()));
    connect(ui->group2Button,SIGNAL(released()), this, SLOT (group2Selected()));
    connect(ui->group3Button,SIGNAL(released()), this, SLOT (group3Selected()));
    connect(ui->alphaButton,SIGNAL(released()), this, SLOT (alphaSelected()));
    connect(ui->betaButton,SIGNAL(released()), this, SLOT (betaSelected()));
    connect(ui->deltaButton,SIGNAL(released()), this, SLOT (deltaSelected()));
    connect(ui->thetaButton,SIGNAL(released()), this, SLOT (thetaSelected()));
    connect(ui->intensityUpButton,SIGNAL(released()), this, SLOT (moveUp()));
    connect(ui->intensityDownButton,SIGNAL(released()), this, SLOT (moveDown()));
    connect(ui->skinButton,SIGNAL(released()), this, SLOT (skinConnected()));
    connect(ui->endButton,SIGNAL(released()), this, SLOT (endSession()));
    connect(ui->recordUpButton,SIGNAL(released()), this, SLOT (recordListUp()));
    connect(ui->recordDownButton, SIGNAL(released()), this, SLOT (recordListDown()));
    connect(ui->recordYesButton, SIGNAL(released()), this, SLOT(handleSaveRecord()));
    connect(ui->recordNoButton, SIGNAL(released()), this, SLOT(handleCancelSaveRecord()));

    // user designated time submit
    connect(ui->customTimeSubmit, SIGNAL(released()), this, SLOT(setUserDesignatedTime()));

    // device config
    connect(ui->realtimeRadioButton, SIGNAL(released()), this, SLOT(setRealtime()));
    connect(ui->relativetimeRadioButton, SIGNAL(released()), this, SLOT(setRelativeTime()));
    connect(ui->clearRecordsButton, SIGNAL(released()), this, SLOT(handleClearRecords()));
    connect(ui->rechargeBatteryButton, SIGNAL(released()), this, SLOT(rechargeBattery()));


    //disabling buttons until device is turned on
    ui->group1Button->setEnabled(false);
    ui->group2Button->setEnabled(false);
    ui->group3Button->setEnabled(false);
    ui->alphaButton->setEnabled(false);
    ui->betaButton->setEnabled(false);
    ui->deltaButton->setEnabled(false);
    ui->thetaButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->endButton->setEnabled(false);
    ui->intensityUpButton->setEnabled(false);
    ui->intensityDownButton->setEnabled(false);
    ui->batteryValLabel->setVisible(false);

    // hide custom time input widget
    ui->userDesignatedWidget->setVisible(false);

    // record list screen starts in a turned off state
    ui->recordList->setStyleSheet("background-color: black");

    // set device to realtime
    setRealtime();

    // disable record interface buttons
    ui->recordYesButton->setEnabled(false);
    ui->recordNoButton->setEnabled(false);
    ui->recordUpButton->setEnabled(false);
    ui->recordDownButton->setEnabled(false);

    //device starts in "Off Mode"
    ui->intensityList->setCurrentRow(0);

    // hide recharge warning
    ui->rechargeWarnLabel->setVisible(false);

    // device starts turned off and not attached to skin
    power = false;
    skin = false;

    connectionLevel = 0;
    chosenTime = -1; //initializing the timer variable
    seconds = 0; //initialize seconds

    //starting the session
    connect(ui->startButton,SIGNAL(released()), this, SLOT (startSession()));

}
//---------------------------------------------------------------------------------------------------------
// destructor, clean up ui and dynamically allocated Records
MainWindow::~MainWindow()
{
    delete ui;
    delete records;
}
//---------------------------------------------------------------------------------------------------------
// simulates pressing of the power button on the device
void MainWindow::powerClicked()
{
    power = !power;

    // determine whether session group and type selection butons are enabled/disabled
    ui->group1Button->setEnabled(power);
    ui->group2Button->setEnabled(power);
    ui->group3Button->setEnabled(power);
    ui->alphaButton->setEnabled(power);
    ui->betaButton->setEnabled(power);
    ui->deltaButton->setEnabled(power);
    ui->thetaButton->setEnabled(power);
    ui->endButton->setEnabled(power);
    ui->intensityUpButton->setEnabled(power);
    ui->intensityDownButton->setEnabled(power);

    ui->group1Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->group2Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->group3Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");

    ui->sessionWidget->setVisible(power);
    ui->batteryValLabel->setVisible(power);

    if (isRunningSession)
    {
        // end session if power button is pressed while a session is running
        endSession();
    }

    if (power)
    {
        // device is turned on
        ui->powerLED->setStyleSheet("background-color: rgb(138, 226, 52)");
        // init records list interface
        initRecordList();
    } else {
        //device is off
        ui->powerLED->setStyleSheet("background-color: rgb(46, 52, 54)");
        MainWindow::shutOffRecordList();
    }
}
//---------------------------------------------------------------------------------------------------------

void MainWindow::group1Selected()
{
    ui->group1Button->setStyleSheet("QPushButton {background-color: rgb(255, 0, 0);}");
    ui->group2Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->group3Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->sessionWidget->setVisible(true);

    currSession.setGroup(20);
    ui->timerLabel->setText(QString::number(currSession.getGroup())+ ":00");

    determineStartState();
}
//---------------------------------------------------------------------------------------------------------
void MainWindow::group2Selected()
{
    ui->group1Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->group2Button->setStyleSheet("QPushButton {background-color: rgb(255, 165, 0);}");
    ui->group3Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->sessionWidget->setVisible(true);

    currSession.setGroup(45);
    ui->timerLabel->setText(QString::number(currSession.getGroup())+ ":00");

    determineStartState();
}
//---------------------------------------------------------------------------------------------------------
void MainWindow::group3Selected()
{
    ui->group1Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->group2Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->group3Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 0);}");
    ui->sessionWidget->setVisible(true);

    ui->userDesignatedWidget->setVisible(true);

    determineStartState();
}
//---------------------------------------------------------------------------------------------------------
void MainWindow::alphaSelected()
{
    ui->alphaButton->setStyleSheet("QPushButton {background-color: rgb(252, 175, 62);}");
    ui->betaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->deltaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->thetaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");

    currSession.setName("Alpha");
    device.setSessionState(true);

    determineStartState();
}
//---------------------------------------------------------------------------------------------------------
void MainWindow::betaSelected()
{
    ui->alphaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->betaButton->setStyleSheet("QPushButton {background-color: rgb(252, 233, 79);}");
    ui->deltaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->thetaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");

    currSession.setName("Beta");

    determineStartState();

}
//---------------------------------------------------------------------------------------------------------
void MainWindow::deltaSelected()
{
    ui->alphaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->betaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->deltaButton->setStyleSheet("QPushButton {background-color: rgb(138, 226, 52);}");
    ui->thetaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");

    currSession.setName("Delta");

    determineStartState();
}
//---------------------------------------------------------------------------------------------------------
void MainWindow::thetaSelected()
{
    ui->alphaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->betaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->deltaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->thetaButton->setStyleSheet("QPushButton {background-color: rgb(58, 157, 255);}");

    currSession.setName("Theta");

    determineStartState();
}
//---------------------------------------------------------------------------------------------------------
int MainWindow::retrieveGroup()
{
    int temp = ui->userInput->text().toInt();
    return temp;
}


// starts the session timer
void MainWindow::startTimer()
{
    ui->connectionTestLabel->setEnabled(false);
    QTimer* timer = device.getTimerObj();
    initTimer(timer);
}

//---------------------------------------------------------------------------------------------------------

// begin therapy session
void MainWindow::startSession()
{
    // update battery info, checks if enough battery life to continue
    updateBat();

    // disable realtime v. relative time toggle while session is running
    setTimeToggleState(false);

    // disable group and type selection buttons while session is running
    toggleSessionSelection(false);

    qDebug() << "Connection to skin: " << connectionLevel;

    ui->connectionTestLabel->setEnabled(true);
    // run connection test
    connectTest();

    // update connection stength label with results of test
    ui->connectStrengthDisplay->setText(connectionLevel == 1  ? "None" : connectionLevel == 2 ? "Medium" : "Strong");

    // don't start session if connection is too weak
    if(connectionLevel == 1){
        qDebug() << "Connection to skin not detected";
        // show warning on ui telling user that connection is too weak
        ui->recordList->clear();
        ui->recordList->addItem("WARNING:\nConnection to skin not detected!\nCannot start session!");
        ui->recordList->setStyleSheet("color: red");
        ui->recordYesButton->setEnabled(false);
        ui->recordNoButton->setEnabled(false);
        return;
    } else {
        initRecordList();
    }

    // pause on connection strength for 2 sec then show intensity
    QTimer::singleShot(2000, this, SLOT(resetIntensityList()));
    QTimer::singleShot(2000, this, SLOT(startTimer()));
    isRunningSession = true;
    // disable start button while session is running
    determineStartState();
}
//---------------------------------------------------------------------------------------------------------
/*
 * This function takes in a timer object. It then grabs the session's group.
 * It connectes the timer to a function, updateInfo() in this case
 * It then checks if the application is on the skin, and if so, starts the timer
 */
void MainWindow::initTimer(QTimer* t) {

    chosenTime = currSession.getGroup();
    connect(t, &QTimer::timeout, this, &MainWindow::updateInfo);

    if (skin == true) {
        t->start(1000);
    }

}
//---------------------------------------------------------------------------------------------------------

/*
 * This function depletes the batter based on the intensity and conncetion level
 * It then causes the visual timer to decrease based on a certain criteria.
 * This will decrease two variables reprresnting minutes and seconds at each interval
 * until the session is ended or the device is removed from skin
 */
void MainWindow::updateInfo() {
    if (skin == true) {

        // electrodes are on skin
        qDebug() << "Update Timer is being called";

        device.batteryDepletion(currSession.getIntensity(), connectionLevel);

        if(seconds == 0 && chosenTime != 0){
            chosenTime--;
            seconds = 60;
        }
        if(seconds==0 && chosenTime==0){
            qDebug() << "Timer is done";
            currSession.setElapsed(0,0);
            setLastSession(currSession);
            chosenTime = -1;
            seconds = 0;
            device.getTimerObj()->stop();
            device.getTimerObj()->disconnect();

            // prompt user to save last session
            showSaveSessionPrompt();
            reset();
            // enable realtime/relative time toggles
            setTimeToggleState(true);
            return;

        }

        seconds -= timeScale;  // controls timer countdown

        QString timeString = ((chosenTime < 10) ? "0" + QString::number(chosenTime) :QString::number(chosenTime)) + ((seconds < 10) ? + ":0" + QString::number(seconds) : + ":" + QString::number(seconds));
        ui->timerLabel->setText(timeString);
        ui->batteryValLabel->setText(QString::number(device.getBat()));


    }
    else{
        // electrodes not on skin
        qDebug() << "Device removed from skin";
        chosenTime = -1;
        seconds = 0;
        device.getTimerObj()->stop();
        device.getTimerObj()->disconnect();

        ui->timerLabel->setText("00:00");
        reset();
        setTimeToggleState(true);
        ui->batteryValLabel->setText(QString::number(device.getBat()));
    }

    this->updateBat();
}
//---------------------------------------------------------------------------------------------------------
void MainWindow::moveUp()
{
    if(ui->intensityList->currentRow()>0)
    {
        ui->intensityList->setCurrentRow(ui->intensityList->currentRow()-1);
        currSession.setIntensity(ui->intensityList->currentRow()+1);
    }
    qDebug() << "intensity" <<currSession.getIntensity();

}
//---------------------------------------------------------------------------------------------------------
void MainWindow::moveDown()
{
    if(ui->intensityList->currentRow()<7)
    {
        ui->intensityList->setCurrentRow(ui->intensityList->currentRow()+1);
        currSession.setIntensity(ui->intensityList->currentRow()+1);
    }
    qDebug() << "intensity" << currSession.getIntensity();

}
//---------------------------------------------------------------------------------------------------------
void MainWindow::skinConnected()
{
    skin = !skin;

    if(skin)
    {
        ui->skinButton->setStyleSheet("QPushButton {background-color: #30D5C8;}");
    }
    else
    {
        ui->skinButton->setStyleSheet("QPushButton {background-color: rgb(247, 215, 255);}");

        if (isRunningSession)
        {
            endSession();
        }
    }

    // check if start button should be enabled
    determineStartState();
    ui->electrodeStatusDisplay->setText(skin ? "True" : "False");
}
//---------------------------------------------------------------------------------------------------------
void MainWindow::connectTest()
{
    int temp =  QRandomGenerator::global()->bounded(1, 9);

    if(temp == 1 || temp == 2 || temp == 3)
        connectionLevel = 3;
    else if(temp == 4 || temp == 5 || temp == 6)
        connectionLevel = 2;
    else
        connectionLevel = 1;

    ui->intensityList->setCurrentRow(temp-1);
    qDebug() << "connection level: " << connectionLevel;

}
//---------------------------------------------------------------------------------------------------------

/*
 * This function ends a session by resetting the time (minutes and seconds) and stops the timer object
 */
void MainWindow::endSession()
{
    // if there is no current session running, then do nothing
    if (!isRunningSession)
    {
        return;
    }

    currSession.setElapsed(chosenTime, seconds);
    setLastSession(currSession);
    qDebug() << "Ending session...";
    chosenTime = -1;
    seconds = 0;
    device.getTimerObj()->stop();
    device.getTimerObj()->disconnect();

    ui->timerLabel->setText("00:00");
    ui->batteryValLabel->setText(QString::number(device.getBat()));
    reset();
    showSaveSessionPrompt();
    setTimeToggleState(true);
}
//---------------------------------------------------------------------------------------------------------
// initializes the recordsList interface on the ui
void MainWindow::initRecordList()
{
    // "turn on" screen
    if (power)
    {
        ui->recordList->setStyleSheet("background-color: white"); // background color
        ui->recordList->setStyleSheet("color: black"); // text color
    }

    ui->recordList->clear();

    // activate nav buttons
    ui->recordUpButton->setEnabled(true);
    ui->recordDownButton->setEnabled(true);

    // deactivate yes, no buttons
    ui->recordYesButton->setEnabled(false);
    ui->recordNoButton->setEnabled(false);

    // populate it with records
    for (int i = 0; i < records->getSize(); i++)
    {
        ui->recordList->addItem(records->getRecord(i)->toString());
    }

}
//---------------------------------------------------------------------------------------------------------
void MainWindow::shutOffRecordList()
{
    // turn off screen
    ui->recordList->setStyleSheet("background-color: black"); // background color
    ui->recordList->clear(); // clear rows

    // disable record interface buttons
    ui->recordYesButton->setEnabled(false);
    ui->recordNoButton->setEnabled(false);
    ui->recordUpButton->setEnabled(false);
    ui->recordDownButton->setEnabled(false);

}
//---------------------------------------------------------------------------------------------------------
void MainWindow::recordListUp()
{
    int currentRow = ui->recordList->currentRow();
    if (currentRow > 0)
    {
        ui->recordList->setCurrentRow(currentRow - 1);
    }

}
//---------------------------------------------------------------------------------------------------------
// navigate records interface down
void MainWindow::recordListDown()
{
    int currentRow = ui->recordList->currentRow();
    if (currentRow < records->getSize() - 1)
    {
       ui->recordList->setCurrentRow(currentRow + 1);
    }

}
//---------------------------------------------------------------------------------------------------------
void MainWindow::showSaveSessionPrompt()
{
    // enable record yes and no buttons
    ui->recordYesButton->setEnabled(true);
    ui->recordNoButton->setEnabled(true);

    // prompt user to save session
    ui->recordList->clear();
    ui->recordList->addItem("SESSION ENDED\n");
    ui->recordList->addItem("Would you like to save\nthe previous session?");
    ui->recordList->addItem("");
    ui->recordList->addItem("Press the Yes button to Save");
    ui->recordList->addItem("Press the No button to Cancel");

}
//---------------------------------------------------------------------------------------------------------
void MainWindow::handleSaveRecord()
{
    QDateTime date;
    QString timestamp = date.currentDateTime().toString();

    // create a new Record from the Current Session and push to Records
    Record* sessionRecord = new Record(lastSession.getName(), lastSession.getGroup(),
                                       lastSession.getElapsed(), lastSession.getIntensity(), timestamp);
    records->pushRecord(sessionRecord);

    // go back to main menu
    ui->recordList->clear();
    initRecordList();

}
//---------------------------------------------------------------------------------------------------------
void MainWindow::handleCancelSaveRecord()
{
    ui->recordList->clear();
    initRecordList();
}
//---------------------------------------------------------------------------------------------------------
void MainWindow::reset()
{
    // set style for session group and type selection buttons
    ui->group1Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->group2Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->group3Button->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");

    ui->alphaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->betaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->deltaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");
    ui->thetaButton->setStyleSheet("QPushButton {background-color: rgb(255, 255, 255);}");

    ui->connectionTestLabel->setEnabled(false);

    // hide user designated time widget and clear text
    ui->userDesignatedWidget->setVisible(false);
    ui->userInput->setText("");

    // reset session info
    currSession.setName("default");
    currSession.setIntensity(1);
    currSession.setGroup(0);

    // enable session selection buttons
    toggleSessionSelection(true);
    isRunningSession = false;
}
//---------------------------------------------------------------------------------------------------------
void MainWindow::updateBat()
{

    int currBat = device.checkBatLevel();

    if(currBat == 2)
            ui->batteryValLabel->setStyleSheet("background-color: rgb(255,165,0);");
    else if(currBat == 1)
            ui->batteryValLabel->setStyleSheet("background-color: rgb(255, 0, 0);");
    else if(currBat == 0)
    {

            this->powerClicked();
    }
    else
            ui->batteryValLabel->setStyleSheet("background-color: rgb(0, 128, 0);");

}

// switch timer to run at realtime
void MainWindow::setRealtime()
{
    ui->realtimeRadioButton->setChecked(true);
    timeScale = 1;
}

// switch timer to run at relative time (1 sec === 1 min)
void MainWindow::setRelativeTime()
{
    ui->relativetimeRadioButton->setChecked(true);
    timeScale = 60;
}

// toggles whether user can switch between real and relative time
void MainWindow::setTimeToggleState(bool s)
{
    ui->realtimeRadioButton->setEnabled(s);
    ui->relativetimeRadioButton->setEnabled(s);
}

// clears entire records list
void MainWindow::handleClearRecords()
{
    records->clear();
    initRecordList();
}

void MainWindow::setUserDesignatedTime()
{
    // grab value from text input
    int val = retrieveGroup();

    // set current session group
    currSession.setGroup(val);
    qDebug() << currSession.getGroup();

    // update timer
    ui->timerLabel->setText(QString::number(currSession.getGroup())+ ":00");

    determineStartState();
}

// controls whether start button is enabled or not
void MainWindow::determineStartState()
{
    bool isEnabled = false;

    if (power && currSession.getGroup() != 0 && currSession.getName() != "default"
            && skin && !isRunningSession)
    {
        isEnabled = true;
    }

    ui->startButton->setEnabled(isEnabled);

}

// reset battery level to 100%
void MainWindow::rechargeBattery()
{
    if (!isRunningSession)
    {
       device.setBatLevel(100.00f);
       updateBat();
       ui->batteryValLabel->setText(QString::number(device.getBat()));
    } else {
        ui->rechargeWarnLabel->setVisible(true);
        QTimer::singleShot(2000, this, SLOT(hideRechargeWarnLabel()));
    }
}


// reset current intensity
void MainWindow::resetIntensityList()
{
    currSession.setIntensity(1);
    ui->intensityList->setCurrentRow(currSession.getIntensity() - 1);
}


void MainWindow::setLastSession(Session s)
{
    lastSession.setName(s.getName());
    lastSession.setIntensity(s.getIntensity());
    lastSession.setGroup(s.getGroup());
    lastSession.setElapsed(s.getElapsed());
}

void MainWindow::hideRechargeWarnLabel()
{
    ui->rechargeWarnLabel->setVisible(false);
}

// takes a bool, uses it to determine whether therapy session group and type buttons are enabled
void MainWindow::toggleSessionSelection(bool b)
{
    ui->group1Button->setEnabled(b);
    ui->group2Button->setEnabled(b);
    ui->group3Button->setEnabled(b);
    ui->alphaButton->setEnabled(b);
    ui->betaButton->setEnabled(b);
    ui->deltaButton->setEnabled(b);
    ui->thetaButton->setEnabled(b);
}
