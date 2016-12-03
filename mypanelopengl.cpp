#include "mypanelopengl.h"
#include <cmath>
#include <iostream>
#include <QVector4D>
#include <fstream>



using namespace cs40;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QOpenGLWidget(parent) {

    /* not much to do here */
    m_shaderProgram=NULL;
    m_vertexShader=NULL;
    m_fragmentShader=NULL;
    m_matrix.setColumn(3,QVector4D(-1,1,0,1));

    //Drawing modes
    m_currentMode=MOVING;  //MOVING?
    m_prevMode=MOVING;
    m_prevmouse = vec2(0,0);

    m_timer = NULL;
    m_circle = NULL;
}

MyPanelOpenGL::~MyPanelOpenGL(){
    destroyShaders();
    /* free all the shapes */
    while(m_shapes.size() > 0 ){
        delete m_shapes.last();
        m_shapes.pop_back();
    }
    if(m_timer) {delete m_timer; m_timer = NULL; }
    if(m_circle){ delete m_circle; m_circle=NULL; }
    // if(m_texture){ delete m_texture; m_texture = NULL; }
}

void MyPanelOpenGL::initializeGL()
{
    glEnable(GL_CULL_FACE); /* required, culling *disabled* by default */
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);  /* optional, GL_BACK is default */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    createShaders();

    float x;
    float y;
    float rad = 0.1;
    int counter = 1;
    // Circle* circ;
    // for (y = -1; y > 1; y = y + 0.1) {
    //     for (x = -1; x > 1; x = x + .1) {
    //         vec2 center = vec2(x,y);
    //         circ = new Circle(m_shaderProgram, center, rad);
    //         m_shapes.append(circ);
    //         float randx = ((rand() % 2) - 1)/2;  //Between -1 and 1
    //         float randy = ((rand() % 2) - 1)/2;
    //         vec2 vel = vec2(randx, randy);   //Create random velocity to travel
    //         cs40::Planet* newcircle = new cs40::Planet(counter, center, rad, vel);
    //         m_info.append(newcircle);
    //         counter += 1;
    //     }
    // }

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    m_timer->start(10);

}

void MyPanelOpenGL::resizeGL(int w, int h)
{
    glViewport(0,0,w, h);
    m_matrix.setColumn(0,QVector4D(2./w,0,0,0));
    m_matrix.setColumn(1,QVector4D(0,-2./h,0,0));
    update();
}

void MyPanelOpenGL::paintGL(){

    if(!m_shaderProgram){
        return; /* give up */
    }

    glClear(GL_COLOR_BUFFER_BIT);

    m_shaderProgram->bind();
    m_shaderProgram->setUniformValue("mview", m_matrix);


    /* draw all the shapes */

    for(int i=0; i<m_shapes.size(); i++){
        m_shapes[i]->draw();
    }

    glFlush();
}

void MyPanelOpenGL::updateTime(){
    //Move All Planets by delHr
    for(int i = 0; i < m_info.size(); i++)
    {
        // m_info[i]->move(1);
    }
    update();
}

void MyPanelOpenGL::createShaders(){

    destroyShaders(); //get rid of any old shaders

    m_vertexShader = new QOpenGLShader(QOpenGLShader::Vertex); /* creates new vertex shader*/
    if (!m_vertexShader->compileSourceFile("shaders/vshader.glsl")){
        qWarning() << m_vertexShader->log();
    }

    m_fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment); /*creates new fragment shader*/
    if(!m_fragmentShader->compileSourceFile("shaders/fshader.glsl")){
        qWarning() << m_fragmentShader->log();
    }

    m_shaderProgram = new QOpenGLShaderProgram();
    m_shaderProgram->addShader(m_vertexShader);
    m_shaderProgram->addShader(m_fragmentShader);

    if(!m_shaderProgram->link()){
        qWarning() << m_shaderProgram->log() << endl;
    }

}

void MyPanelOpenGL::destroyShaders(){

    delete m_vertexShader; m_vertexShader=NULL;
    delete m_fragmentShader; m_fragmentShader=NULL;

    if(m_shaderProgram){
        m_shaderProgram->release();
        delete m_shaderProgram; m_shaderProgram=NULL;
    }
}

// This method allows the user to move the clicked shapes
// to a new location based on the previous location and the newest location
// clicked
void MyPanelOpenGL::mouseMoveEvent(QMouseEvent *event)
{
    // if (m_currentMode == MOVING)
    if (m_shapes.size() != 0)
    // {
    //     vec2 pos(event->localPos().x(),event->localPos().y());
    //     int curr_shape = 999;
    //     for (int i = 0; i<m_shapes.size(); i++){
    //         if (m_shapes[i]->contains(pos)){
    //             curr_shape = i;
    //         }
    //     }
    //     if (curr_shape != 999) {
    //         m_shapes[curr_shape]->move(pos[0]-m_prevmouse[0],pos[1]-m_prevmouse[1]);
    //     }
    //     m_prevmouse = pos;
    // }
    {
        vec2 pos(event->localPos().x(),event->localPos().y());
        float difx = pos[0] - m_prevmouse[0];
        float dify = pos[1] - m_prevmouse[1];
        m_shapes[0]->move(difx*0.1, dify*0.1);
        m_prevmouse = pos;
    }
    update();
}

// This method creates, deletes, and changes color of the shapes based
// on the current mode and the color, by taking in the user mouse events
// as the locations to implement the changes
void MyPanelOpenGL::mousePressEvent(QMouseEvent *event){
    vec2 click(event->localPos().x(),event->localPos().y());
    QVector4D worldPoint(click, 0, 1);
    QVector4D clipPoint=m_matrix*worldPoint;
    std::cout << clipPoint.toVector2D() << std::endl;


    app_mode_t mode = m_currentMode;
    if (m_prevMode != m_currentMode){
        m_clicks.clear();

    }
    m_clicks += click;
    m_prevMode = mode;

    //   if (m_currentMode == ADD_CIRCLE)
    //   {
    //   }
    if (m_clicks.size() == 2)
      {
          QVector2D p1 = m_clicks[0];
          QVector2D p2 = m_clicks[1];
          float rad = (p2-p1).length();
          Circle* circ;
          circ = new Circle(m_shaderProgram, p1, rad);
          circ->setColor(vec3(0,0,0));
          m_shapes.append(circ);
        //   m_clicks.clear();
      }
    //   else if (m_currentMode == CHANGE_COLOR)
    //   {
    //       for (int i = m_shapes.size()-1; i >= 0; i--)
    //       {
    //           if (m_shapes[i]->contains(click))
    //           {
    //               m_shapes[i]->setColor(curr_color);
    //           }
    //       }
    //   }
    //   else if (m_currentMode == MOVING)
    //   {
    //       m_prevmouse = click;
    //   }

    update();
}

// These methods update the current mode and the current color
// based on what buttons the user clicks


//
// void MyPanelOpenGL::Sandbox()
// {
//     m_currentMODE = Sandbox;
// }
//
// void MyPanelOpenGL::Singleplayer()
// {
//     m_currentMODE = Singleplayer;
// }
//
// void MyPanelOpenGL::AIFFA()
// {
//     m_currentMODE = AIFFA;
// }
//
// void MyPanelOpenGL::TopScore()
// {
//     m_currentMode = TopScore;
// }
//
// void MyPanelOpenGL::PlayerScore()
// {
//     m_currentMode = PlayerScore;
// }
