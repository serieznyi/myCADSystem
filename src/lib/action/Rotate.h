//  Действие "Вращение"

#ifndef ROTATE_H
#define ROTATE_H

#include "src/lib/action/Action.h"

class Rotate : public Action
{
public:
    explicit Rotate(GLdouble angleX=0, GLdouble angleY=0, GLdouble angleZ=0);
    virtual void Apply(int mode=true);

public:
    double angleX;
    double angleY;
    double angleZ;
    void RotateX(GLdouble angle);
    void RotateY(GLdouble angle);
    void RotateZ(GLdouble angle);
};

#endif // ROTATE_H
