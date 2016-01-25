#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_reverseButton_clicked();

    void on_neutralButton_clicked();

    void on_forwardButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
