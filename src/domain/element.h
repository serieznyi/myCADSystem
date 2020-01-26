#ifndef MYCADSYSTEM_SRC_DOMAIN_ELEMENT_H_
#define MYCADSYSTEM_SRC_DOMAIN_ELEMENT_H_

#include "QOpenGLWidget"
#include <QString>

class Element {
 public:
  Element() {

  }
  void SetGid(long n) {
    this->gid_ = n;
  }
  //  Установить GID

  long GetGid() {
    return this->gid_;
  }
  //  Получить GID
  void SetTypeName(int a) {
    this->type_name_ = a;
  }
  //  Установить флаг примитива
  int GetTypeName() {
    return this->type_name_;
  }
  virtual void Apply(int mode) = 0;    //  Применить действие

 private:
  long gid_;         //  Глобальный идентификатор элемента
  int type_name_;

};

#endif //MYCADSYSTEM_SRC_DOMAIN_ELEMENT_H_
