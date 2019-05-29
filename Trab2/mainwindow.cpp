#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resetEverything();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetEverything(){
    setIlum(FLAT);
}

void MainWindow::on_quitPushButton_clicked()
{
    exit(0);
}

void MainWindow::setIlum(iluminations ilum){
    currIlum = ilum;
    if(ilum == FLAT){
        ui->flatCheckBox->setChecked(true);
        ui->gouradCheckBox->setChecked(false);
        ui->phongCheckBox->setChecked(false);
    }else if(ilum == GOURAD){
        ui->flatCheckBox->setChecked(false);
        ui->gouradCheckBox->setChecked(true);
        ui->phongCheckBox->setChecked(false);
    }else if(ilum == PHONG){
        ui->flatCheckBox->setChecked(false);
        ui->gouradCheckBox->setChecked(false);
        ui->phongCheckBox->setChecked(true);
    }
}

void MainWindow::on_resetPushButton_clicked()
{
    resetEverything();
}

void MainWindow::on_flatPushButton_clicked()
{
    setIlum(FLAT);
}

void MainWindow::on_gouradPushButton_clicked()
{
    setIlum(GOURAD);
}

void MainWindow::on_phongPushButton_clicked()
{
    setIlum(PHONG);
}
