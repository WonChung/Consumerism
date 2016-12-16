#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

#include <QtWidgets>
#include <QtOpenGL>
#include <stdlib.h>
#include "circle.h"  //already includes drawable.h
#include "geomfun.h"
#include "score.h"
#include <QGraphicsView>
#include <QFont>


class MyPanelOpenGL : public QOpenGLWidget
{
    Q_OBJECT

    /* define a new type app_mode_t that stores the current mode*/
    /* put this block in mypanelopengl.h but outside the class */
    typedef enum CS40_APP_MODE{
      NONE=0,
      SINGLEPLAYER,
      SANDBOX,
      AI_FFA,
      ADD_CIRCLES,
      RESET_SIZE,
      GAMEOVER
    } app_mode_t;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    // void keyPressEvent(QKeyEvent* event);


public:
    explicit MyPanelOpenGL(QWidget *parent = 0);
    virtual ~MyPanelOpenGL();
    void setTexture(cs40::Circle*);
    QOpenGLTexture* getTexture(cs40::Circle*);
    Score* m_score;

private:
    /* shader/program objects */
    QOpenGLShader *m_vertexShader;
    QOpenGLShader *m_fragmentShader;
    QOpenGLShaderProgram *m_shaderProgram;

    //Added private member variable for matrix
    QMatrix4x4 m_matrix;

    /* list of drawable shapes */
    QList<cs40::Circle*> m_shapes;

    // Texture data
    QOpenGLTexture* m_texture;

    // QList for mouseMoveEvent (same as m_clicks)
    QVector2D m_mouseClicks;
    QVector2D m_prevmouse;

    //Drawing modes modification
    app_mode_t m_currentMode;
    app_mode_t m_prevMode;

    // //m_clicks
    QList<QVector2D> m_clicks;
    QTimer* m_timer;
    float m_maxvel;


    QVector3D curr_color;

    /* helpers */
    void createShaders();
    void destroyShaders();

signals:
    /* empty */

public slots:
    void updateTime();
    void AIFFA();
    void Sandbox();
    void Singleplayer();
    void Add_Circles();
    void Reset_Size();
    // void updatePlayerScore();

    // void updateTopScore();
    // void updatePlayerScore();


    // void clickCircle();
    /* empty */

};

#endif // MYPANELOPENGL_H
