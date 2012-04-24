//  Действие "Вращение"

#ifndef ROTATE_H
#define ROTATE_H

#include "lib/action/action.h"

class Rotate : public Action
{
public:
    explicit Rotate(double angleX=0, double angleY=0, double angleZ=0);
    virtual void Apply();

public:
    double angleX;
    double angleY;
    double angleZ;
    void RotateX(double angle);
    void RotateY(double angle);
    void RotateZ(double angle);
};

#endif // ROTATE_H
