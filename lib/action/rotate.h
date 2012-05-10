//  Действие "Вращение"

#ifndef ROTATE_H
#define ROTATE_H

#include "lib/action/action.h"

class Rotate : public Action
{
public:
    explicit Rotate(double angleX=0, double angleY=0, double angleZ=0);
    virtual void Apply(bool mode=true);

public:
    double angleX;
    double angleY;
    double angleZ;
    void RotateX(GLdouble angle);
    void RotateY(GLdouble angle);
    void RotateZ(GLdouble angle);
};

#endif // ROTATE_H
