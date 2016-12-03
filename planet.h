#pragma once

#include <QString>
#include <QtOpenGL>

/* an example planet class. Don't like it? Throw it out, write your own. */
namespace cs40{

class Planet
{
public:

    /* name:    name of planet
     * o_rad:   orbital radius
     * o_tau:   orbital period
     * ecc:     eccentricity
     * inc:     inclination
     * rad:     planet radius
     * r_tau:   rotaional period
     * tilt:    axial tilt
     */
    Planet(float counter, vec2 center, float rad, vec2 vel);

    ~Planet(){ if(m_texture){ delete m_texture; m_texture=NULL;} }

    /* move the planet with time change in delhrs Earth hours. */
    void move(float delhrs);

    inline bool has_texture() const { return m_has_texture; }

    void setTexture();

    inline QOpenGLTexture* getTexture() const { return m_texture; }

    // inline QString getName() const {return m_name; }
    // inline float getDistToSun() const { return m_orb_radius; }
    // inline float getRadius() const { return m_radius; }
    // inline float getTilt() const { return m_axial_tilt; }
    //
    // inline float getOrbPos() const { return m_theta; }
    // inline float getRotPos() const { return m_phi; }
    //
    // inline float getInclination() const { return m_inclination; }


private:
    Planet();

    // QString m_name;         /* planet name */
    // float m_orb_radius;     /* distance from sun (*10**6 m) */
    // float m_orb_tau;        /* orbital period (Earth years = 365.25 days) */
    QOpenGLTexture* m_texture; /* texture wrapper class */
    // float m_eccentricity;   /* ellipsy-ness */
    // float m_inclination;    /* relative to orbital plane (degrees) */
    // float m_radius;         /* radius of planet */
    // float m_rot_tau;        /* rotation period (Earth days = 24 hrs) */
    // float m_axial_tilt;     /* axial tilt (degrees) */
    bool  m_has_texture;    /* true if texture set */
    //
    // float m_theta;          /* current orbital angle */
    // float m_phi;            /* current rotational angle */
    //
    // /* wrap value to range -180 .. 180 */
    // float wrap(float val);

    int m_counter;
    vec2 m_center;
    float m_rad;
    vec2 m_vel;

};

} //namepace
