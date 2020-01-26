#include "rotate.h"

Rotate::Rotate(GLdouble angle_x, GLdouble angle_y, GLdouble angle_z) : Action() {
  this->angle_x_ = angle_x;
  this->angle_y_ = angle_y;
  this->angle_z_ = angle_z;
}

void Rotate::Apply(int mode) {
  glRotated(angle_x_, 1, 0, 0);
  glRotated(angle_y_, 0, 1, 0);
  glRotated(angle_z_, 0, 0, 1);
}

void Rotate::RotateX(GLdouble angle) {
  this->angle_x_ += angle;
}

void Rotate::RotateY(GLdouble angle) {
  this->angle_y_ += angle;
}

void Rotate::RotateZ(GLdouble angle) {
  this->angle_z_ += angle;
}



