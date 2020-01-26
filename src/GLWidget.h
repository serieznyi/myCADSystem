// Область рисования

#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QtGui>
#include <QOpenGLWidget>
#include <QPoint>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMouseEvent>
#include <cmath>
#include "GL/glu.h"
#include "src/resource.h"
#include "Work.h"
#include "src/gui/ContextMenu.h"

#include "invers.h"
#include "matrix.h"


class MainWindow;

class GLWidget : public QOpenGLWidget
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
    void eventGroupPrimitive(long ob1, long obj2);
    void eventSubstractPrimitive(long obj1, long obj2);
    void eventIntersectPrimitive(long obj1, long obj2);
    void eventScalePrimitive(QPoint point);
    void eventStretchPrimitive(QPoint poin);
    void addPrimitive(QPoint pos=QPoint(0,0));                                      //  Добавление примитива
    void addAction(int i);
    void addPrimitive(int i);
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
    double calcKoef();
    bool intersectionGroupObj(long obj1, long obj2);
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
    QPoint          lastPos;              //
    QPoint          currentPos;           //
    QVBoxLayout     *lay_global_v;          //
    QHBoxLayout     *lay_global_h;          //
    QComboBox       *comboBox;              //
    GLfloat         _x,
                    _y,
                    _z;
    double          n;
    double          R;
    constexpr static const GLfloat step_scale = 0.01f;
    constexpr static const GLfloat step_translate = 0.05f;
    constexpr static const GLdouble step_rotate = 1;

//////////////////////////////////////
    GLint Mx, My;           // Позиция Курсора (обработанная)
    GLint prevMx, prevMy;   // Предыдущая позиция курсора?
    GLdouble startMatrix[4][4];
    GLdouble inversStartMatrix[4][4];

    QString getTextEvent(int event);
public slots:
    void changeProection(int n);
    void deletePrimitive();
};

#endif // GLWIDGET_H
