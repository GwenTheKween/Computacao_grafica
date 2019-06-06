#include "canvasopengl.h"

//==============================================================================================================================
//PUBLIC FUNCTIONS

CanvasOpenGL::CanvasOpenGL(QWidget* parent):QOpenGLWidget(parent)
{
    drawing = false;
    currentPolygon = new Polygon;
}

void CanvasOpenGL::toggleDrawing(){
    drawing = !drawing;
}

void CanvasOpenGL::setParameters()
{

}

void CanvasOpenGL::resetParameters()
{

}

void CanvasOpenGL::toggleProjection()
{

}

void CanvasOpenGL::perspectiveGL()
{

}

void CanvasOpenGL::LookAt(){

}

void CanvasOpenGL::lineLow(int x1,int y1, int x2,int y2){
    int d,dx,dy,incY;
    dx = x2-x1;
    dy = y2-y1;
    incY = 1;
    if(dy < 0){
        incY = -1;
        dy = -dy;
    }
    d = 2*dy - dx;
    while(x1< x2){
        if(d<=0){
            d += 2*dy;
            x1 ++;
        }else{
            d += 2*(dy-dx);
            x1 ++;
            y1+=incY;
        }
        glVertex2i(x1,y1);
    }
}

void CanvasOpenGL::lineHigh(int x1,int y1, int x2,int y2){
    int d,dx,dy,incX;
    dx = x2-x1;
    dy = y2-y1;
    incX = 1;
    if(dx < 0){
        incX = -1;
        dx = -dx;
    }
    d = 2*dx - dy;
    while(y1< y2){
        if(d<=0){
            d += 2*dx;
            y1++;
        }else{
            d += 2*(dx-dy);
            x1 +=incX;
            y1++;
        }
        glVertex2i(x1,y1);
    }
}

void CanvasOpenGL::drawLines(vector<vector<float> > &vertices)
{
    int x1,x2,y1,y2;
    vector<vector<float> > loop(vertices);
    loop.push_back(vertices[0]);
    for(unsigned int i=0;i<loop.size()-1; i++){
        x1 = loop[i][0];
        y1 = loop[i][1];
        x2 = loop[i+1][0];
        y2 = loop[i+1][1];
        qDebug()<<x1<<y1<<x2<<y2;

        qDebug()<<x1<<y1<<x2<<y2;
        if(abs(x2-x1) > abs(y2-y1)){
            if(x2 < x1){
                x2 ^= x1;
                x1^=x2;
                x2 ^= x1;
                y2^= y1;
                y1 ^= y2;
                y2 ^= y1;
            }
            lineLow(x1,y1,x2,y2);
        }else {
            if(y2<y1){
                x2 ^= x1;
                x1^=x2;
                x2 ^= x1;
                y2^= y1;
                y1 ^= y2;
                y2 ^= y1;
            }
            lineHigh(x1,y1,x2,y2);
        }
    }
}

void CanvasOpenGL::fillPoligon(Polygon* polygon)
{
    (void) polygon;
}

GLdouble CanvasOpenGL::euclidean(QVector3D p1, QVector3D p2)
{
    GLdouble result = GL_DOUBLE;
    (void) p1;
    (void) p2;
    return result;
}

void CanvasOpenGL::reset()
{

}

void CanvasOpenGL::initializeGL()
{
}

void CanvasOpenGL::resizeGL(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 600.0, 0.0, -1.0, 10.0);
}

void CanvasOpenGL::paintGL() {
    glClearColor(0.0,0.0,0.0,0.0);
    if(drawing){
        glBegin(GL_POINTS);
        glPointSize(5.0f);
        glColor3d(1.0,0.5,0.2);
        if(currentPolygon->vertices.size() > 1)
            drawLines(currentPolygon->vertices);
        glEnd();
    }
    glFlush();
}

void CanvasOpenGL::mouseMoveEvent(QMouseEvent *event)
{
    (void) event;
}

void CanvasOpenGL::mousePressEvent(QMouseEvent *event)
{
    if(drawing){
        vector<float> vec;
        vec.resize(3);
        vec[0] = event->x();
        vec[1] = event->y();
        vec[2] = 0;
        qDebug()<<event->x()<<event->y();
        currentPolygon->vertices.push_back(vec);
        this->update();
    }
}

void  CanvasOpenGL::wheelEvent (QWheelEvent * event)
{
    (void) event;
}
