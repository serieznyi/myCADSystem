#include "pyramid.h"

Pyramid::Pyramid(GLfloat a) : Primitive() {
  this->a_ = a;
  this->SetTypeName(MEL_PYRAMID);
}

void Pyramid::Draw() {
  Mcolor *color = 0;
  if (GetPaintMode())
    color = GetColor();
  else
    color = GetIdColor();

  glColor3ub(color->red_, color->green_, color->blue_);

  GLdouble h = (sqrt(3) / 2) * this->a_;
  // glPushMatrix();//основание
  glRotated(90, 1, 0, 0);
  glBegin(GL_TRIANGLES);
  glVertex3d(0, h / 2, 0);
  glVertex3d(a_ / 2, -h / 2, 0);
  glVertex3d(-a_ / 2, -h / 2, 0);

  glVertex3d(0, 0, -h);
  glVertex3d(0, h / 2, 0);
  glVertex3d(a_ / 2, -h / 2, 0);

  glVertex3d(0, 0, -h);
  glVertex3d(0, h / 2, 0);
  glVertex3d(-a_ / 2, -h / 2, 0);

  glVertex3d(0, 0, -h);
  glVertex3d(a_ / 2, -h / 2, 0);
  glVertex3d(-a_ / 2, -h / 2, 0);
  glEnd();
  //             glPopMatrix();
}
