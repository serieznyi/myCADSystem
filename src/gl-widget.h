// Область рисования

#ifndef MYCADSYSTEM_SRC_GL_WIDGET_H_
#define MYCADSYSTEM_SRC_GL_WIDGET_H_

#include <QtGui>
#include <QOpenGLWidget>
#include <QPoint>
#include <QVBoxLayout>
#include <QComboBox>
#include <QMouseEvent>
#include <cmath>
#include "GL/glu.h"
#include "src/constants.h"
#include "work.h"
#include "src/gui/context-menu.h"

#include "invers.h"
#include "matrix.h"

class MainWindow;

class GLWidget : public QOpenGLWidget {
 Q_OBJECT
 protected:
  void initializeGL() override;                                                //  Инициализация GL
  void resizeGL(int w_arg, int h_arg) override;                                      //  Изменение размера области рисования
  void paintGL() override;                                                     //  Главная функция рисования
 public:
  explicit GLWidget(QWidget *parent = nullptr);                             //  Конструктор
  void mousePressEvent(QMouseEvent *event) override;                           //  Обработка нажатия клавиш мыши
  void mouseMoveEvent(QMouseEvent *event) override;                            //  Обработка движения мыши
  int GetProjection();                                                //  Получить тип проекции вида
  void SetProjection(int i);                                          //  Установить тип проекции вида
  void SelectEvent(QMouseEvent *event, QPoint current);               //  Выбор события
  void EventTranslateCamera(QMouseEvent *event, QPoint current);      //  Перемещение камеры
  void EventRotateCamera(QMouseEvent *event, QPoint current);         //  Поворот камеры
  void EventZoomCamera(QMouseEvent *event, QPoint current);           //  Масштабирование камеры
  void EventTranslatePrimitive(QMouseEvent *event);                   //  Перемещение примитива
  void EventRotatePrimitive(QMouseEvent *event, QPoint current);      //  Поворот примитива
  void EventGroupPrimitive(long obj_1, long obj_2);
  void EventSubstractPrimitive(long obj_1, long obj_2);
  void EventIntersectPrimitive(long obj_1, long obj_2);
  void EventScalePrimitive(QPoint point);
  void EventStretchPrimitive(QPoint point);
  void AddPrimitive(QPoint pos = QPoint(0, 0));                                      //  Добавление примитива
  void AddAction(int i);
  void AddPrimitive(int i);
  double ScreenToOgl(int coord, int type);                            //  Перевод оконных координат в координаты OpenGL
  void DrawAxes();                                                    //  Рисование осей
  void DrawPlane();                                                   //  Рисование плоскости
  void SaveLastState();
  void LoadLastState();
  double ScreenToOgLv2(int last, int coord, int type);                //
  void SetXRotation(int angle);                                       //
  void SetYRotation(int angle);                                       //
  void SetZRotation(int angle);                                       //
  void DrawX();
  void DrawY();
  void DrawZ();
  void QNormalizeAngle(int &angle);
  long GetSelectedPrimitiveId(QMouseEvent *event);
  double CalcKoef();
  bool IntersectionGroupObj(long obj_1, long obj_2);
//---------------------------ПЕРЕМЕННЫЕ---------------------------
 public:
  MainWindow *p_mw_;                                               //  Указатель на виджет самого верхнего уровня
  int painting_mode_;                                      //  Режим рисования
  int projection_type_;                                    //  Тип проекции вида
  Work *current_work_;                                       //  Текущий проект
  int *curren_event_;                                       //  Текущее событие
  int *previous_event_;                                     //  Предыдущее событие
  bool selected_;                                           //  Выбран объект сцены
  bool axes_;                                               //  Рисовать оси
  bool plane_;                                              //  Рисовать сетку
  GLubyte pixel_[3];                                           //  Цвет пикселя выбранного мышью
  ///////////////ПОчистить/////////////////
  struct Ortho {
    Ortho() :
        width_(0), height_(0), last_width_(0), last_height_(0),
        left_val_(0), right_val_(0), top_val_(0), down_val_(0),
        near_val_(0), far_val_(0) {
    }

    double width_;
    double height_;
    double last_width_;
    double last_height_;
    double left_val_;
    double right_val_;
    double top_val_;
    double down_val_;
    double near_val_;
    double far_val_;
  };
  Ortho current_ortho_;

  double koef_;
  ContextMenu *context_menu_primitive_;
  int last_projection_;
  GLdouble x_rot_, y_rot_, z_rot_;
  GLfloat x_translate_, y_translate_, z_translate_;
  GLdouble g_scale_;                 // Масштаб всей сцены
  QPoint last_pos_;
  QPoint current_pos_;
  QVBoxLayout *lay_global_v_;
  QHBoxLayout *lay_global_h_;
  QComboBox *combo_box_;
  GLfloat x_, y_, z_;
  double n_;
  double r_;
  constexpr static const GLfloat step_scale_ = 0.01f;
  constexpr static const GLfloat step_translate_ = 0.05f;
  constexpr static const GLdouble step_rotate_ = 1;

//////////////////////////////////////
  GLint mx_, my_;           // Позиция Курсора (обработанная)
  GLint prev_mx_, prev_my_;   // Предыдущая позиция курсора?
  GLdouble start_matrix_[4][4];
  GLdouble invers_start_matrix_[4][4];

  QString GetTextEvent(int event);
 public slots:
  void ChangeProection(int n);
  void DeletePrimitive();
};

#endif //MYCADSYSTEM_SRC_GL_WIDGET_H_
