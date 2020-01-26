#include "sphere.h"

Sphere::Sphere(GLUquadric *quad, GLfloat a) : Primitive() {
    this->a_ = a;
    this->SetTypeName(MEL_SPHERE);
    quadric_ = quad;
}

void Sphere::Draw() {
    Mcolor *color = nullptr;
    if (GetPaintMode())
        color = GetColor();
    else
        color = GetIdColor();

    glColor3ub(color->red_, color->green_, color->blue_);

    gluSphere(quadric_, a_, 20, 20);
}
void Sphere::SetQuadric(GLUquadric *quad) {
    quadric_ = quad;
}
