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
    explicit GLWidget(QWidget *parent = 0);                             //  Конструктор
    void setProjection(int i);                                          //  Установить тип проекции вида
    int getProjection();                                                //  Получить тип проекции вида
    void mousePressEvent(QMouseEvent *event);                           //  Обработка нажатия клавиш мыши
    void mouseMoveEvent(QMouseEvent *event);                            //  Обработка движения мыши

    void selectEvent(QMouseEvent *event, QPoint current);               //  Выбор события
    void eventTranslateCamera(QMouseEvent *event, QPoint current);      //  Перемещение камеры
    void eventRotateCamera(QMouseEvent *event, QPoint current);         //  Поворот камеры
    void eventZoomCamera(QMouseEvent *event, QPoint current);           //  Масштабирование камеры
    void eventTranslatePrimitive(QMouseEvent *event, QPoint current);   //  Перемещение примитива
    void eventRotatePrimitive(QMouseEvent *event, QPoint current);      //  Поворот примитива
    void addPrimitive();                                                //  Добавление примитива в позицию по умолчанию
    void addPrimitive(QPoint current);                                  //  Добавление примитива на сцену в указанную позицию

    void SaveLastState();
    double ScreenToOGL(int coord, int type);                            // Перевод оконных координат в координаты OpenGL
    double ScreenToOGLv2(int last, int coord, int type);                //
    void setXRotation(int angle);                                       //
    void setYRotation(int angle);                                       //
    void setZRotation(int angle);                                       //
    void drawX();
    void drawY();
    void drawZ();
protected:
    void initializeGL();                                                //  Инициализация GL
    void resizeGL(int w, int h);                                        //  Изменение размера области рисования
    void paintGL();                                                     //  Главная функция рисования
    void drawAxes();                                                    //  Рисование осей
    void drawPlane();                                                   //  Рисование плоскости
    void qNormalizeAngle(int &angle);                                   //
public:
    MainWindow      *pMW;                                               //  Указатель на виджет самого верхнего уровня
    int             PAINTING_MODE;                                      //  Режим рисования
    int             PROJECTION_TYPE;                                    //  Тип проекции вида
    Work            *currentWork;                                       //  Текущий проект
    int             *currenEvent;                                       //  Текущее событие
    int             *previousEvent;                                     //  Предыдущее событие

    ////////////////////////////////
    bool            SELECTED,                                           //  Выбран объект сцены
                    AXES,                                               //  Рисовать оси
                    PLANE;                                              //  Рисовать сетку
    GLubyte         pixel[3];
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
    static const GLfloat step_scale = 0.01f;
    static const GLfloat step_translate = 0.05f;
//////////////////////////////////////
    GLint Mx, My;           // Позиция Курсора (обработанная)
    GLint prevMx, prevMy;   // Предыдущая позиция курсора?
    int selected_prim;




public slots:
    void changeProection(int n);
};

#endif // GLWIDGET_H
