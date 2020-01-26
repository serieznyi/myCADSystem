//  Контейнер хранящий прмитив и все связные с ним операции

#ifndef MYCADSYSTEM_SRC_DOMAIN_CONTAINER_H_
#define MYCADSYSTEM_SRC_DOMAIN_CONTAINER_H_

#include <QList>
#include "src/domain/primitive.h"
#include "src/domain/action/translate.h"
#include "src/domain/action/rotate.h"
#include "src/domain/action/scale.h"

class Container {
 public:
  explicit Container(Primitive *prim);
  Container(Primitive *prim, Translate *translate);
  void AddTranslate(Translate *trans);
  void AddRotate(Rotate *rot);
  void AddScale(Scale *scale);
  void Draw(int mode);
  QList<Translate *> *GetTranslateList();
  QList<Rotate *> *GetRotateList();
  QList<Scale *> *GetScaleList();
  Translate *GetTranslate();
  Scale *GetScale();
  Rotate *GetRotate();
  Primitive *GetPrimitive();

 private:
  Primitive *primitive_;
  QList<Translate *> *translate_list_;
  QList<Rotate *> *rotate_list_;
  QList<Scale *> *scale_list_;
};

QDataStream &operator<<(QDataStream &out, const Container *painting);

#endif //MYCADSYSTEM_SRC_DOMAIN_CONTAINER_H_
