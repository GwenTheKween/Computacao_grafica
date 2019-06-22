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

// Custom Libs
#include "AET.h"


using namespace std;

class CanvasOpenGL : public QOpenGLWidget
{
public:
    CanvasOpenGL(QWidget*);
    ~CanvasOpenGL();

    void toggleDrawing();
    void undoPolygon();
    void commitPolygon();
    void setZ(double);

    void setRColor(double);
    void setGColor(double);
    void setBColor(double);
    void resetParameters();

    void setLightX(double);
    void setLightY(double);
    void setLightZ(double);
    void setTonning(int val);

    void toggleProjection ();
    void setViewport();
    void setObserver(int,double);

    void clearPolygons();
    void setPerspective(int,double);

private:
    bool drawing, perspective;
    double  currZ;
    double  currColor[3];
    double light[3];
    int currTone;
    // VIEWING
    GLint height, width;
    GLdouble
        minX,   maxX,
        minY,   maxY,
        minZ,   maxZ,
        aspect, fovY;
    void setParameters();
    void perspectiveGL();

    // OBSERVER
    QVector3D up, eye, center;
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
