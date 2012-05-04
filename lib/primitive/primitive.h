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
    int* getColor();
    virtual void draw()=0;
    void setPaintMode(int mode);
    int getPaintMode();
private:
    int ID_COLOR[3];
    int COLOR[3];
    int PAINT_MODE;
};


#endif // PRIMITIVE_H
