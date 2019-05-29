#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

enum iluminations{
    FLAT,
    GOURAD,
    PHONG
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resetEverything();

private slots:
    void on_quitPushButton_clicked();

    void on_resetPushButton_clicked();

    void on_flatPushButton_clicked();

    void on_gouradPushButton_clicked();

    void on_phongPushButton_clicked();

private:
    int currIlum;

    Ui::MainWindow *ui;
    void setIlum(iluminations ilum);
};

#endif // MAINWINDOW_H
