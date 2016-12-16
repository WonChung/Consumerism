#include "mypanelopengl.h"
#include <cmath>
#include <iostream>
#include <QVector4D>
#include <stdlib.h>
#include "options.h"
#include "score.h"
#include <QGraphicsTextItem>
#include <QFont>
// #include "triangle.h"
// #include "rectangle.h"
// #include "line.h"

using namespace cs40;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QOpenGLWidget(parent) {

    /* not much to do here */
    m_shaderProgram=NULL;
    m_vertexShader=NULL;
    m_fragmentShader=NULL;
    m_matrix.setColumn(3,QVector4D(-1,1,0,1));
    m_texture = NULL;

    //Drawing modes
    m_currentMode=SINGLEPLAYER;
    m_prevMode=SINGLEPLAYER;
    m_prevmouse = vec2(0,0);
    m_maxvel = 10;

    //Timer for animation
    m_timer = NULL;
}

MyPanelOpenGL::~MyPanelOpenGL(){
    destroyShaders();
    /* free all the shapes */
    while(m_shapes.size() > 0 ){
        delete m_shapes.last();
        m_shapes.pop_back();
    }
    if(m_texture){delete m_texture; m_texture = NULL; }
    if(m_timer) {delete m_timer; m_timer = NULL; }
}

void MyPanelOpenGL::initializeGL()
{
    //testing CCW
    // glEnable(GL_CULL_FACE); /* required, culling *disabled* by default */
    // glFrontFace(GL_CW);
    // glCullFace(GL_BACK);  /* optional, GL_BACK is default */

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    createShaders();

    // int modenum = options.getmode();
    float x = 0;
    float y = 0;

    float rad = 10;
    Circle* circ;

    // Screen starts top left, from 0-1000 in x, 0-600 in y
    for (y = 100; y < 600; y = y + 100) {
        for (x = 100; x < 1000; x = x + 100) {
            vec2 center = vec2(x,y);
            float randx = ((rand() % 101) - 50)/50.;  //Between -1.00 and 1.00 in 0.02 inc
            float randy = ((rand() % 101) - 50)/50.;
            vec2 vel = vec2(randx,randy);
            vel.normalize();
            vel = vel;
            circ = new Circle(m_shaderProgram, center, rad, vel);
            circ->setColor(QVector3D(0,0,0));
            m_shapes.append(circ);
        }
    }
    std::cout << m_shapes.size() << std::endl;

    m_shaderProgram->bind();

    // m_score = new Score();

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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shaderProgram->bind();
    m_shaderProgram->setUniformValue("mview", m_matrix);

    /* draw all the shapes */
    for(int i=0; i<m_shapes.size(); i++){
        // m_texture = getTexture(m_shapes[i]);
        // if (m_texture != NULL)
        // {
        //     m_texture->bind();
        // }
        // glColor3f(1,0,0);

        m_shapes[i]->draw();

    }
    glFlush();
}

void MyPanelOpenGL::updateTime(){
    //Height and Width of window to avoid problems.
    GLint dims[4] = {0};
    glGetIntegerv(GL_VIEWPORT, dims);

    //Update all Circle positions by time increment and vel
    for(int i = 1; i < m_shapes.size(); i++)
    {
      if (m_currentMode != SANDBOX)
      //Motion of circles based on velocity
      {
        vec2 velo = m_shapes[i]->getvel();
        m_shapes[i]->move(velo.x()*1,velo.y()*1);
        m_shapes[i]->setcenter(velo);
        m_shapes[i]->wrap(dims[2],dims[3]);
      }
    }

      //Comparing your ball and other balls.
      //Singleplayer mode.
    if (m_currentMode == SINGLEPLAYER || m_currentMode == SANDBOX)
    {
      m_prevMode = m_currentMode;
      // for(int i = 1; i < m_shapes.size(); i++)
      // {
      //   vec2 cent = m_shapes[0]->getcenter();
      //   float rad = m_shapes[0]->getrad();
      //   vec2 centtwo = m_shapes[i]->getcenter();
      //   float radtwo = m_shapes[i]->getrad();
      //   float dist = (cent-centtwo).length();
      //   float raddist = std::fabs(rad+radtwo);
      //   if (dist <= raddist)
      //   {
      //     if (rad >= radtwo)
      //     {
      //       float res = pow(rad,2) + pow(radtwo,2);
      //       res = sqrt(res);
      //       Circle* circ2 = new Circle(m_shaderProgram, m_shapes[0]->getcenter(),
      //       res, m_shapes[0]->getvel());
      //       m_shapes.removeAt(0);
      //       m_shapes.prepend(circ2);  //Replacing old circ with new circ.
      //       m_shapes.removeAt(i);
      //       i--;  //Because ball is removed, scale back one position
      //     }
      //   }
      // }
      for (int i = 0; i<m_shapes.size()-1; i++)  //Starting circle
      {
        //Circle variables are held
        vec2 cent = m_shapes[i]->getcenter();
        float rad = m_shapes[i]->getrad();
        for (int j = i + 1; j<m_shapes.size(); j++)
        {
          vec2 centtwo = m_shapes[j]->getcenter();
          float radtwo = m_shapes[j]->getrad();
          float dist = (cent-centtwo).length();
          float raddist = std::abs(rad+radtwo);
          float res = pow(rad,2) + pow(radtwo,2);
          res = sqrt(res);
          if (dist <= raddist)
          {
            if (rad >= radtwo) {
              Circle* circ2 = new Circle(m_shaderProgram, m_shapes[i]->getcenter(),
                                        res, m_shapes[i]->getvel());
              if (i == 0) {
                circ2->setColor(QVector3D(1,0,0));
              }
              m_shapes.removeAt(i);
              m_shapes.insert(i, circ2);
              m_shapes.removeAt(j);
              j--;
            } else { //Update 2nd object, replace 1st.
              if (i == 0) {
                m_currentMode = GAMEOVER;
                i = m_shapes.size();
                j = m_shapes.size();
              } else {
                Circle* circ2 = new Circle(m_shaderProgram, m_shapes[j]->getcenter(),
                res, m_shapes[j]->getvel());
                m_shapes.removeAt(j);
                m_shapes.insert(j, circ2);
                m_shapes.removeAt(i);
                j = m_shapes.size();
                i--;
              }
            }
          }
        }
      }
    }

    //No human ball component
    //AI consume each other
    else if (m_currentMode == AI_FFA)
    {
      //Remove singleplayer generated ball.
      if (m_clicks.size() >= 2)
      {
        m_shapes.removeAt(0);
        m_clicks.clear();
      }
      m_prevMode = m_currentMode;
      for (int i = 0; i<m_shapes.size()-1; i++)  //Starting circle
      {
        //Circle variables are held
        vec2 cent = m_shapes[i]->getcenter();
        float rad = m_shapes[i]->getrad();
        for (int j = i + 1; j<m_shapes.size(); j++)
        {
          vec2 centtwo = m_shapes[j]->getcenter();
          float radtwo = m_shapes[j]->getrad();
          float dist = (cent-centtwo).length();
          float raddist = std::abs(rad+radtwo);
          float res = pow(rad,2) + pow(radtwo,2);
          res = sqrt(res);
          if (dist <= raddist)
          {
            if (rad >= radtwo) {

              Circle* circ2 = new Circle(m_shaderProgram, m_shapes[i]->getcenter(),
                                        res, m_shapes[i]->getvel());
              m_shapes.removeAt(i);
              m_shapes.insert(i, circ2);
              m_shapes.removeAt(j);
              j--;
            } else { //Update 2nd object, replace 1st.
              Circle* circ2 = new Circle(m_shaderProgram, m_shapes[j]->getcenter(),
              res, m_shapes[j]->getvel());
              m_shapes.removeAt(j);
              m_shapes.insert(j, circ2);
              m_shapes.removeAt(i);
              j = m_shapes.size();
              if (i != 0)   //Edge case
              {
                i--;
              }
            }
          }
        }
      }
    }

    else if (m_currentMode == ADD_CIRCLES){
      GLint dims[4] = {0};
      glGetIntegerv(GL_VIEWPORT, dims);
      Circle* circ;
      float rad = 10;

      //Regimented Creation
      if (m_prevMode != SANDBOX) {
        for (int y = dims[3]/10; y < dims[3]; y = y + dims[3]/5) {
          for (int x = 100; x < dims[2]; x = x + dims[2]/5) {
            vec2 center = vec2(x,y);
            float randx = ((rand() % 101) - 50)/50.;  //Between -1.00 and 1.00 in 0.02 inc
            float randy = ((rand() % 101) - 50)/50.;
            vec2 vel = vec2(randx,randy);
            vel.normalize();
            vel = vel;
            circ = new Circle(m_shaderProgram, center, rad, vel);
            m_shapes.append(circ);
          }
        }
      } else {
        //Random Creation
        for (int i = 0; i < 50; i++) {
          int xmod = dims[2] - rad;
          int ymod = dims[3] - rad;
          float x = rand() % xmod;  //Between -1.00 and 1.00 in 0.02 inc
          float y = rand() % ymod;
          vec2 center = vec2(x,y);
          float randx = ((rand() % 101) - 50)/50.;  //Between -1.00 and 1.00 in 0.02 inc
          float randy = ((rand() % 101) - 50)/50.;
          vec2 vel = vec2(randx,randy);
          vel.normalize();
          vel = vel*3;
          circ = new Circle(m_shaderProgram, center, rad, vel);
          m_shapes.append(circ);
        }
      }
      m_currentMode = m_prevMode;
    }

    else if (m_currentMode == RESET_SIZE) {
      if (m_prevMode != SINGLEPLAYER && m_prevMode != SANDBOX) {
        m_currentMode = m_prevMode;
        return;
      } else {
        Circle* circ3;
        circ3 = new Circle(m_shaderProgram, m_shapes[0]->getcenter(), 15,
                          m_shapes[0]->getvel());
        circ3->setColor(QVector3D(1,0,0));
        m_shapes.removeAt(0);
        m_shapes.insert(0,circ3);
      }
      m_currentMode = m_prevMode;
    }

    else if (m_currentMode == GAMEOVER) {
      while (m_shapes.size() > 1) {
        m_shapes.removeLast();
      }
      std::cout << "GAME OVER! Your end score was " << m_shapes[0]->getrad() << std::endl;
      m_currentMode = m_prevMode;
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

// void MyPanelOpenGL::keyPressEvent(QKeyEvent *event)
// {
//     GLint dims[4] = {0};
//     glGetIntegerv(GL_VIEWPORT, dims);
//     switch(event->key()){
//     case Qt::Key_5:
//         break;
//     // Added keys to pan and zoom
//     case Qt::Key_W:
//         m_shapes[0]->move(0,dims[3]/100);
//         m_shapes[0]->setcenter(vec2(0,dims[3]/100));
//         update();
//         break;
//     case Qt::Key_S:
//         m_shapes[0]->move(0,-dims[3]/100);
//         m_shapes[0]->setcenter(vec2(0,-dims[3]/100));
//         update();
//         break;
//     case Qt::Key_A:
//         m_shapes[0]->move(dims[2]/100,0);
//         m_shapes[0]->setcenter(vec2(dims[2]/100,0));
//         update();
//         break;
//     case Qt::Key_D:
//         m_shapes[0]->move(-dims[2]/100,0);
//         m_shapes[0]->setcenter(vec2(-dims[2]/100,0));
//         update();
//         break;
//     default:
//         QWidget::keyPressEvent(event); /* pass to base class */
//     }
//     update();
// }

void MyPanelOpenGL::mouseMoveEvent(QMouseEvent *event)
{
  if (m_clicks.size() >= 2)
  {
      GLint dims[4] = {0};
      glGetIntegerv(GL_VIEWPORT, dims);
      // if (m_currenttrial == EASYMODE)
      if (m_currentMode == AI_FFA)
      {
        m_prevmouse = vec2(dims[2]/2, dims[3]/2);
      }
      // else if (m_currenttrial == HARDMODE)
      else if (m_currentMode == SINGLEPLAYER || m_currentMode == SANDBOX)
      {
        m_prevmouse = vec2(m_shapes[0]->getcenter().x(), m_shapes[0]->getcenter().y());
      }
      vec2 pos(event->localPos().x(),event->localPos().y());
      float difx = pos[0] - m_prevmouse[0];
      float dify = pos[1] - m_prevmouse[1];
      m_shapes[0]->move(difx*.01, dify*.01);

      m_shapes[0]->setcenter(vec2(difx*.01, dify*.01));

      /* Buggy attempt to constrain the user-constrolled circle */
      // float radius = m_shapes[0]->getrad();
      // if ((m_shapes[0]->getcenter().x() - radius) > 0)
      // {
      //   m_shapes[0]->setcenter(vec2(0,dify*0.01));
      // }
      // else if ((m_shapes[0]->getcenter().x() + radius) > dims[2])
      // {
      //   m_shapes[0]->setcenter(vec2(dims[2]-m_shapes[0]->getcenter().x(),dify*0.01));
      // }
      // else if (m_shapes[0]->getcenter().y() + radius < 0)
      // {
      //   m_shapes[0]->setcenter(vec2(difx*0.01,0));
      // }
      // else if ((m_shapes[0]->getcenter().y() + radius) > dims[3])
      // {
      //   m_shapes[0]->setcenter(vec2(difx*0.01,dims[3]-m_shapes[0]->getcenter().y()));
      // }
      // else
      // {
        // m_shapes[0]->setcenter(vec2(difx*.01, dify*.01));
      // }


      // update();
  }
}

void MyPanelOpenGL::mousePressEvent(QMouseEvent *event){
    vec2 click(event->localPos().x(),event->localPos().y());
    QVector4D worldPoint(click, 0, 1);
    QVector4D clipPoint=m_matrix*worldPoint;


    if (m_currentMode != SINGLEPLAYER && m_currentMode != SANDBOX)
      {
        return;
      } else {
        std::cout << clipPoint.toVector2D() << std::endl;
        m_clicks += click;
        m_prevmouse = click;
        if (m_clicks.size() == 2)
        {
          QVector2D p1 = m_clicks[0];
          QVector2D p2 = m_clicks[1];
          float rad = (p2-p1).length();
          // QVector3D curr_color = QVector3D(0,1,0);
          Circle* circ;
          circ = new Circle(m_shaderProgram, p1, rad, vec2(0,0));
          // circ->setColor(curr_color);
          circ->setColor(QVector3D(1,0,0));
          // m_texture = m_texture = new QOpenGLTexture(QImage("door.jpg").mirrored());
          // m_texture->bind();
          // circ->setColor(1,0,0);
          m_shapes.push_front(circ);
          // m_clicks.clear();
        }
      }
    update();
}

// Player Circle is last in the list

void MyPanelOpenGL::Singleplayer()
{
    m_currentMode = SINGLEPLAYER;
    // The user circle can "consume" other circles

    // If the user circle radius is equal to greater than that of
    // the circle being consumed, then the user circle can "consume" it
    // Increment Score
    // When radius >
    // if (user_score < radius of user circle)
    // {
    //     user_score = radius of user circle;
    // }

    // If the user circle radius is smaller than that of the circle being
    // consume, then the user circle dies and it's GAMEOVER
}

void MyPanelOpenGL::Sandbox()
{
    m_currentMode = SANDBOX;
    // The user circle is the only one that can move and "consume" other circles

    // Other circles don't move
    // Same Rule as Above (remember to increment score)
}

void MyPanelOpenGL::AIFFA()
{
    m_currentMode = AI_FFA;
    // There is no user circle
    // The other circles move and consume each other
    // There is no score
}

void MyPanelOpenGL::Add_Circles()
{
  m_currentMode = ADD_CIRCLES;
}

void MyPanelOpenGL::Reset_Size()
{
  m_currentMode = RESET_SIZE;
}
// void MyPanelOpenGL::updateTopScore()
// {
//
// }
//
// void MyPanelOpenGL::updatePlayerScore()
// {
//
// }

// void MyPanelOpenGL::setTexture(cs40::Circle* circ)
// {
//     if(m_texture)
//     {
//         delete m_texture;
//     }
//     m_texture = new QOpenGLTexture(QImage("galaxy.jpg").mirrored());
//     // m_texture->bind();
// }
//
// QOpenGLTexture* MyPanelOpenGL::getTexture(cs40::Circle* circ)
// {
//     return m_texture;
// }
// void MyPanelOpenGL::updatePlayerScore()
// {
//
// }
