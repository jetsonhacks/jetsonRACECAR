#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "JHPWMPCA9685.h"

PCA9685 *pca9685 ;

// At 50 hz a frame is 20 milliseconds
// The PCA9685 PWM Driver is 12 bits
// Full Reverse signal to the ESC is 1 ms
// Neutral signal to the ESC is 1.5 ms
// Full PWM signal to the ESC is 2 ms

// The nomenclature is for the ESC throttle, for the steering neutral is center,
// full forward is right, full reverse is left

#define PWM_FULL_REVERSE 204 // 1ms/20ms * 4096
#define PWM_NEUTRAL 307      // 1.5ms/20ms * 4096
#define PWM_FULL_FORWARD 409 // 2ms/20ms * 4096



// The Steering Servo is plugged into the follow PWM channel
#define STEERING_CHANNEL 0
// The ESC is plugged into the following PWM channel
#define ESC_CHANNEL 1

float currentPWM = PWM_NEUTRAL ;
int currentChannel = ESC_CHANNEL ;

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
    // Set the PWM to "neutral" (1.5ms)
    sleep(1) ;
    pca9685->setPWM(ESC_CHANNEL,0,PWM_NEUTRAL);
    currentPWM = PWM_NEUTRAL ;
    ui->spinValue->setMaximum(4095.0)  ;
    ui->spinValue->setMinimum(0.0);
    ui->spinValue->setValue( PWM_NEUTRAL ) ;
    updatePWM() ;
    currentChannel=ESC_CHANNEL ;
}

MainWindow::~MainWindow()
{
    pca9685->closePCA9685();
    delete ui;
}

void MainWindow::updatePWM()
{
    pca9685->setPWM(currentChannel,0,currentPWM) ;
    QString labelColor = "black" ;
    if ((currentPWM < PWM_FULL_REVERSE) || (currentPWM > PWM_FULL_FORWARD)) {
        labelColor="red";
    }

    // Update the readout
    char stringBuffer[10] ;
    sprintf(stringBuffer,"%.2f",currentPWM) ;
    QString fonttemplate = tr("<font color='%1'>%2</font>");
    ui->labelCurrentValue->setText( fonttemplate.arg( labelColor, stringBuffer ) );
    ui->spinValue->setValue(currentPWM) ;
}

void MainWindow::on_decrementButton_clicked()
{
    currentPWM -- ;
    updatePWM() ;
}


void MainWindow::on_neutralButton_clicked()
{
    currentPWM = PWM_NEUTRAL ;
    updatePWM() ;
}

void MainWindow::on_incrementButton_clicked()
{
    currentPWM ++ ;
    updatePWM() ;
}



void MainWindow::on_spinValue_valueChanged(double arg1)
{
    currentPWM = arg1 ;
    updatePWM() ;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    currentChannel = (index==0) ? ESC_CHANNEL : STEERING_CHANNEL ;
    // reset the pwm duty cycle
    currentPWM=PWM_NEUTRAL ;
    updatePWM() ;
}
