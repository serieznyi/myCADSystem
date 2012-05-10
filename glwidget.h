// Область рисования

#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QtGui>
#include <QGLWidget>
#include <QPoint>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMouseEvent>
#include <math.h>
#include "GL/glu.h"
#include "resource.h"
#include "work.h"
#include "toolbars/list_primitive_toolbar.h"
#include "lib/lib.h"
#include "contextmenu.h"

class MainWindow;

class GLWidget : public QGLWidget
{
    Q_OBJECT
protected:
    void initializeGL();                                                //  Инициализация GL
    void resizeGL(int _w, int _h);                                      //  Изменение размера области рисования
    void paintGL();                                                     //  Главная функция рисования

public:
    explicit GLWidget(QWidget *parent = 0);                             //  Конструктор
    void mousePressEvent(QMouseEvent *event);                           //  Обработка нажатия клавиш мыши
    void mouseMoveEvent(QMouseEvent *event);                            //  Обработка движения мыши
    int getProjection();                                                //  Получить тип проекции вида
    void setProjection(int i);                                          //  Установить тип проекции вида
    void selectEvent(QMouseEvent *event, QPoint current);               //  Выбор события
    void eventTranslateCamera(QMouseEvent *event, QPoint current);      //  Перемещение камеры
    void eventRotateCamera(QMouseEvent *event, QPoint current);         //  Поворот камеры
    void eventZoomCamera(QMouseEvent *event, QPoint current);           //  Масштабирование камеры
    void eventTranslatePrimitive(QMouseEvent *event);                   //  Перемещение примитива
    void eventRotatePrimitive(QMouseEvent *event, QPoint current);      //  Поворот примитива
    void addPrimitive();                                                //  Добавление примитива в позицию по умолчанию
    void addPrimitive(QPoint current);                                  //  Добавление примитива на сцену в указанную позицию
    double ScreenToOGL(int coord, int type);                            //  Перевод оконных координат в координаты OpenGL
    void drawAxes();                                                    //  Рисование осей
    void drawPlane();                                                   //  Рисование плоскости

    void initializeLighting();
    void SaveLastState();
    void LoadLastState();
    double ScreenToOGLv2(int last, int coord, int type);                //
    void setXRotation(int angle);                                       //
    void setYRotation(int angle);                                       //
    void setZRotation(int angle);                                       //
    void drawX();
    void drawY();
    void drawZ();
    void qNormalizeAngle(int &angle);
    long getSelectedPrimitiveID(QMouseEvent *event);

//---------------------------ПЕРЕМЕННЫЕ---------------------------

public:
    MainWindow      *pMW;                                               //  Указатель на виджет самого верхнего уровня
    int             PAINTING_MODE;                                      //  Режим рисования
    int             PROJECTION_TYPE;                                    //  Тип проекции вида
    Work            *currentWork;                                       //  Текущий проект
    int             *currenEvent;                                       //  Текущее событие
    int             *previousEvent;                                     //  Предыдущее событие
    bool            SELECTED,                                           //  Выбран объект сцены
                    AXES,                                               //  Рисовать оси
                    PLANE;                                              //  Рисовать сетку
    GLubyte         pixel[3];                                           //  Цвет пикселя выбранного мышью

    ///////////////ПОчистить/////////////////
    struct Ortho{
        Ortho():
                width(0), height(0), last_width(0), last_height(0),
            left_val(0), right_val(0), top_val(0), down_val(0),
            near_val(0), far_val(0)
        {
        }

        double width;
        double height;
        double last_width;
        double last_height;
        double left_val;
        double right_val;
        double top_val;
        double down_val;
        double near_val;
        double far_val;
    };

    Ortho           currentOrtho;
    double koef;
    ContextMenu     *contextMenuPrimitive;
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
    GLdouble step_rotate;
//////////////////////////////////////
    GLint Mx, My;           // Позиция Курсора (обработанная)
    GLint prevMx, prevMy;   // Предыдущая позиция курсора?

    double calcKoef();
    void eventGroupPrimitive(long ob1, long obj2);
    bool intersectionGroupObj(long ob1, long obj2);
    void addAction(int i);
    void addPrimitive(int i);
public slots:
    void changeProection(int n);
    void deletePrimitive();
};

#endif // GLWIDGET_H
