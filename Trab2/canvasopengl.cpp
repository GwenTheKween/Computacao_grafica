#include "canvasopengl.h"

//==============================================================================================================================
//PUBLIC FUNCTIONS

CanvasOpenGL::CanvasOpenGL(QWidget* parent):QOpenGLWidget(parent)
{
    currentPolygon = nullptr;
    this->resetParameters();
}

CanvasOpenGL::~CanvasOpenGL(){
    clearPolygons();
    currZ = 0;
    delete currentPolygon;
    currentPolygon = nullptr;
}

void CanvasOpenGL::resetParameters()
{
    drawing = perspective = false;
    currZ = 0;
    if(currentPolygon) delete currentPolygon;
    currentPolygon = new Polygon;
    if(polygons.size()){
        for(unsigned int i=0;i<polygons.size();i++)
            delete polygons[i];
        polygons.clear();
    }
    currColor[0]=currColor[1] = currColor[2] = 0;
    light[0] = light[1] = light[2] = 0;
    observer[0] = observer[1] = observer[2] = 2;
    currTone = 0;
    minX = DEFAULTMINX;
    maxX = DEFAULTMAXX;
    minY = DEFAULTMINY;
    maxY = DEFAULTMAXY;
    minZ = DEFAULTMINZ;
    maxZ = DEFAULTMAXZ;
    width = maxX - minX;
    height = maxY - minY;
    aspect = width / 1.0*height;
}

void CanvasOpenGL::setViewport(){

}

//==============================================================================================================================
//funcoes de desenho pelo usuario

void CanvasOpenGL::toggleDrawing(){
    currentPolygon->vertices.clear();
    drawing = !drawing;
}

void CanvasOpenGL::undoPolygon(){
    if(currentPolygon->vertices.size()){
        currentPolygon->vertices.pop_back();
        this->update();
    }
}

void CanvasOpenGL::commitPolygon(){
    if(drawing){//O botao so funciona se tiver desenhando
        if(currentPolygon->vertices.size() > 2){
            vector<float> z_points;
            for(unsigned int i = 0; i<z_points.size(); i++){
                z_points[0] = currentPolygon->vertices[i][0];
                z_points[1] = currentPolygon->vertices[i][1];
                z_points[2] = currZ;
                currentPolygon->vertices.push_back(z_points);
            }
            currentPolygon->color[0] = currColor[0];
            currentPolygon->color[1] = currColor[1];
            currentPolygon->color[2] = currColor[2];
            currentPolygon->color[3] = 1;
            polygons.push_back(currentPolygon);
            currentPolygon = new Polygon;
        }else{
            currentPolygon->vertices.clear();
        }
        this->update();
    }
}

void CanvasOpenGL::clearPolygons(){
    for(unsigned int i=0;i<polygons.size(); i++){
        delete polygons[i];
    }
    polygons.clear();
}

//==============================================================================================================================
//funcoes de set de parametros

void CanvasOpenGL::setRColor(double val){
    currColor[0] = val;
    currentPolygon->color[0] = currColor[0];
    this->update();
}

void CanvasOpenGL::setGColor(double val){
    currColor[1] = val;
    currentPolygon->color[1] = currColor[1];
    this->update();
}

void CanvasOpenGL::setBColor(double val){
    currColor[2] =  val;
    currentPolygon->color[2] = currColor[2];
    this->update();
}

void CanvasOpenGL::setZ(double newZ){
    currZ = newZ;
}

void CanvasOpenGL::setLightX(double newX){
    light[0] = newX;
    this->update();
}


void CanvasOpenGL::setLightY(double newY){
    light[1] = newY;
    this->update();
}


void CanvasOpenGL::setLightZ(double newZ){
    light[2] = newZ;
    this->update();
}

void CanvasOpenGL::setTonning(int val){
    currTone = val;
}

void CanvasOpenGL::setObserver(int index, double val){
    observer[index] = val;
}

void CanvasOpenGL::setParameters()
{

}

void CanvasOpenGL::setPerspective(int which, double val){
    switch(which){
        case 0:
            minX = val;
            break;
        case 1:
            maxY = val;
            break;
        case 2:
            minY = val;
            break;
        case 3:
            maxY = val;
            break;
        case 4:
            minZ = val;
            break;
        case 5:
            maxZ = val;
    }
}

void CanvasOpenGL::toggleProjection()
{
    perspective = !perspective;
}

void CanvasOpenGL::perspectiveGL()
{
}

//==============================================================================================================================
//Funcao auxiliar para desenhar
void CanvasOpenGL::LookAt(){

}

//==============================================================================================================================
//funcoes para desenhar linhas

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
        // VIEWING
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

//==============================================================================================================================
//funcao para preencher um poligono
void CanvasOpenGL::fillPoligon(Polygon* polygon)
{
    (void) polygon;
}

//==============================================================================================================================
//funcoes basicas do opengl
void CanvasOpenGL::initializeGL()
{

}
void CanvasOpenGL::resizeGL(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void CanvasOpenGL::paintGL() {
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(drawing){
        glBegin(GL_POINTS);
        glPointSize(5.0f);
        glColor3dv(currColor);
        if(currentPolygon->vertices.size() > 1)
            drawLines(currentPolygon->vertices);
        glEnd();
    }else if(perspective){
        GLdouble FW,FH;
        FH = tan(fovY/360 * pi)*maxZ;
        FW = FH * aspect;
        glFrustum(-FW,FW,-FH,FH,minZ,maxZ);
    }else{
        glOrtho(minX,maxX,minY,maxY,minZ,maxZ);
    }
    for(unsigned int i=0;i<polygons.size(); i++){
        //essa secao esta aqui por motivos de debug. Aqui que vai ser colocada a chamada para fill polygon
        //unsigned int faceVertexCount = polygons[i]->vertices.size()/2;
        glBegin(GL_POINTS);
        glColor4dv(polygons[i]->color);
        drawLines(polygons[i]->vertices);
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
        currentPolygon->vertices.push_back(vec);
        this->update();
    }
}

void  CanvasOpenGL::wheelEvent (QWheelEvent * event)
{
    (void) event;
}
