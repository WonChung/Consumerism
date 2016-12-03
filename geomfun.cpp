#include "geomfun.h"

using namespace cs40;

/* bool cs40::leftOf()
 * This method checks if the third point is left of the
 * the first two points. The method first does a cross product of
 * between the differences of p3 & p1, and p2 & p1.
 * Then a dot product between the cross product and the base is performed,
 * in which a non-positive value indicates that the third point
 * is not left of the first two points, and returns false.
 */
bool cs40::leftOf(const vec2& p1, const vec2& p2, const vec2& p3){
    vec2 vbar = p2 - p1;
    vec2 wbar = p3 - p1;
    vec3 cross;
    // Cross Product between the difference between p2 & p1 and
    // p3 & p1
    cross = vec3::crossProduct(vbar,wbar);

    // A dot product is performed on the result of the cross product
    // and the base, in which a non-posive value indicates that the
    // third point is not left of the first two points.
    QVector3D zbase = QVector3D(0,0,1);
    float dot;
    dot = vec3::dotProduct(cross,zbase);
    if (dot>0) {
        return true;
    } else {
        return false;
    }
}

/* This method calculates the distance between segments by taking
 * the distance from the nearest point at points outside the perpendicular
 * limits of the line segment, and the distance to segment within the limits.
 */  

float cs40::distToSegment(const vec2& p1, const vec2& p2, const vec2& p3){
    // vec2 Done = p3 - p1;
    // vec2 Dtwo = p3 - p2;
    // vec2 Dthree = p2 - p1;
    // vec3 crossed = vec3::crossProduct(Dthree, Done);
    // float dotted = vec3::dotProduct(Dthree,Done);
    // float clen = crossed.length();
    // float Dlen = Dthree.length();
    // float res = dotted / Dlen;
    // if (res < 0) {
    //     return Done.length();
    // }   else if (res <= 1){
    //     return clen;
    // } else{
    //     return Dtwo.length();
    // }

    /*Should work, but running into another error.  Wrote the other one to
    make sure it wasn't due to that*/
    vec2 w = p3 - p1;
    vec2 v = p2 - p1;
    float d1 = w.length();
    vec2 vec23 = p3 - p2;
    float d2 = vec23.length();


    vec3 crossed = vec3::crossProduct(v,w);
    float d3 = crossed.length() / v.length();
    float dotted = vec3::dotProduct(w,v) / v.length();

    if (dotted < 0) {
        return d1;
    } else if (dotted < v.length()){
        return d3;
    } else {
        return d2;
    }
}

/* helpful debugging ostream operators */
std::ostream& operator<<(std::ostream& str, const QVector2D& vec){
    str << "(" <<(float) vec.x() << ", " << (float) vec.y() <<")";
    return str;
}

std::ostream& operator<<(std::ostream& str, const QVector3D& vec){
    str << "(" << (float) vec.x() << ", " << (float) vec.y() << ", ";
    str << (float) vec.z() << ")";
    return str;
}

std::ostream& operator<<(std::ostream& str, const QVector4D& vec){
    str << "(" << (float) vec.x() << ", " << (float) vec.y() << ", ";
    str << (float) vec.z() << ", " << (float) vec.w() << ")";
    return str;
}
