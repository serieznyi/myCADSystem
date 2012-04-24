#ifndef ELEMENT_H
#define ELEMENT_H

#include "QGLWidget"
#include <QString>
#include "resource.h"

class Element
{
public:
    Element();
    void setGID(long n);         //  Установить GID
    long getGID();               //  Получить GID
    void setTypeName(int a);    //  Установить флаг примитива
    virtual void Apply() = 0;    //  Применить действие
    int getTypeName();

private:
    long            GID;         //  Глобальный идентификатор элемента
    int             type_name;
};

#endif // ELEMENT_H
