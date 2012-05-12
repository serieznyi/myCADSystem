#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QGLWidget>
#include <QStack>
#include <QColor>
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
    void setColor(int color[3]);
private:
    int ID_COLOR[3];
    int COLOR[3];
    int PAINT_MODE;
    QStack<QColor> colors_arr;
};


#endif // PRIMITIVE_H
