#ifndef MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_SUBSTRACT_PRIMITIVE_H_
#define MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_SUBSTRACT_PRIMITIVE_H_

#include "group-primitive.h"
#include "src/domain/container.h"
#include "src/constants.h"

class SubstractPrimitive : public GroupPrimitive {
 public:
  SubstractPrimitive(Container *con_1, Container *con_2);
  void Draw() override;
  void SyncData() override;
};

#endif //MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_SUBSTRACT_PRIMITIVE_H_
