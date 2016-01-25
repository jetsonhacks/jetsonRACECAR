#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "JHPWMPCA9685.h"

PCA9685 *pca9685 ;

// At 50 hz a frame is 20 milliseconds
// The PCA9685 PWM Driver is 12 bits
// Full Reverse signal to the ESC is 1 ms
// Neutral signal to the ESC is 1.5 ms
// Full Throttle signal to the ESC is 2 ms

#define THROTTLE_FULL_REVERSE 204 // 1ms/20ms * 4096
#define THROTTLE_NEUTRAL 307      // 1.5ms/20ms * 4096
#define THROTTLE_FULL_FORWARD 409 // 2ms/20ms * 4096

// The ESC is plugged into the following PWM channel
#define ESC_CHANNEL 1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Initialize the PWM board
    pca9685 = new PCA9685() ;
    int err = pca9685->openPCA9685();
    if (err < 0){
        printf("Error: %d", pca9685->error);
    }
    printf("PCA9685 Device Address: 0x%02X\n",pca9685->kI2CAddress) ;
    pca9685->setAllPWM(0,0) ;
    pca9685->reset() ;
    pca9685->setPWMFrequency(50) ;
    // Set the throttle to "neutral" (1.5ms)
    sleep(1) ;
    pca9685->setPWM(ESC_CHANNEL,0,THROTTLE_NEUTRAL);
}

MainWindow::~MainWindow()
{
    pca9685->closePCA9685();
    delete ui;
}

void MainWindow::on_reverseButton_clicked()
{
    ui->currentSetting->setText("Full Reverse");
    pca9685->setPWM(ESC_CHANNEL,0,THROTTLE_FULL_REVERSE);
}

void MainWindow::on_neutralButton_clicked()
{

    ui->currentSetting->setText("Neutral") ;
    pca9685->setPWM(ESC_CHANNEL,0,THROTTLE_NEUTRAL);
}

void MainWindow::on_forwardButton_clicked()
{
    ui->currentSetting->setText("Full Forward") ;
    pca9685->setPWM(ESC_CHANNEL,0,THROTTLE_FULL_FORWARD);
}
