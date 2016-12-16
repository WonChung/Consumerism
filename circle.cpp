#include "circle.h"
#include <iostream>
using namespace cs40;

Circle::Circle(QOpenGLShaderProgram* const prog,
  const vec2& center, float radius, const vec2& vel) {
    m_prog = prog;
    m_pts[0] = center;
    m_rad = radius;
    m_vel = vel;
    //Made array of arbitrary value (100) for m_pts for polygon creation
    //For loop to pass through m_pts values.
    for (int i=1;i<100;i++){
        float x = m_pts[0].x()+radius*cos(2*3.14*i/97);
        float y = m_pts[0].y()+radius*sin(2*3.14*i/97);
        m_pts[i] = vec2(x,y);
    }
/*The way the for loop is written guarantees that the points are created
 *in a ccw order already.  */

    if (initVBO()) {
        /* IDs created */

        m_vao->bind();
        m_prog->bind();
        m_vbo->bind();
        m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vbo->allocate(m_pts, 100*sizeof(QVector2D));

        m_prog->enableAttributeArray("vPosition");
        m_prog->setAttributeBuffer("vPosition", GL_FLOAT, 0, 2, 0);

        m_prog->release();
        m_vao->release();
    }
}

Circle::Circle(const Circle *other){

    m_prog = other->m_prog;

    for (int i = 0;i<100;i++){
        m_pts[i] = other->m_pts[i];
    }


    m_color = other->m_color;
    m_displacement = other->m_displacement;
    m_visible = other->m_visible;

    if (initVBO()) {

        m_vao->bind();
        m_prog->bind();
        m_vbo->bind();
        m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vbo->allocate(m_pts, 100*sizeof(QVector2D));

        m_prog->enableAttributeArray("vPosition");
        m_prog->setAttributeBuffer("vPosition", GL_FLOAT, 0, 2, 0);

        m_prog->release();
        m_vao->release();
    }

}

void Circle::draw(){
   drawHelper(GL_TRIANGLE_FAN, 100);
}

void Circle::moves(){
  //Need to account for size of box
  m_pts[0]= vec2(m_pts[0].x() + m_vel.x()*1,m_pts[0].y() + m_vel.y()*1);
  for (int i=1;i<100;i++){
      float x = m_pts[0].x()+m_rad*cos(2*3.14*i/97);
      float y = m_pts[0].y()+m_rad*sin(2*3.14*i/97);
      m_pts[i] = vec2(x,y);
  }
}

void Circle::wrap(int x, int y) {
  // if ((m_pts[0].x() < m_rad) || (m_pts[0].x() > x-200-m_rad)) {
  //   m_vel = vec2(m_vel.x()*-1,m_vel.y());   //Flips direction
  // }
  // if ((m_pts[0].y() < m_rad) || (m_pts[0].y() > y-125-m_rad)) {
  //   m_vel = vec2(m_vel.x(),m_vel.y()*-1);
  // }


  //Extended version

  //TOOO BIG!!!  Just win already!
  if (m_rad > x/3 || m_rad > y/3) {
    m_pts[0] = vec2(x/2,y/2);
    m_vel = vec2(0,0);
  }

  //Edge detection to stay within the confines.
  else {
    if (m_pts[0].x() < m_rad) {
      m_pts[0] = vec2(m_rad,m_pts[0].y());
      m_vel = vec2(m_vel.x()*-1,m_vel.y());   //Flips direction
    }
    else if (m_pts[0].x() > x-200-m_rad) {
      m_pts[0] = vec2(x-200-m_rad,m_pts[0].y());
      m_vel = vec2(m_vel.x()*-1,m_vel.y());   //Flips direction
    }

    if (m_pts[0].y() < m_rad) {
      m_pts[0] = vec2(m_pts[0].x(), m_rad);
      m_vel = vec2(m_vel.x(),m_vel.y()*-1);
    }
    else if (m_pts[0].y() > y-125-m_rad){
      m_pts[0] = vec2(m_pts[0].x(), y-125-m_rad);
      m_vel = vec2(m_vel.x(),m_vel.y()*-1);
    }
  }
}

void Circle::setrad(float newrad){
  m_rad = newrad;
}

void Circle::setcenter(vec2 center){  //increments center by that amount
  m_pts[0] = m_pts[0] + center;
}

void Circle::setvel(vec2 vel){
  m_vel = vel;
  m_displacement = vec2(0,0);
}



bool Circle::contains(const vec2& pt) const {

    vec2 vectord = pt - (m_pts[0]+m_displacement);
    vec2 circrad = (m_pts[1]+m_displacement) - (m_pts[0]+m_displacement);
    float radlen = circrad.length();
    float distance = vectord.length();
    if (distance<=radlen){
        return true;
    } else{
        return false;
    }
}

// void Circle::setTexture()
// {
//     if(m_texture)
//     {
//         delete m_texture;
//     }
//     m_texture = new QOpenGLTexture(QImage("galaxy.png").mirrored());
//     m_texture->bind();
// }
