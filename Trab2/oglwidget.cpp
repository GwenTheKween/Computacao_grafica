#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget* parent):QOpenGLWidget(parent){

}

void OGLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, this->width, this->height);
}

void OGLWidget::paintGL() {

    //this->setParameters();

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //glRotated(this->xRot, 1.0, 0.0, 0.0); // X
    //glRotated(this->yRot, 0.0, 1.0, 0.0); // Y
    //glRotated(this->zRot, 0.0, 0.0, 1.0); // Z

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) {
        glColor3fv(this->colors[i]);
        for(int j = 0; j < 4; j++) {
            glVertex3fv(this->faces[i][j]);
        }
    }
    glEnd();

    glFlush();
}

void OGLWidget::resizeGL(GLint w, GLint h) {
    this->width = w;
    this->height = h;
    //this->aspect = this->width/this->height;

    this->update();
}
