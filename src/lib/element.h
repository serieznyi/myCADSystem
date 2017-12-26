#ifndef ELEMENT_H
#define ELEMENT_H

#include "QOpenGLWidget"
#include <QString>

class Element
{
public:
    Element();
    void setGID(long n);         //  Установить GID
    long getGID();               //  Получить GID
    void setTypeName(int a);    //  Установить флаг примитива
    int getTypeName();
    virtual void Apply(int mode) = 0;    //  Применить действие

private:
    long            GID;         //  Глобальный идентификатор элемента
    int             type_name;

};

#endif // ELEMENT_H
