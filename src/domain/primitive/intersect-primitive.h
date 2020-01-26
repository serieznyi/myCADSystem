#ifndef MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_INTERSECT_PRIMITIVE_H_
#define MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_INTERSECT_PRIMITIVE_H_

#include "group-primitive.h"
#include "src/domain/container.h"
#include "src/constants.h"

class IntersectPrimitive : public GroupPrimitive {
 public:
  IntersectPrimitive(Container *con_1, Container *con_2);
  void Draw() override;
  void SyncData() override;
};

#endif //MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_INTERSECT_PRIMITIVE_H_
