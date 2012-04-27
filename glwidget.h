// Область рисования

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QPoint>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMouseEvent>
#include <math.h>
#include "GL/glu.h"
#include "resource.h"
#include "abstractmainwindow.h"
#include "work.h"
#include "toolbars/list_primitive_toolbar.h"
#include "lib/primitive/primitive.h"
#include "lib/action/translate.h"

class MainWindow;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void setProjection(int i);
    int getProjection();
    void mousePressEvent(QMouseEvent *event);                           //
    void mouseMoveEvent(QMouseEvent *event);                            //
    void eventTranslateCamera(QMouseEvent *event, QPoint current);      //
    void eventZoomCamera(QMouseEvent *event, QPoint current);           //
    void setXRotation(int angle);                                       //
    void setYRotation(int angle);                                       //
    void setZRotation(int angle);                                       //
    void selectEvent(QMouseEvent *event, QPoint current);               //
    void eventRotateCamera(QMouseEvent *event, QPoint current);         //
    void addPrimitive(QPoint current);                                  //
    void addPrimitive();                                          //
    void eventTranslatePrimitive(QMouseEvent *event, QPoint current);
    void eventRotatePrimitive(QMouseEvent *event, QPoint current);
    void drawX();
    void drawY();
    void drawZ();
    void SaveLastState();
    double ScreenToOGL(int coord, int type);    // Перевод оконных координат в координаты OpenGL
protected:
    void initializeGL();                        // Инициализация GL
    void resizeGL(int w, int h);                // Изменение размера области рисования
    void paintGL();                             // Главная функция рисования
    void drawAxes();                            // Рисование осей
    void drawPlane();                           // Рисование плоскости
    void qNormalizeAngle(int &angle);           //
public:
    GLubyte color_selected_prim[3];
    int             mode;
private:
    int             type_projection;
    int             w,
                    h,
                    last_w,
                    last_h;
    int             lastProjection;
    GLdouble        xRot,                   //
                    yRot,                   //
                    zRot;                   //
    GLfloat         xTranslate,             //
                    yTranslate,             //
                    zTranslate;             //
    GLdouble        gScale;                 // Масштаб всей сцены
    QPoint          p_lastPos;              //
    QPoint          p_currentPos;           //
    QVBoxLayout     *lay_global_v;          //
    QHBoxLayout     *lay_global_h;          //
    QComboBox       *comboBox;              //
    GLfloat         _x,
                    _y,
                    _z;
    double          n;
    double          R;
    MainWindow *pMW;
    Work            *currentWork;
    int             *currenEvent;
    int             *previousEvent;

    static const GLfloat step_scale = 0.01f;
    static const GLfloat step_translate = 0.05f;
public slots:
    void changeProection(int n);
};

#endif // GLWIDGET_H
