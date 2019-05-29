#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>

class OGLWidget:public QOpenGLWidget
{
private:
    GLint width, height;

    GLfloat colors[6][3] = {
        {1.,0.,0.},
        {0.,1.,0.},
        {0.,0.,1.},
        {1.,1.,0.},
        {1.,0.,1.},
        {0.,1.,1.}
    };

    GLfloat faces[6][4][3] = {
        {{0.5,0.5,0.5},{0.5,-0.5,0.5},{-0.5,-0.5,0.5},{-0.5,0.5,0.5}},
        {{0.5,0.5,0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5},{-0.5,0.5,0.5}},
        {{0.5,0.5,0.5},{0.5,-0.5,0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5}},
        {{0.5,0.5,-0.5},{0.5,-0.5,-0.5},{-0.5,-0.5,-0.5},{-0.5,0.5,-0.5}},
        {{0.5,-0.5,0.5},{0.5,-0.5,-0.5},{-0.5,-0.5,-0.5},{-0.5,-0.5,0.5}},
        {{-0.5,0.5,0.5},{-0.5,-0.5,0.5},{-0.5,-0.5,-0.5},{-0.5,0.5,-0.5}}
    };
public:
    OGLWidget(QWidget* parent);

protected:
    void initializeGL();
    void resizeGL(GLint w, GLint h);
    void paintGL();
};

#endif // OGLWIDGET_H
