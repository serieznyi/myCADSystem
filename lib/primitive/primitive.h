#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QGLWidget>
#include "lib/element.h"
#include "resource.h"

class Primitive : public Element
{
public:
    Primitive();
    int* getIDColor();
    void setIDColor(int *a);
    int *getColor();
    void setColor(int *a);
private:
    int *ID_COLOR;
    int *COLOR;
};


#endif // PRIMITIVE_H
