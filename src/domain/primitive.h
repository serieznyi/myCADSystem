#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QStack>
#include "src/domain/element.h"
#include "src/constants.h"

struct MCOLOR {
  MCOLOR(int r, int g, int b) : red(r), green(g), blue(b) {}
  int red;
  int green;
  int blue;
};

class Primitive : public Element {

 public:
  Primitive();
  MCOLOR *getIDColor();
  MCOLOR *getColor();
  void setIDColor(MCOLOR *color);
  void setColor(MCOLOR *color);
  virtual void draw() = 0;
  void Apply(int mode);
  void setPaintMode(int mode);
  int getPaintMode();
 private:
  int PAINT_MODE;
  MCOLOR *COLOR;
  MCOLOR *ID_COLOR;
  QStack<MCOLOR *> *idcolors_arr;
};

QDataStream &operator<<(QDataStream &out, const Primitive *painting);
#endif // PRIMITIVE_H
