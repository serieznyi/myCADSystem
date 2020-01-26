#ifndef INTERSECTPRIMITIVE_H
#define INTERSECTPRIMITIVE_H

#include "group-primitive.h"
#include "src/domain/container.h"
#include "src/constants.h"

class IntersectPrimitive : public GroupPrimitive {
 public:
  IntersectPrimitive(Container *con1, Container *con2);
  virtual void draw();
  virtual void SynchData();
};

#endif // INTERSECTPRIMITIVE_H
