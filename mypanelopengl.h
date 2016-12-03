#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

#include <QtWidgets>
#include <QtOpenGL>
#include <stdlib.h>
#include "drawable.h"
#include "circle.h"
#include "planet.h"
#include "geomfun.h"

class MyPanelOpenGL : public QOpenGLWidget
{
    Q_OBJECT

    /* define a new type app_mode_t that stores the current mode*/
    /* put this block in mypanelopengl.h but outside the class */
    typedef enum CS40_APP_MODE{
      NONE=0,
      MOVING,
      DELETING,
      CHANGE_COLOR,
      ADD_CIRCLE,

    } app_mode_t;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

public:
    explicit MyPanelOpenGL(QWidget *parent = 0);
    virtual ~MyPanelOpenGL();

private:
    /* shader/program objects */
    QOpenGLShader *m_vertexShader;
    QOpenGLShader *m_fragmentShader;
    QOpenGLShaderProgram *m_shaderProgram;

    //Added private member variable for matrix
    QMatrix4x4 m_matrix;

    /* list of drawable shapes */
    QList<cs40::Drawable*> m_shapes;

    // QList for mouseMoveEvent (same as m_clicks)
    QVector2D m_mouseClicks;
    QVector2D m_prevmouse;

    //Drawing modes modification
    app_mode_t m_currentMode;
    app_mode_t m_prevMode;

    // //m_clicks
    QList<QVector2D> m_clicks;
    cs40::Circle* m_circle;
    QTimer* m_timer;      /* event timer */
    QList<cs40::Planet*> m_info;

    // QVector3D curr_color;

    /* helpers */
    void createShaders();
    void destroyShaders();

signals:
    /* empty */

public slots:
    void updateTime();
    // void Sandbox();
    // void Singleplayer():
    // void AIFFA();
    // void TopScore():
    // void PlayerScore();


    /* empty */

};

#endif // MYPANELOPENGL_H
