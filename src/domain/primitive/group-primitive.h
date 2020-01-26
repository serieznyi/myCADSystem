#ifndef MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_GROUP_PRIMITIVE_H_
#define MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_GROUP_PRIMITIVE_H_

#include "src/domain/primitive.h"
#include "src/domain/container.h"

class GroupPrimitive : public Primitive {
 public:
  GroupPrimitive(Container *con_1, Container *con_2);
  void Draw() override;
  virtual void SyncData();
 public:
  Container *container_1_;
  Container *container_2_;
};

#endif //MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_GROUP_PRIMITIVE_H_
