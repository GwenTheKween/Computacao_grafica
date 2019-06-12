#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);

    this->ui->canvasOpenGL->setFormat(format);

    this->updateStatusBar("Use esse método para dar feedback das interações na barra de status.");

    QTimer::singleShot( // o timer é apenas demonstrativo
        5000,
        this,
        SLOT( clearStatusBar() ) // E utilize esse para limpar a barra de status
    );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStatusBar(QString message) {
    this->ui->statusBar->showMessage(message);
}

void MainWindow::clearStatusBar() {
    this->ui->statusBar->clearMessage();
}


// OBSERVER
void MainWindow::on_obsX_valueChanged(double arg1)
{
    ui->canvasOpenGL->setObserver(0,arg1);
}

void MainWindow::on_obsY_valueChanged(double arg1)
{
    ui->canvasOpenGL->setObserver(1,arg1);
}

void MainWindow::on_obsZ_valueChanged(double arg1)
{
    ui->canvasOpenGL->setObserver(2,arg1);
}

// LIGHTING
void MainWindow::on_lightingXValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setLightX(arg1);
}

void MainWindow::on_lightingYValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setLightY(arg1);
}

void MainWindow::on_lightingZValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setLightZ(arg1);
}

// VIEWING
void MainWindow::on_xMinValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setPerspective(0, arg1);
}

void MainWindow::on_xMaxValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setPerspective(1,arg1);
}

void MainWindow::on_yMinValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setPerspective(2,arg1);
}


void MainWindow::on_yMaxValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setPerspective(3,arg1);
}

void MainWindow::on_nearValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setPerspective(4,arg1);
}

void MainWindow::on_farValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setPerspective(5,arg1);
}

void MainWindow::on_fovyValue_valueChanged(double arg1)
{
    (void) arg1;
}

void MainWindow::on_isPerspective_stateChanged(int arg1)
{
    ui->canvasOpenGL->toggleProjection();
}

// DRAWING
void MainWindow::on_drawingRValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setRColor(arg1);
}

void MainWindow::on_drawingGValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setGColor(arg1);
}

void MainWindow::on_drawingBValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setBColor(arg1);
}

void MainWindow::on_drawingZValue_valueChanged(double arg1)
{
    ui->canvasOpenGL->setZ(arg1);
}

void MainWindow::on_drawingCheckBox_stateChanged(int arg1)
{
    (void) arg1;
    ui->canvasOpenGL->toggleDrawing();
}

void MainWindow::on_undo_clicked()
{
    ui->canvasOpenGL->undoPolygon();
}

void MainWindow::on_confirm_clicked()
{
    ui->canvasOpenGL->commitPolygon();
}

void MainWindow::on_toningValue_currentIndexChanged(int index)
{
    (void) index;
}

void MainWindow::on_clear_clicked()
{
    ui->canvasOpenGL->clearPolygons();
}

void MainWindow::on_reset_clicked()
{
    ui->canvasOpenGL->resetParameters();
}
