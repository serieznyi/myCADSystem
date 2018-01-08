#ifndef SCALE_H
#define SCALE_H

#include "src/lib/action/Action.h"

class Scale : public Action
{
public:
    Scale(GLdouble x, GLdouble y, GLdouble z);
    virtual void Apply(int mode);
    void ScaleX(GLdouble x);
    void ScaleY(GLdouble y);
    void ScaleZ(GLdouble z);
    void ScaleYXY(GLdouble x, GLdouble y, GLdouble z);
private:
    double x, y, z;
};

#endif // SCALE_H
