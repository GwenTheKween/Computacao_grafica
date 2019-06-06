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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "canvasopengl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    CanvasOpenGL *canvasOpenGL;
    QGroupBox *observerGroup;
    QDoubleSpinBox *obsZ;
    QDoubleSpinBox *obsX;
    QDoubleSpinBox *obsY;
    QLabel *obsLabelX;
    QLabel *obsLabelY;
    QLabel *obsLabelZ;
    QGroupBox *lightingGroup;
    QDoubleSpinBox *lightingXValue;
    QDoubleSpinBox *lightingYValue;
    QLabel *lightingX;
    QLabel *lightingZ;
    QLabel *lightingY;
    QDoubleSpinBox *lightingZValue;
    QGroupBox *viewing;
    QLabel *xMin;
    QLabel *xMax;
    QLabel *yMin;
    QLabel *yMax;
    QDoubleSpinBox *xMinValue;
    QDoubleSpinBox *yMinValue;
    QDoubleSpinBox *yMaxValue;
    QDoubleSpinBox *xMaxValue;
    QLabel *near;
    QLabel *far;
    QLabel *fovy;
    QDoubleSpinBox *nearValue;
    QDoubleSpinBox *fovyValue;
    QDoubleSpinBox *farValue;
    QCheckBox *isPerspective;
    QGroupBox *Drawing;
    QLabel *drawingR;
    QLabel *drawingG;
    QLabel *drawingB;
    QDoubleSpinBox *drawingRValue;
    QDoubleSpinBox *drawingGValue;
    QDoubleSpinBox *drawingBValue;
    QPushButton *undo;
    QPushButton *confirm;
    QCheckBox *drawingCheckBox;
    QDoubleSpinBox *drawingZValue;
    QLabel *drawingZ;
    QPushButton *clear;
    QGroupBox *toning;
    QComboBox *toningValue;
    QLabel *toningLabel;
    QPushButton *reset;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1080, 620);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1080, 620));
        MainWindow->setMaximumSize(QSize(1080, 640));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(1080, 620));
        centralWidget->setMaximumSize(QSize(1080, 620));
        canvasOpenGL = new CanvasOpenGL(centralWidget);
        canvasOpenGL->setObjectName(QString::fromUtf8("canvasOpenGL"));
        canvasOpenGL->setGeometry(QRect(0, 0, 800, 600));
        sizePolicy.setHeightForWidth(canvasOpenGL->sizePolicy().hasHeightForWidth());
        canvasOpenGL->setSizePolicy(sizePolicy);
        observerGroup = new QGroupBox(centralWidget);
        observerGroup->setObjectName(QString::fromUtf8("observerGroup"));
        observerGroup->setGeometry(QRect(800, 15, 280, 81));
        observerGroup->setAlignment(Qt::AlignCenter);
        observerGroup->setFlat(false);
        observerGroup->setCheckable(false);
        obsZ = new QDoubleSpinBox(observerGroup);
        obsZ->setObjectName(QString::fromUtf8("obsZ"));
        obsZ->setGeometry(QRect(190, 50, 60, 27));
        obsZ->setDecimals(1);
        obsZ->setMinimum(-1000.000000000000000);
        obsZ->setMaximum(1000.000000000000000);
        obsX = new QDoubleSpinBox(observerGroup);
        obsX->setObjectName(QString::fromUtf8("obsX"));
        obsX->setGeometry(QRect(10, 50, 60, 27));
        obsX->setDecimals(1);
        obsX->setMinimum(-1000.000000000000000);
        obsX->setMaximum(1000.000000000000000);
        obsY = new QDoubleSpinBox(observerGroup);
        obsY->setObjectName(QString::fromUtf8("obsY"));
        obsY->setGeometry(QRect(100, 50, 60, 27));
        obsY->setDecimals(1);
        obsY->setMinimum(-1000.000000000000000);
        obsY->setMaximum(1000.000000000000000);
        obsLabelX = new QLabel(observerGroup);
        obsLabelX->setObjectName(QString::fromUtf8("obsLabelX"));
        obsLabelX->setGeometry(QRect(10, 25, 60, 18));
        obsLabelX->setAlignment(Qt::AlignCenter);
        obsLabelY = new QLabel(observerGroup);
        obsLabelY->setObjectName(QString::fromUtf8("obsLabelY"));
        obsLabelY->setGeometry(QRect(100, 25, 60, 18));
        obsLabelY->setAlignment(Qt::AlignCenter);
        obsLabelZ = new QLabel(observerGroup);
        obsLabelZ->setObjectName(QString::fromUtf8("obsLabelZ"));
        obsLabelZ->setGeometry(QRect(190, 25, 60, 18));
        obsLabelZ->setAlignment(Qt::AlignCenter);
        lightingGroup = new QGroupBox(centralWidget);
        lightingGroup->setObjectName(QString::fromUtf8("lightingGroup"));
        lightingGroup->setGeometry(QRect(800, 110, 280, 81));
        lightingGroup->setAlignment(Qt::AlignCenter);
        lightingGroup->setFlat(false);
        lightingGroup->setCheckable(false);
        lightingXValue = new QDoubleSpinBox(lightingGroup);
        lightingXValue->setObjectName(QString::fromUtf8("lightingXValue"));
        lightingXValue->setGeometry(QRect(6, 50, 60, 27));
        lightingXValue->setDecimals(1);
        lightingXValue->setMinimum(-1000.000000000000000);
        lightingXValue->setMaximum(1000.000000000000000);
        lightingYValue = new QDoubleSpinBox(lightingGroup);
        lightingYValue->setObjectName(QString::fromUtf8("lightingYValue"));
        lightingYValue->setGeometry(QRect(100, 50, 60, 27));
        lightingYValue->setDecimals(1);
        lightingYValue->setMinimum(-1000.000000000000000);
        lightingYValue->setMaximum(1000.000000000000000);
        lightingX = new QLabel(lightingGroup);
        lightingX->setObjectName(QString::fromUtf8("lightingX"));
        lightingX->setGeometry(QRect(6, 25, 60, 18));
        lightingX->setAlignment(Qt::AlignCenter);
        lightingZ = new QLabel(lightingGroup);
        lightingZ->setObjectName(QString::fromUtf8("lightingZ"));
        lightingZ->setGeometry(QRect(190, 25, 60, 18));
        lightingZ->setAlignment(Qt::AlignCenter);
        lightingY = new QLabel(lightingGroup);
        lightingY->setObjectName(QString::fromUtf8("lightingY"));
        lightingY->setGeometry(QRect(100, 25, 60, 18));
        lightingY->setAlignment(Qt::AlignCenter);
        lightingZValue = new QDoubleSpinBox(lightingGroup);
        lightingZValue->setObjectName(QString::fromUtf8("lightingZValue"));
        lightingZValue->setGeometry(QRect(190, 50, 60, 27));
        lightingZValue->setDecimals(1);
        lightingZValue->setMinimum(-1000.000000000000000);
        lightingZValue->setMaximum(1000.000000000000000);
        viewing = new QGroupBox(centralWidget);
        viewing->setObjectName(QString::fromUtf8("viewing"));
        viewing->setGeometry(QRect(800, 200, 280, 120));
        viewing->setAlignment(Qt::AlignCenter);
        viewing->setFlat(false);
        viewing->setCheckable(false);
        xMin = new QLabel(viewing);
        xMin->setObjectName(QString::fromUtf8("xMin"));
        xMin->setGeometry(QRect(3, 30, 40, 18));
        xMax = new QLabel(viewing);
        xMax->setObjectName(QString::fromUtf8("xMax"));
        xMax->setGeometry(QRect(3, 50, 40, 18));
        yMin = new QLabel(viewing);
        yMin->setObjectName(QString::fromUtf8("yMin"));
        yMin->setGeometry(QRect(3, 73, 40, 18));
        yMax = new QLabel(viewing);
        yMax->setObjectName(QString::fromUtf8("yMax"));
        yMax->setGeometry(QRect(3, 97, 40, 18));
        xMinValue = new QDoubleSpinBox(viewing);
        xMinValue->setObjectName(QString::fromUtf8("xMinValue"));
        xMinValue->setGeometry(QRect(65, 23, 60, 25));
        xMinValue->setDecimals(1);
        xMinValue->setMinimum(-1000.000000000000000);
        xMinValue->setMaximum(1000.000000000000000);
        yMinValue = new QDoubleSpinBox(viewing);
        yMinValue->setObjectName(QString::fromUtf8("yMinValue"));
        yMinValue->setGeometry(QRect(65, 70, 60, 25));
        yMinValue->setDecimals(1);
        yMinValue->setMinimum(-1000.000000000000000);
        yMinValue->setMaximum(1000.000000000000000);
        yMaxValue = new QDoubleSpinBox(viewing);
        yMaxValue->setObjectName(QString::fromUtf8("yMaxValue"));
        yMaxValue->setGeometry(QRect(65, 94, 60, 25));
        yMaxValue->setDecimals(1);
        yMaxValue->setMinimum(-1000.000000000000000);
        yMaxValue->setMaximum(1000.000000000000000);
        xMaxValue = new QDoubleSpinBox(viewing);
        xMaxValue->setObjectName(QString::fromUtf8("xMaxValue"));
        xMaxValue->setGeometry(QRect(65, 47, 60, 25));
        xMaxValue->setDecimals(1);
        xMaxValue->setMinimum(-1000.000000000000000);
        xMaxValue->setMaximum(1000.000000000000000);
        near = new QLabel(viewing);
        near->setObjectName(QString::fromUtf8("near"));
        near->setGeometry(QRect(145, 30, 35, 18));
        far = new QLabel(viewing);
        far->setObjectName(QString::fromUtf8("far"));
        far->setGeometry(QRect(145, 50, 35, 18));
        fovy = new QLabel(viewing);
        fovy->setObjectName(QString::fromUtf8("fovy"));
        fovy->setGeometry(QRect(145, 73, 35, 18));
        nearValue = new QDoubleSpinBox(viewing);
        nearValue->setObjectName(QString::fromUtf8("nearValue"));
        nearValue->setGeometry(QRect(200, 23, 60, 25));
        nearValue->setDecimals(1);
        nearValue->setMinimum(-1000.000000000000000);
        nearValue->setMaximum(1000.000000000000000);
        fovyValue = new QDoubleSpinBox(viewing);
        fovyValue->setObjectName(QString::fromUtf8("fovyValue"));
        fovyValue->setGeometry(QRect(200, 70, 60, 25));
        fovyValue->setDecimals(1);
        fovyValue->setMinimum(-1000.000000000000000);
        fovyValue->setMaximum(1000.000000000000000);
        farValue = new QDoubleSpinBox(viewing);
        farValue->setObjectName(QString::fromUtf8("farValue"));
        farValue->setGeometry(QRect(200, 47, 60, 25));
        farValue->setDecimals(1);
        farValue->setMinimum(-1000.000000000000000);
        farValue->setMaximum(1000.000000000000000);
        isPerspective = new QCheckBox(viewing);
        isPerspective->setObjectName(QString::fromUtf8("isPerspective"));
        isPerspective->setGeometry(QRect(155, 97, 90, 22));
        Drawing = new QGroupBox(centralWidget);
        Drawing->setObjectName(QString::fromUtf8("Drawing"));
        Drawing->setGeometry(QRect(800, 330, 280, 130));
        Drawing->setAlignment(Qt::AlignCenter);
        Drawing->setFlat(false);
        Drawing->setCheckable(false);
        drawingR = new QLabel(Drawing);
        drawingR->setObjectName(QString::fromUtf8("drawingR"));
        drawingR->setGeometry(QRect(10, 27, 58, 18));
        drawingG = new QLabel(Drawing);
        drawingG->setObjectName(QString::fromUtf8("drawingG"));
        drawingG->setGeometry(QRect(10, 51, 58, 18));
        drawingB = new QLabel(Drawing);
        drawingB->setObjectName(QString::fromUtf8("drawingB"));
        drawingB->setGeometry(QRect(10, 75, 58, 18));
        drawingRValue = new QDoubleSpinBox(Drawing);
        drawingRValue->setObjectName(QString::fromUtf8("drawingRValue"));
        drawingRValue->setGeometry(QRect(45, 24, 60, 25));
        drawingRValue->setDecimals(1);
        drawingRValue->setMaximum(1.000000000000000);
        drawingRValue->setSingleStep(0.100000000000000);
        drawingGValue = new QDoubleSpinBox(Drawing);
        drawingGValue->setObjectName(QString::fromUtf8("drawingGValue"));
        drawingGValue->setGeometry(QRect(45, 48, 60, 25));
        drawingGValue->setDecimals(1);
        drawingGValue->setMaximum(1.000000000000000);
        drawingGValue->setSingleStep(0.100000000000000);
        drawingBValue = new QDoubleSpinBox(Drawing);
        drawingBValue->setObjectName(QString::fromUtf8("drawingBValue"));
        drawingBValue->setGeometry(QRect(45, 72, 60, 25));
        drawingBValue->setDecimals(1);
        drawingBValue->setMaximum(1.000000000000000);
        drawingBValue->setSingleStep(0.100000000000000);
        undo = new QPushButton(Drawing);
        undo->setObjectName(QString::fromUtf8("undo"));
        undo->setGeometry(QRect(35, 105, 80, 20));
        confirm = new QPushButton(Drawing);
        confirm->setObjectName(QString::fromUtf8("confirm"));
        confirm->setGeometry(QRect(145, 105, 80, 20));
        drawingCheckBox = new QCheckBox(Drawing);
        drawingCheckBox->setObjectName(QString::fromUtf8("drawingCheckBox"));
        drawingCheckBox->setGeometry(QRect(135, 25, 100, 24));
        drawingZValue = new QDoubleSpinBox(Drawing);
        drawingZValue->setObjectName(QString::fromUtf8("drawingZValue"));
        drawingZValue->setGeometry(QRect(170, 60, 60, 25));
        drawingZValue->setDecimals(1);
        drawingZValue->setMaximum(1000.000000000000000);
        drawingZValue->setSingleStep(1.000000000000000);
        drawingZ = new QLabel(Drawing);
        drawingZ->setObjectName(QString::fromUtf8("drawingZ"));
        drawingZ->setGeometry(QRect(135, 64, 58, 18));
        clear = new QPushButton(centralWidget);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setGeometry(QRect(980, 565, 80, 26));
        toning = new QGroupBox(centralWidget);
        toning->setObjectName(QString::fromUtf8("toning"));
        toning->setGeometry(QRect(800, 480, 280, 70));
        toning->setAlignment(Qt::AlignCenter);
        toningValue = new QComboBox(toning);
        toningValue->addItem(QString());
        toningValue->addItem(QString());
        toningValue->addItem(QString());
        toningValue->setObjectName(QString::fromUtf8("toningValue"));
        toningValue->setGeometry(QRect(140, 35, 120, 26));
        toningLabel = new QLabel(toning);
        toningLabel->setObjectName(QString::fromUtf8("toningLabel"));
        toningLabel->setGeometry(QRect(10, 38, 60, 18));
        reset = new QPushButton(centralWidget);
        reset->setObjectName(QString::fromUtf8("reset"));
        reset->setGeometry(QRect(820, 565, 80, 26));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setMinimumSize(QSize(1080, 20));
        statusBar->setMaximumSize(QSize(1080, 20));
        statusBar->setSizeGripEnabled(false);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        observerGroup->setTitle(QApplication::translate("MainWindow", "Observador", nullptr));
        obsLabelX->setText(QApplication::translate("MainWindow", "X", nullptr));
        obsLabelY->setText(QApplication::translate("MainWindow", "Y", nullptr));
        obsLabelZ->setText(QApplication::translate("MainWindow", "Z", nullptr));
        lightingGroup->setTitle(QApplication::translate("MainWindow", "Ilumina\303\247\303\243o", nullptr));
        lightingX->setText(QApplication::translate("MainWindow", "X", nullptr));
        lightingZ->setText(QApplication::translate("MainWindow", "Z", nullptr));
        lightingY->setText(QApplication::translate("MainWindow", "Y", nullptr));
        viewing->setTitle(QApplication::translate("MainWindow", "Visualiza\303\247\303\243o", nullptr));
        xMin->setText(QApplication::translate("MainWindow", "xMin", nullptr));
        xMax->setText(QApplication::translate("MainWindow", "xMax", nullptr));
        yMin->setText(QApplication::translate("MainWindow", "yMin", nullptr));
        yMax->setText(QApplication::translate("MainWindow", "yMax", nullptr));
        near->setText(QApplication::translate("MainWindow", "Near", nullptr));
        far->setText(QApplication::translate("MainWindow", "Far", nullptr));
        fovy->setText(QApplication::translate("MainWindow", "FOVY", nullptr));
        isPerspective->setText(QApplication::translate("MainWindow", "Perspectiva", nullptr));
        Drawing->setTitle(QApplication::translate("MainWindow", "Desenho", nullptr));
        drawingR->setText(QApplication::translate("MainWindow", "R", nullptr));
        drawingG->setText(QApplication::translate("MainWindow", "G", nullptr));
        drawingB->setText(QApplication::translate("MainWindow", "B", nullptr));
        undo->setText(QApplication::translate("MainWindow", "Desfazer", nullptr));
        confirm->setText(QApplication::translate("MainWindow", "Confirmar", nullptr));
        drawingCheckBox->setText(QApplication::translate("MainWindow", "Desenhando", nullptr));
        drawingZ->setText(QApplication::translate("MainWindow", "Z", nullptr));
        clear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        toning->setTitle(QApplication::translate("MainWindow", "Tonaliza\303\247\303\243o", nullptr));
        toningValue->setItemText(0, QApplication::translate("MainWindow", "Flat", nullptr));
        toningValue->setItemText(1, QApplication::translate("MainWindow", "Gourad", nullptr));
        toningValue->setItemText(2, QApplication::translate("MainWindow", "Phong", nullptr));

        toningLabel->setText(QApplication::translate("MainWindow", "M\303\251todo", nullptr));
        reset->setText(QApplication::translate("MainWindow", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
