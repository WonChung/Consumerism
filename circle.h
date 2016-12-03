#pragma once

/* TODO: create, implement circle.cpp */

#include <drawable.h>
namespace cs40{

class Circle : public Drawable {

   public:

     Circle(QOpenGLShaderProgram* const prog,
				 const vec2& center, float radius);

     Circle(const Circle* const other);

     //No destructor necessary
     ~Circle() {/*do nothing*/};

     //Draw the Line using openGL
     void draw();

		 // return true if shape contains point pt, false otherwise
     bool contains(const vec2 &pt) const;

   private:
     //Vertices of Circle in ccw order
     vec2 m_pts[102];

     /* don't implement this */
     Circle& operator=(const Circle&);
};

}//namespace
