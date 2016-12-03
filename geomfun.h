#pragma once
#
#include <QtOpenGL>


namespace cs40{

  typedef QVector2D vec2;
  typedef QVector3D vec3;
  typedef QVector4D vec4;

  /* return true if p1 is left of line from p2 to p3 */
  bool leftOf(const vec2& p1, const vec2& p2, const vec2& p3);
  float distToSegment(const vec2& p1, const vec2& p2, const vec2& p3);


} //namespace

/* helpful debugging ostream operators */
std::ostream& operator<<(std::ostream& str, const QVector2D& vec);
std::ostream& operator<<(std::ostream& str, const QVector3D& vec);
std::ostream& operator<<(std::ostream& str, const QVector4D& vec);
