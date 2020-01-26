#ifndef GROUPPRIMITIVE_H
#define GROUPPRIMITIVE_H

#include "src/domain/primitive.h"
#include "src/domain/container.h"

class GroupPrimitive : public Primitive {
 public:
  GroupPrimitive(Container *con1, Container *con2);
  virtual void draw();
  void SynchData();
 public:
  Container *container1;
  Container *container2;
};

#endif // GROUPPRIMITIVE_H
