#pragma once

#include <drawable.h>
namespace cs40{

class Circle : public Drawable {

   public:

     Circle(QOpenGLShaderProgram* const prog,
				 const vec2& center, float radius, const vec2& vel);

     Circle(const Circle* const other);

     //No destructor necessary
     ~Circle() {/*do nothing*/};

     //Draw the Line using openGL
     void draw();

     void moves();

     void wrap(int x, int y);


		 // return true if shape contains point pt, false otherwise
     bool contains(const vec2 &pt) const;

     void setrad(float newrad);
     void setcenter(vec2 center);
     void setvel(vec2 vel);
     inline vec2 getvel() const { return m_vel; }
     inline float getrad() const { return m_rad; }
     inline vec2 getcenter() const { return m_pts[0]; }

    //  void setTexture();
    //  inline QOpenGLTexture* getTexture() const { return m_texture; }

   private:
     //Vertices of Circle in ccw order
     vec2 m_pts[102];
     vec2 m_vel;
     float m_rad;

     QOpenGLTexture* m_texture;

     /* don't implement this */
     Circle& operator=(const Circle&);
};

}//namespace
