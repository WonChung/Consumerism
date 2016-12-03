#include "circle.h"

using namespace cs40;

Circle::Circle(QOpenGLShaderProgram* const prog,
  const vec2& center, float radius) {


    m_prog = prog;

    m_pts[0] = center;
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

    /*if (!(sizeof(other->m_pts)==100)) {
        exit(1);
    }*/

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

// void Circle::draw(){
//
//      m_vao->bind();
//      m_prog->bind();
//      m_prog->setUniformValue("color",m_color);
//      m_prog->setUniformValue("displacement",m_displacement);
//      //glDrawArrays(GL_LINE_LOOP, 2, outer_num_vert);
//      glDrawArrays(GL_TRIANGLE_FAN, 0, 100);
//      m_prog->release();
//      m_vao->release();
// }

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
