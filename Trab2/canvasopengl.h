#ifndef CANVASOPENGL_H
#define CANVASOPENGL_H

// Qt Libs
#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPoint>
#include <QVector3D>
#include <QMatrix4x4>
#include <QDebug>

// C Libs
#include <vector>
#include <stdlib.h>
#include <math.h>

// Custom Structs
#include "structs.h"


using namespace std;

class CanvasOpenGL : public QOpenGLWidget
{
public:
    CanvasOpenGL(QWidget*);
    ~CanvasOpenGL();

    void toggleDrawing();
    void commitPolygon();
    void setZ(double);

    void setRColor(double);
    void setGColor(double);
    void setBColor(double);

private:
    bool drawing;
    float currZ;
    float currColor[3];
    // VIEWING
    GLint height, width;
    GLdouble
        hMin,   hMax,
        vMin,   vMax,
        near,   far,
        aspect, fovY;
    void setParameters();
    void resetParameters();
    void toggleProjection ();
    void perspectiveGL();

    // OBSERVER
    QVector3D *up, *eye, *center;
    GLfloat xRot, yRot, zRot;
    QPoint lastPos;
    void LookAt();

    //poligonos
    Polygon* currentPolygon;
    vector<Polygon*> polygons;

    // SCANLINE
    void drawLines(vector<vector<float> > &vertices);
    void lineLow(int, int, int, int);
    void lineHigh(int, int, int, int);
    void fillPoligon(Polygon* polygon);

    // ADT
    vector<Edge*> edgeTable;
    vector<GLint> activeEdgeList;

    // HELPERS
    const GLdouble pi = 4*atan(1); //mesma precisao, mais facil de entender.
    GLdouble euclidean (QVector3D, QVector3D);
    void reset();

protected:
    // OpenGL
    void initializeGL();
    void resizeGL(GLint w, GLint h);
    void paintGL();

    // Qt Events
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent (QWheelEvent * event);
};

#endif // CANVASOPENGL_H
