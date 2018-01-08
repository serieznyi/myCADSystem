// Панель проекций вида

#ifndef PAINTINGZONE_H
#define PAINTINGZONE_H

#include <QSplitter>
#include "src/GLWidget.h"
#include "src/resource.h"

//#include "matrix.h"
//#include "invers.h"

class PaintingZone : public QWidget
{
public:
    explicit PaintingZone(QWidget *parent = 0);
    void Update();
    void setAllUnvisible(bool a);
    void saveProjectionLastState();
    void loadProjectionLastState();

public:
    QSplitter           *sp_global;
    QSplitter           *sp_top;
    QSplitter           *sp_down;
    GLWidget            *widPerspective;           // Перспективная проекция
    GLWidget            *widTop;                   // YOX
    GLWidget            *widFront;                 // ZOX
    GLWidget            *widRight;                 // XOY
    QVBoxLayout         *lay_global;               // Глобальный менеджер компоновки
public slots:
    void setMaximum(int i);
};

#endif // PAINTINGZONE_H
