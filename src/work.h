// Работа (Проект)
#ifndef MYCADSYSTEM_SRC_WORK_H_
#define MYCADSYSTEM_SRC_WORK_H_

#include <QOpenGLWidget>
#include <GL/glu.h>
#include <cstdlib>
#include <ctime>
#include <src/domain/primitive.h>
#include <src/domain/container.h>
#include "src/constants.h"

class MainWindow;

class Work {
 public:
  explicit Work(QWidget *parent);
  void DrawWork(bool mode = true);
  void AddPrimitive(int i, QPoint pos = QPoint(0, 0));                           // Добавление объекта на сцену
  void AddAction(int i);                              // Применение действия
  long GenerateGid();                                 // Генерация идентификатора для события
  Mcolor *GenerateIdColor();
  Mcolor *GenerateColor();
  QList<Container *> *GetList();
  void DeletePrimitive(long index);
  void SetGroupObj1(long i);
  void SetGroupObj2(long i);
  long GetGroupObj1();
  long GetGroupObj2();
 public:
  int real_color_[3];
 private:
  long for_group_id_[2];
  MainWindow *p_mw_;
  QList<Container *> *element_list_;             //  Список элементов сцены
  long current_free_id_;           //  Текущий свободный идентификатор
  int current_free_color_[3];     //
  GLUquadric *quadric_;
};

#endif //MYCADSYSTEM_SRC_WORK_H_
