/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "oglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    OGLWidget *openGLWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *primitivasGroupBox;
    QPushButton *cuboPushButton;
    QPushButton *cilindroPushButton;
    QPushButton *piramidePushButton;
    QPushButton *esferaPushButton;
    QGroupBox *iluminacaoGroupBox;
    QPushButton *flatPushButton;
    QCheckBox *flatCheckBox;
    QPushButton *gouradPushButton;
    QCheckBox *gouradCheckBox;
    QPushButton *phongPushButton;
    QCheckBox *phongCheckBox;
    QPushButton *quitPushButton;
    QPushButton *resetPushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(612, 453);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        openGLWidget = new OGLWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 481, 391));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(490, 0, 121, 321));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 119, 319));
        primitivasGroupBox = new QGroupBox(scrollAreaWidgetContents);
        primitivasGroupBox->setObjectName(QString::fromUtf8("primitivasGroupBox"));
        primitivasGroupBox->setGeometry(QRect(10, 10, 101, 151));
        cuboPushButton = new QPushButton(primitivasGroupBox);
        cuboPushButton->setObjectName(QString::fromUtf8("cuboPushButton"));
        cuboPushButton->setGeometry(QRect(10, 30, 80, 24));
        cilindroPushButton = new QPushButton(primitivasGroupBox);
        cilindroPushButton->setObjectName(QString::fromUtf8("cilindroPushButton"));
        cilindroPushButton->setGeometry(QRect(10, 60, 80, 24));
        piramidePushButton = new QPushButton(primitivasGroupBox);
        piramidePushButton->setObjectName(QString::fromUtf8("piramidePushButton"));
        piramidePushButton->setGeometry(QRect(10, 90, 80, 24));
        esferaPushButton = new QPushButton(primitivasGroupBox);
        esferaPushButton->setObjectName(QString::fromUtf8("esferaPushButton"));
        esferaPushButton->setGeometry(QRect(10, 120, 80, 24));
        iluminacaoGroupBox = new QGroupBox(scrollAreaWidgetContents);
        iluminacaoGroupBox->setObjectName(QString::fromUtf8("iluminacaoGroupBox"));
        iluminacaoGroupBox->setGeometry(QRect(10, 170, 101, 121));
        flatPushButton = new QPushButton(iluminacaoGroupBox);
        flatPushButton->setObjectName(QString::fromUtf8("flatPushButton"));
        flatPushButton->setGeometry(QRect(10, 30, 61, 24));
        flatCheckBox = new QCheckBox(iluminacaoGroupBox);
        flatCheckBox->setObjectName(QString::fromUtf8("flatCheckBox"));
        flatCheckBox->setGeometry(QRect(80, 30, 16, 22));
        flatCheckBox->setCheckable(true);
        gouradPushButton = new QPushButton(iluminacaoGroupBox);
        gouradPushButton->setObjectName(QString::fromUtf8("gouradPushButton"));
        gouradPushButton->setGeometry(QRect(10, 60, 61, 24));
        gouradCheckBox = new QCheckBox(iluminacaoGroupBox);
        gouradCheckBox->setObjectName(QString::fromUtf8("gouradCheckBox"));
        gouradCheckBox->setGeometry(QRect(80, 60, 16, 22));
        gouradCheckBox->setCheckable(true);
        phongPushButton = new QPushButton(iluminacaoGroupBox);
        phongPushButton->setObjectName(QString::fromUtf8("phongPushButton"));
        phongPushButton->setGeometry(QRect(10, 90, 61, 24));
        phongCheckBox = new QCheckBox(iluminacaoGroupBox);
        phongCheckBox->setObjectName(QString::fromUtf8("phongCheckBox"));
        phongCheckBox->setGeometry(QRect(80, 90, 16, 22));
        phongCheckBox->setCheckable(true);
        scrollArea->setWidget(scrollAreaWidgetContents);
        quitPushButton = new QPushButton(centralWidget);
        quitPushButton->setObjectName(QString::fromUtf8("quitPushButton"));
        quitPushButton->setGeometry(QRect(510, 360, 80, 24));
        resetPushButton = new QPushButton(centralWidget);
        resetPushButton->setObjectName(QString::fromUtf8("resetPushButton"));
        resetPushButton->setGeometry(QRect(510, 330, 80, 24));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 612, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        primitivasGroupBox->setTitle(QApplication::translate("MainWindow", "Primitivas", nullptr));
        cuboPushButton->setText(QApplication::translate("MainWindow", "Cubo", nullptr));
        cilindroPushButton->setText(QApplication::translate("MainWindow", "Cilindro", nullptr));
        piramidePushButton->setText(QApplication::translate("MainWindow", "Piramide", nullptr));
        esferaPushButton->setText(QApplication::translate("MainWindow", "Esfera", nullptr));
        iluminacaoGroupBox->setTitle(QApplication::translate("MainWindow", "Iluminacao", nullptr));
        flatPushButton->setText(QApplication::translate("MainWindow", "Flat", nullptr));
        flatCheckBox->setText(QString());
        gouradPushButton->setText(QApplication::translate("MainWindow", "Gourad", nullptr));
        gouradCheckBox->setText(QString());
        phongPushButton->setText(QApplication::translate("MainWindow", "Phong", nullptr));
        phongCheckBox->setText(QString());
        quitPushButton->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        resetPushButton->setText(QApplication::translate("MainWindow", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
