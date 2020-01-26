#include "translate.h"
#include <QDebug>

Translate::Translate(double x, double y, double z) : Action() {
  this->x_ = x;
  this->y_ = y;
  this->z_ = z;
}

void Translate::Apply(int mode) {
  glTranslated(x_, y_, z_);
}

void Translate::Move(double x, double y, double z) {
  this->x_ += x;
  this->y_ += y;
  this->z_ += z;
}

void Translate::MoveTo(double x, double y, double z) {
  this->x_ = x;
  this->y_ = y;
  this->z_ = z;
}
