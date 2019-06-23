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
    eye.setX(0);
    eye.setY(0);
    eye.setZ(0);
    center.setX(0);
    center.setY(0);
    center.setZ(-1);
    up.setX(0);
    up.setY(-1);
    up.setZ(0);
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
    update();
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
    switch(index){
        case 0:
            eye.setX(val);
            break;
        case 1:
            eye.setY(val);
            break;
        case 2:
            eye.setZ(val);
    }
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
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    QMatrix4x4 lookAtMatrix;
    lookAtMatrix.lookAt(eye,center,up);
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
    vector<float> poligonPoints;
    vector<float> poligonFaceXY;
    vector<float> poligonFaceXYZ;
    int facesNumber = Polygon->vertices.size/2;
    Polygon *poligonFaces = NULL;
    int z_position = 0;
    int x_init = 0;
    int x_end = 0;

    //face frontal do poligno, fixa o eixo z e trabalha xy
    for(int i = 0; i<facesNumber; i++) {
        poligonPoints.push_back(Polygon->vertices[i][0]);
        poligonPoints.push_back(Polygon->vertices[i][1]);
    }
    z_position = Polygon->vertices[0][2];
    poligonFaceXY = PoliFill(poligonPoints);
    //acrescenta o eixo Z no vetor de pontos para preenchimento da face frontal
    for(int i = 0; i<poligonFaceXY.size-1; i+=2) {
        poligonFaceXYZ.push_back(poligonFaceXY[i]);
        poligonFaceXYZ.push_back(poligonFaceXY[i+1]);
        poligonFaceXYZ.push_back(z_position);
    }
    //adiciona face frontal ao poligono com todas as faces
    poligonFaces->vertices.push_back(poligonFaceXYZ);
    poligonPoints.clear();
    poligonFaceXY.clear();
    poligonFaceXYZ.clear();
    

    //preenche faces laterais do poligono, fixa o eixo x e trabalha yz
    //eixo z vira x e eixo y continua sendo y para o algoritmo scanline
    //cada face lateral eh indicada por 4 pontos, sendo dois da face fronta e dois da face de fundo
    for(int i = 0; i<facesNumber; i++) {
        //faces laterais menos a ultima face que eh a ligacao do ultimo com o primeiro
        if(i<facesNumber-1) {
            poligonPoints.push_back(Polygon->vertices[i][2]);
            poligonPoints.push_back(Polygon->vertices[i][1]);
            poligonPoints.push_back(Polygon->vertices[i+1][2]);
            poligonPoints.push_back(Polygon->vertices[i+1][1]);
            poligonPoints.push_back(Polygon->vertices[i+facesNumber][2]);
            poligonPoints.push_back(Polygon->vertices[i+facesNumber][1]);
            poligonPoints.push_back(Polygon->vertices[i+facesNumber+1][2]);
            poligonPoints.push_back(Polygon->vertices[i+facesNumber+1][1]);
            //salva x inicial e final dos pontos da face frontal para calculo dos valores de x relativos a yz
            //ponto x varia de um pixel a cada linha do scanline ateh chegar no x do ponto final da face frontal
            x_init = Polygon->vertices[i][0];
            x_end = Polygon->vertices[i+1][0];
        //ultima face do poligono
        }else {
            poligonPoints.push_back(Polygon->vertices[i][2]);
            poligonPoints.push_back(Polygon->vertices[i][1]);
            poligonPoints.push_back(Polygon->vertices[0][2]);
            poligonPoints.push_back(Polygon->vertices[0][1]);
            poligonPoints.push_back(Polygon->vertices[facesNumber][2]);
            poligonPoints.push_back(Polygon->vertices[facesNumber][1]);
            poligonPoints.push_back(Polygon->vertices[i+facesNumber][2]);
            poligonPoints.push_back(Polygon->vertices[i+facesNumber][1]);
            x_init = Polygon->vertices[i][0];
            x_end = Polygon->vertices[0][0];
        }    
        poligonFaceXY = PoliFill(poligonPoints);
        if(x_init != x_end) {
            //calcula o x para cada yz da face onde o x eh o x anterior + 1 pixel ate chegar no x final
            for(int i = 0; i<poligonFaceXY.size-1; i+=2) {
                poligonFaceXYZ.push_back(x_init);
                poligonFaceXYZ.push_back(poligonFaceXY[i+1]);
                poligonFaceXYZ.push_back(poligonFaceXY[i]);
                if((poligonFaceXY[i+1] != poligonFaceXY[i+2]) && (x_init < x_end))
                    x_init++;
                
            }        
        }
        poligonFaces->vertices.push_back(poligonFaceXYZ);
        poligonPoints.clear();
        poligonFaceXY.clear();
        poligonFaceXYZ.clear();
    }

    //face do fundo do poligono fixa o eixo z e trabalha xy
    for(int i = 0; i<facesNumber; i++) {
        poligonPoints.push_back(Polygon->vertices[i][0]);
        poligonPoints.push_back(Polygon->vertices[i][1]);
    }
    z_position = Polygon->vertices[0][2];
    poligonFaceXY = PoliFill(poligonPoints);
    //acrescenta o eixo Z no vetor de pontos para preenchimento da face de fundo
    for(int i = 0; i<poligonFaceXY.size-1; i+=2) {
        poligonFaceXYZ.push_back(poligonFaceXY[i]);
        poligonFaceXYZ.push_back(poligonFaceXY[i+1]);
        poligonFaceXYZ.push_back(z_position);
    }
    //adiciona face de fundo ao poligono com todas as faces
    poligonFaces->vertices.push_back(poligonFaceXYZ);
    poligonPoints.clear();
    poligonFaceXY.clear();
    poligonFaceXYZ.clear();
    //(void) polygon;
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
    glOrtho(minX,maxX,maxY,minY,minZ,maxZ);
}

void CanvasOpenGL::paintGL() {
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(perspective && !drawing){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLdouble FW,FH;
        FH = tan(fovY/360 * pi)*maxZ;
        FW = FH * aspect;
        glFrustum(-FW,FW,-FH,FH,minZ,maxZ);
    }else{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(minX,maxX,maxY,minY,minZ,maxZ);
    }
    //this->LookAt();
    if(drawing){
        glBegin(GL_POINTS);
        glPointSize(5.0f);
        glColor3dv(currColor);
        if(currentPolygon->vertices.size() > 1)
            drawLines(currentPolygon->vertices);
        glEnd();
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
        qDebug()<<event->x() << event->y();
        currentPolygon->vertices.push_back(vec);
        this->update();
    }
}

void  CanvasOpenGL::wheelEvent (QWheelEvent * event)
{
    (void) event;
}
