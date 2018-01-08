// Базовый класс действий
#ifndef ACTION_H
#define ACTION_H

#include <QOpenGLWidget>
#include "src/lib/element.h"
#include "src/resource.h"

class Action : public Element
{
public:
    explicit Action(bool mode=true);
};

#endif // ACTION_H
