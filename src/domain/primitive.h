#ifndef MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_H_
#define MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_H_

#include <QStack>
#include "src/domain/element.h"
#include "src/constants.h"

struct Mcolor {
  Mcolor(int r, int g, int b) : red_(r), green_(g), blue_(b) {}
  int red_;
  int green_;
  int blue_;
};

class Primitive : public Element {

 public:
  Primitive();
  Mcolor *GetIdColor();
  Mcolor *GetColor();
  void SetIdColor(Mcolor *color);
  void SetColor(Mcolor *color);
  virtual void Draw() = 0;
  void Apply(int mode);
  void SetPaintMode(int mode);
  int GetPaintMode();
 private:
  int paint_mode_;
  Mcolor *color_;
  Mcolor *id_color_;
  QStack<Mcolor *> *id_colors_arr_;
};

QDataStream &operator<<(QDataStream &out, const Primitive *painting);
#endif //MYCADSYSTEM_SRC_DOMAIN_PRIMITIVE_H_
