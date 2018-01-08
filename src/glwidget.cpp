#include "glwidget.h"
#include "src/gui/paintingzone.h"
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include "src/gui/mainwindow.h"

//  Главные

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    // ПОЧИСТИТЬ!
    koef = 1;
    pMW = dynamic_cast<MainWindow*>(parent);
    contextMenuPrimitive = new ContextMenu(MCM_PRIMITIVE,this);
    currentOrtho = Ortho();
    //color_selected_prim = {0};
    this->SELECTED            = false;
    this->AXES                = true;
    this->PLANE               = true;
    this->PAINTING_MODE       = MODE_REAL;
    lastProjection      =0;
    currentWork         = pMW->getWork();
    currenEvent         = pMW->getCurEvent();
    previousEvent       = pMW->getPrevEvent();
    n                   = 0;
    xRot                = 0;
    yRot                = 0;
    zRot                = 0;
    xTranslate                = 0;
    yTranslate                = 0;
    zTranslate                = 0;
    gScale              = 1;
    currentPos        = QPoint();
    lastPos              = QPoint();
    comboBox            = new QComboBox();
    lay_global_v        = new QVBoxLayout();
    lay_global_h        = new QHBoxLayout();
    comboBox->addItem(QString::fromLocal8Bit("Перспектива"));
    comboBox->addItem(QString::fromLocal8Bit("Верх"));
    comboBox->addItem(QString::fromLocal8Bit("Бок"));
    comboBox->addItem(QString::fromLocal8Bit("Перед"));
    comboBox->addItem(QString::fromLocal8Bit("Во весь экран"));
    comboBox->addItem(QString::fromLocal8Bit("Сброс"));
    lay_global_h->addWidget(comboBox);
    lay_global_h->addStretch(3);
    lay_global_v->addLayout(lay_global_h);
    lay_global_v->addStretch(3);
    this->setLayout(lay_global_v);

    ////////////////////////
    Mx = 0; My = 0;           // Позиция Курсора (обработанная)
    prevMx = 0; prevMy = 0;   // Предыдущая позиция курсора?

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeProection(int)));

    setMouseTracking(true);
}

void GLWidget::initializeGL()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);                  // цвет "очистки порта вида"
    glEnable(GL_DEPTH_TEST);                            // буфер глубины
    //glStencilMask(l);// число битов, задающее маску
    glEnable(GL_STENCIL_TEST);                          // буфер трафарета
    glClearStencil(0); // значение заполнения буфера трафарета при очистке
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);


    glMatrixMode(GL_MODELVIEW);                     // включить матрицу вида
}

void GLWidget::resizeGL(int _w, int _h)
{
    int w = _w, h = _h;
    if(w!=0&&h!=0)
    {
        currentOrtho.width = w;
        currentOrtho.height = h;
    }
    else
    {
        currentOrtho.width = currentOrtho.last_width;
        currentOrtho.height = currentOrtho.last_height;
        w = currentOrtho.last_width;
        h = currentOrtho.last_height;
    }

    currentOrtho.left_val = -w/h*2;
    currentOrtho.right_val = w/h*2;
    currentOrtho.top_val = -w/h;
    currentOrtho.down_val = w/h;
    currentOrtho.near_val = -10;
    currentOrtho.far_val = 10;

    glViewport(0, 0, currentOrtho.width, currentOrtho.height);                         // Размер порта вида
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    glOrtho(currentOrtho.left_val,
            currentOrtho.right_val,
            currentOrtho.top_val,
            currentOrtho.down_val,
            currentOrtho.near_val,
            currentOrtho.far_val);                                  // Размер ортогональной проекции
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //  glGetDoublev(GL_MODELVIEW_MATRIX, &startMatrix[0][0]);
    //  copyMatrix(inversStartMatrix, startMatrix);
    //  inversMatrix(inversStartMatrix);
}

void GLWidget::paintGL()
{
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);   // Очистка буферов
    glPolygonMode(GL_FRONT, GL_FILL);          // Режим отрисовки

    glScalef(gScale, gScale, gScale);
    glTranslatef(xTranslate, yTranslate, zTranslate);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    if(this->getProjection()==MPJ_FRONT)
    {
        glPushMatrix();
        glTranslated(0,0,-currentOrtho.far_val);
        glRotated(-90, 1, 0, 0);
        if(PAINTING_MODE!=MODE_FICTIVE)
            this->drawPlane();
        glPopMatrix();
    }
    else if(this->getProjection()==MPJ_RIGHT)
    {
        glPushMatrix();
        glTranslated(currentOrtho.far_val, 0, 0);
        glRotatef(90, 0, 0, 1);
        if(PAINTING_MODE!=MODE_FICTIVE)
            this->drawPlane();
        glPopMatrix();
    }
    else
    {
        if(PAINTING_MODE!=MODE_FICTIVE)
            this->drawPlane();
    }

    if(PAINTING_MODE==MODE_FICTIVE)
        glDisable(GL_LIGHTING);
    else
        glEnable(GL_LIGHTING);

    currentWork->drawWork(PAINTING_MODE);
    if(PAINTING_MODE!=MODE_FICTIVE)
    {
        glDisable(GL_LIGHTING);
        drawAxes();
    }
    /*
    GLUquadric *quad = gluNewQuadric();

    glStencilFunc(GL_NEVER, 1, 1); // значение mask не используется
    glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);


    glColor3d(1,0,0);
    gluSphere(quad, 1.0, 20, 20);


    glTranslated(0.7, 0, 0);

    glStencilFunc(GL_NOTEQUAL, 1, 1); // значение mask не используется
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

    glColor3d(0,1,0);
    gluSphere(quad, 1.0, 20, 20);*/


}

void GLWidget::mousePressEvent(QMouseEvent *event)
{        
    getSelectedPrimitiveID(event);

    if(event->button()==Qt::RightButton&&SELECTED)
    {
        contextMenuPrimitive->exec(event->globalPos());
    }

    switch(*currenEvent)
    {
    case MEL_SPHERE:
    case MEL_CUBE:
    case MEL_PYRAMID:
    case MEL_CYLINDER:
        addPrimitive();
        previousEvent = currenEvent;
        pMW->setCurEvent(MEV_CAMERA_TRANSLATE);
        break;
    case MEV_ROTATE:
        if(SELECTED)
            addAction(MEV_ROTATE);
        break;
    case MEV_TRANSLATE:
        if(SELECTED)
            addAction(MEV_TRANSLATE);
        break;
    case MEV_SCALE:
        if(SELECTED)
            addAction(MEV_SCALE);
        break;
    case MEV_STRETCH:
        if(SELECTED)
            addAction(MEV_STRETCH);
        break;

    case MEV_GROUP:
    {
        if(currentWork->getGroupObj1()==-1)
            currentWork->setGroupObj1(pMW->selected_prim);
        else if(currentWork->getGroupObj2()==-1)
            currentWork->setGroupObj2(pMW->selected_prim);

        if(currentWork->getGroupObj1()>-1&&currentWork->getGroupObj2()>-1)
            eventGroupPrimitive(currentWork->getGroupObj1(), currentWork->getGroupObj2());

        break;
    }
    case MEV_SUBSTRACT:
    {
        if(currentWork->getGroupObj1()==-1)
            currentWork->setGroupObj1(pMW->selected_prim);
        else if(currentWork->getGroupObj2()==-1)
            currentWork->setGroupObj2(pMW->selected_prim);

        if(currentWork->getGroupObj1()>-1&&currentWork->getGroupObj2()>-1)
            eventSubstractPrimitive(currentWork->getGroupObj1(), currentWork->getGroupObj2());

        break;
    }
    case MEV_INTERSECT:
    {
        if(currentWork->getGroupObj1()==-1)
            currentWork->setGroupObj1(pMW->selected_prim);
        else if(currentWork->getGroupObj2()==-1)
            currentWork->setGroupObj2(pMW->selected_prim);

        if(currentWork->getGroupObj1()>-1&&currentWork->getGroupObj2()>-1)
            eventIntersectPrimitive(currentWork->getGroupObj1(), currentWork->getGroupObj2());

        break;
    }
    default:break;
    }

    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    currentPos.setX(event->x() - lastPos.x());
    currentPos.setY(event->y() - lastPos.y());
    if(event->buttons() && Qt::LeftButton)
        selectEvent(event, currentPos);
    lastPos = event->pos();

    pMW->getStatusBar()->showMessage("Window: "+QString::number(event->pos().x())+"   "+QString::number(event->pos().y())+
                                     "      OpenGL: "+QString::number(ScreenToOGL(event->pos().x(), COORD_X))+"   "
                                     +QString::number(ScreenToOGL(event->pos().y(), COORD_Y))
                                     +QString::fromLocal8Bit("      Событие: ")+getTextEvent(*currenEvent));
}

void GLWidget::setProjection(int i)
{
    this->PROJECTION_TYPE = i;
    glLoadIdentity();
    switch(i)
    {
    case MPJ_FRONT:
        xRot = 0;
        yRot = 0;
        zRot = 0;
        this->comboBox->setCurrentIndex(3);
        break;
    case MPJ_TOP:
        xRot = -90.0f*16;
        yRot = 0;
        zRot = 0;
        this->comboBox->setCurrentIndex(1);
        break;
    case MPJ_RIGHT:
        xRot = 0;
        yRot = 90.0f*16;
        zRot = 0;
        this->comboBox->setCurrentIndex(2);
        break;
    case MPJ_PERSPECTIVE:
        xRot = 10.0f*16;
        yRot = 10.0f*16;
        zRot = 0;
        this->comboBox->setCurrentIndex(0);
        break;
    }
    this->update();
}

int GLWidget::getProjection()
{
    return PROJECTION_TYPE;
}

void GLWidget::changeProection(int n)
{
    switch(n)
    {
    case MPJ_PERSPECTIVE:
        setProjection(MPJ_PERSPECTIVE);
        break;
    case MPJ_TOP:
        setProjection(MPJ_TOP);
        break;
    case MPJ_RIGHT:
        setProjection(MPJ_RIGHT);
        break;
    case MPJ_FRONT:
        setProjection(MPJ_FRONT);
        break;
    case MPJ_MAXIMAZE:
        //pMW->getPaintingZone()->saveProjectionLastState();
        pMW->getPaintingZone()->setMaximum(this->PROJECTION_TYPE);
        break;
    case MPJ_RESET:
        pMW->getPaintingZone()->setAllUnvisible(false);
        pMW->getPaintingZone()->loadProjectionLastState();
        break;
    }
}

void GLWidget::SaveLastState()
{
    currentOrtho.last_height = currentOrtho.height;
    currentOrtho.last_width = currentOrtho.width;
    this->lastProjection = getProjection();

}

void GLWidget::LoadLastState()
{
    currentOrtho.height = currentOrtho.last_height;
    currentOrtho.width = currentOrtho.last_width;
    setProjection(this->lastProjection);
}

void GLWidget::selectEvent(QMouseEvent *event, QPoint current)
{
    switch(*currenEvent)
    {
    case MEV_CAMERA_TRANSLATE:
        eventTranslateCamera(event,current);
        break;

    case MEV_TRANSLATE:
        if(SELECTED)
            eventTranslatePrimitive(event);
        else
            eventTranslateCamera(event,current);
        break;

    case MEV_CAMERA_ROTATE:
        eventRotateCamera(event, current);
        break;

    case MEV_ROTATE:
        if(SELECTED)
            eventRotatePrimitive(event, current);
        else
            eventRotateCamera(event,current);
        break;

    case MEV_CAMERA_ZOOM:
        eventZoomCamera(event, current);
        break;

    case MEV_SCALE:
        if(SELECTED)
            eventScalePrimitive(current);
        else
            eventZoomCamera(event, current);
        break;
    case MEV_STRETCH:
        if(SELECTED)
            eventStretchPrimitive(current);
        break;

    }
}

//  Камера

void GLWidget::eventTranslateCamera(QMouseEvent *event, QPoint current)
{
    if(this->getProjection()==MPJ_TOP){
        if(current.x()>0){
            xTranslate += step_translate;
        }
        else if(current.x()<0){
            xTranslate -= step_translate;
        }
        if(current.y()>0){
            yTranslate -= step_translate;
        }
        else if(current.y()<0){
            yTranslate += step_translate;
        }
        this->update();
        return;
    }

    if(this->getProjection()==MPJ_RIGHT){
        if(current.x()>0){
            xTranslate += step_translate;
        }
        else if(current.x()<0){
            xTranslate -= step_translate;
        }
        if(current.y()>0){
            yTranslate -= step_translate;
        }
        else if(current.y()<0){
            yTranslate += step_translate;
        }

        this->update();
        return;
    }

    if(this->getProjection()==MPJ_FRONT){
        if(current.x()>0){
            xTranslate += step_translate;
        }
        else if(current.x()<0){
            xTranslate -= step_translate;
        }
        if(current.y()>0){
            yTranslate -= step_translate;
        }
        else if(current.y()<0){
            yTranslate += step_translate;
        }
        this->update();
        return;
    }

    if(this->getProjection()==MPJ_PERSPECTIVE){
        if(current.x()>0){
            xTranslate += step_translate;
            //xCamPos -= step_translate;
            //xCamLook -= step_translate;
        }
        else if(current.x()<0){
            xTranslate -= step_translate;
            //xCamPos += step_translate;
            //xCamLook += step_translate;
        }
        if(current.y()>0){
            yTranslate -= step_translate;
            //zCamPos -= step_translate;
            //zCamLook -= step_translate;
        }
        else if(current.y()<0){
            yTranslate += step_translate;
            //zCamPos += step_translate;
            //zCamLook += step_translate;
        }
        this->update();
        return;
    }

    //R = sqrt((xCamLook-xCamPos)*(xCamLook-xCamPos)+(zCamLook-zCamPos)*(zCamLook-zCamPos));
}

void GLWidget::eventZoomCamera(QMouseEvent *event, QPoint current)
{
    if(this->getProjection()==MPJ_TOP){
        if(current.y()>0)
            gScale -= step_scale;
        else if(current.y()<0)
            gScale += step_scale;

        this->update();
    }
    else if(this->getProjection()==MPJ_RIGHT){
        if(current.y()>0)
            gScale -= step_scale;
        else if(current.y()<0)
            gScale += step_scale;
        this->update();
    }
    else if(this->getProjection()==MPJ_FRONT){
        if(current.y()>0)
            gScale -= step_scale;
        else if(current.y()<0)
            gScale += step_scale;

        this->update();
    }
    /*
    else if(isPerspectiveW){
        if(current.y()>0){
            yCamPos -= step_translate;
            zCamPos -= step_translate;
        }
        else if(current.y()<0){
            yCamPos += step_translate;
            zCamPos += step_translate;
        }
        this->update();
        return;
    }
*/

    koef = calcKoef();
}

void GLWidget::eventRotateCamera(QMouseEvent *event, QPoint current)
{
    if(this->getProjection()==MPJ_TOP)
        setYRotation(yRot + 8 * current.x());

    if(this->getProjection()==MPJ_FRONT)
        setZRotation(zRot + (-8) * current.x());

    if(this->getProjection()==MPJ_RIGHT)
    {
        setXRotation(xRot + 8 * current.x());
    }

    if(this->getProjection()==MPJ_PERSPECTIVE){

        GLdouble matrix[4][4], workMatrix[4][4];

        glGetDoublev(GL_MODELVIEW_MATRIX, &matrix[0][0]);
        copyMatrix(workMatrix, inversStartMatrix);
        multMatrix(workMatrix, matrix);
        glLoadMatrixd(&startMatrix[0][0]);

        if (prevMx != event->x()) {
            glRotated((double)(lastPos.x() - event->x()), 0, -1, 0);
        }
        if (prevMy != event->y()) {
            glRotated((double)(lastPos.y() - event->y()), -1, 0, 0);
        }
/*


        if(current.x()>0)
        {
            setYRotation(yRot + 8 * current.x());
            //n += 3.14/sector;
            //xCamLook +=R*sin(n);
            //zCamLook +=R*cos(n);
        }
        if(current.x()<0)
        {
            setYRotation(yRot + 8 * current.x());
            //n -= 3.14/sector;
            //xCamLook -=R*sin(n);
            // zCamLook -=R*cos(n);
        }
        if(current.y()>0)
        {
            setZRotation(zRot + 8 * current.x());
            //n += 3.14/sector;
            //xCamLook +=R*sin(n);
            //zCamLook +=R*cos(n);
        }
        if(current.y()<0)
        {
            setZRotation(zRot + 8 * current.x());
        }
*/

        glMultMatrixd(&workMatrix[0][0]);
    }


    this->update();
    return;
}

//  Примитивы

void GLWidget::addPrimitive(QPoint pos)
{
    if(pos.x()==0&&pos.y()==0)
        currentWork->addPrimitive(*currenEvent);
    else
    {
        double x = ScreenToOGL(pos.x(), COORD_X);
        double y = ScreenToOGL(pos.y(), COORD_Y);
        qDebug()<<x<<" "<<y;
        currentWork->addPrimitive(*currenEvent, QPoint(x,y));
    }

    pMW->Update();
}

void GLWidget::addPrimitive(int i)
{
    currentWork->addAction(i);
    pMW->Update();
}

void GLWidget::addAction(int i)
{
    currentWork->addAction(*currenEvent);
}

void GLWidget::deletePrimitive()
{
    currentWork->deletePrimitive(pMW->selected_prim);
    pMW->Update();
}

void GLWidget::eventTranslatePrimitive(QMouseEvent *event)
{
    Translate *translate =currentWork->getList()->at(pMW->selected_prim)->getTranslate();

    double new_Mx = currentOrtho.width/2 - event->pos().x();
    double new_My = event->pos().y() - currentOrtho.height/2;
    Mx = prevMx - new_Mx;
    My = prevMy - new_My;
    prevMx = new_Mx;
    prevMy = new_My;

    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_TOP)
    {
        translate->move(ScreenToOGL(Mx, COORD_X), 0, ScreenToOGL(My, COORD_Y));
        pMW->Update();
        return;
    }

    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_FRONT)
    {
        translate->move(ScreenToOGL(Mx, COORD_X), ScreenToOGL(My, COORD_Y), 0);
        pMW->Update();
        return;
    }

    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_RIGHT)
    {
        translate->move(0, ScreenToOGL(My, COORD_Y), ScreenToOGL(Mx, COORD_X));
        pMW->Update();
        return;
    }
}

void GLWidget::eventRotatePrimitive(QMouseEvent *event, QPoint current)
{
    Rotate *rotate =currentWork->getList()->at(pMW->selected_prim)->getRotate();
    switch(getProjection())
    {
    case MPJ_TOP:
        if(current.x()>0){
            rotate->RotateY(step_rotate);
        }
        else if(current.x()<0){
            rotate->RotateY(-1*step_rotate);
        }
        if(current.y()>0){
            rotate->RotateY(step_rotate);
        }
        else if(current.y()<0){
            rotate->RotateY(-1*step_rotate);
        }

        pMW->Update();
        break;
    case MPJ_FRONT:
        if(current.x()<0){
            rotate->RotateZ(step_rotate);
        }
        else if(current.x()>0){
            rotate->RotateZ(-1*step_rotate);
        }
        if(current.y()<0){
            rotate->RotateZ(step_rotate);
        }
        else if(current.y()>0){
            rotate->RotateZ(-1*step_rotate);
        }
        pMW->Update();
        break;
    case MPJ_RIGHT:
        if(current.x()>0){
            rotate->RotateX(step_rotate);
        }
        else if(current.x()<0){
            rotate->RotateX(-1*step_rotate);
        }
        if(current.y()>0){
            rotate->RotateX(step_rotate);
        }
        else if(current.y()<0){
            rotate->RotateX(-1*step_rotate);
        }
        pMW->Update();
        break;
    case MPJ_PERSPECTIVE:
        break;
    }
}

void GLWidget::eventGroupPrimitive(long obj1, long obj2)
{
    if(obj1==obj2)
    {
        QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка"),
                              QString::fromLocal8Bit("Невозможно групировать с самим собой!"));
        currentWork->setGroupObj1(-1);
        currentWork->setGroupObj2(-1);
        return;
    }
    if(intersectionGroupObj(obj1,obj2))
    {
        addPrimitive(MEV_GROUP);
        QMessageBox::about(this, QString::fromLocal8Bit("Операция выполнена"),
                           QString::fromLocal8Bit("Объекты сгрупированы!"));
        currentWork->setGroupObj1(-1);
        currentWork->setGroupObj2(-1);
    }
    else
    {
        QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка"),
                              QString::fromLocal8Bit("Объекты не пересекаются!"));
        currentWork->setGroupObj1(-1);
        currentWork->setGroupObj2(-1);
        return;
    }
}

void GLWidget::eventSubstractPrimitive(long obj1, long obj2)
{
    if(obj1==obj2)
    {
        QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка"),
                              QString::fromLocal8Bit("Невозможно вычесть из самого себя!"));
        currentWork->setGroupObj1(-1);
        currentWork->setGroupObj2(-1);
        return;
    }
    if(intersectionGroupObj(obj1,obj2))
    {
        addPrimitive(MEV_SUBSTRACT);
        QMessageBox::about(this, QString::fromLocal8Bit("Операция выполнена"),
                           QString::fromLocal8Bit("Объект вычтен!"));
        currentWork->setGroupObj1(-1);
        currentWork->setGroupObj2(-1);
    }
    else
    {
        QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка"),
                              QString::fromLocal8Bit("Объекты не пересекаются!"));
        currentWork->setGroupObj1(-1);
        currentWork->setGroupObj2(-1);
        return;
    }

}

void GLWidget::eventIntersectPrimitive(long obj1, long obj2)
{
    if(obj1==obj2)
    {
        QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка"),
                              QString::fromLocal8Bit("Невозможно пересечь с самим сабой!"));
        currentWork->setGroupObj1(-1);
        currentWork->setGroupObj2(-1);
        return;
    }
    if(intersectionGroupObj(obj1,obj2))
    {
        addPrimitive(MEV_INTERSECT);
        QMessageBox::about(this, QString::fromLocal8Bit("Операция выполнена"),
                           QString::fromLocal8Bit("Объекты пересечены!"));
        currentWork->setGroupObj1(-1);
        currentWork->setGroupObj2(-1);
    }
    else
    {
        QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка"),
                              QString::fromLocal8Bit("Объекты не пересекаются!"));
        currentWork->setGroupObj1(-1);
        currentWork->setGroupObj2(-1);
        return;
    }
}

void GLWidget::eventScalePrimitive(QPoint poin)
{
    Scale *scale =currentWork->getList()->at(pMW->selected_prim)->getScale();

    if(poin.y()<0){
        scale->ScaleYXY(step_scale, step_scale, step_scale);
    }
    else if(poin.y()>0){
        scale->ScaleYXY(-1*step_scale, -1*step_scale, -1*step_scale);
    }

    pMW->Update();
}

void GLWidget::eventStretchPrimitive(QPoint poin)
{
    Scale *scale =currentWork->getList()->at(pMW->selected_prim)->getScale();

    switch(getProjection())
    {
    case MPJ_TOP:
        if(poin.x()>0){
            scale->ScaleX(step_scale);
        }
        else if(poin.x()<0){
            scale->ScaleX(-1*step_scale);
        }
        if(poin.y()<0){
            scale->ScaleZ(step_scale);
        }
        else if(poin.y()>0){
            scale->ScaleZ(-1*step_scale);
        }

        pMW->Update();
        break;
    case MPJ_FRONT:
        if(poin.x()>0){
            scale->ScaleX(step_scale);
        }
        else if(poin.x()<0){
            scale->ScaleX(-1*step_scale);
        }
        if(poin.y()<0){
            scale->ScaleY(step_scale);
        }
        else if(poin.y()>0){
            scale->ScaleY(-1*step_scale);
        }

        pMW->Update();
        break;
    case MPJ_RIGHT:
        if(poin.x()>0){
            scale->ScaleZ(step_scale);
        }
        else if(poin.x()<0){
            scale->ScaleZ(-1*step_scale);
        }
        if(poin.y()<0){
            scale->ScaleY(step_scale);
        }
        else if(poin.y()>0){
            scale->ScaleY(-1*step_scale);
        }

        pMW->Update();
        break;
    }


    pMW->Update();
}

//  Рисование
void GLWidget::drawAxes()
{
    glLoadIdentity();
    glTranslated(2.9, -1.4, 5);
    glScaled(0.5, 0.5, 0.5);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);//Цвет оси X
    // Ось X
    glVertex3d(0, 0, 0);
    glVertex3d(1, 0, 0);
    glPushMatrix();
    glLineWidth(3);
    glTranslated(1.2, 0, 0);
    glScaled(0.2, 0.2, 0.2);
    //drawX();
    glLineWidth(2);
    glPopMatrix();
    glColor3ub(0, 255, 0);//Цвет оси Y
    // Ось Y
    glVertex3d(0, 0, 0);
    glVertex3d(0, 1, 0);
    glPushMatrix();
    glLineWidth(3);
    glTranslated(0, 1.2, 0);
    glScaled(0.3, 0.3, 0.3);
    glLineWidth(2);
    //   drawY();
    glPopMatrix();
    glColor3ub(0, 0, 255);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 1);
    glPushMatrix();
    glLineWidth(3);
    glTranslated(0, 0, 1.2);
    glScaled(0.3, 0.3, 0.3);
    glLineWidth(2);
    //  drawZ();
    glPopMatrix();
    glEnd();
    glLineWidth(1);
}

void GLWidget::drawX()
{
    // Буква X
    glBegin(GL_LINES);
    glVertex3d(-1, 1, 0);
    glVertex3d(1, -1, 0);

    glVertex3d(-1, -1, 0);
    glVertex3d(1, 1, 0);
    glEnd();
}

void GLWidget::drawY()
{
    glBegin(GL_LINES);
    glVertex3d(-1, 1, 0);
    glVertex3d(1, 1, 0);
    glVertex3d(-1, -1, 0);
    glVertex3d(1, -1, 0);
    glVertex3d(-1, -1, 0);
    glVertex3d(1, -1, 0);
    glEnd();
}

void GLWidget::drawZ()
{
    glBegin(GL_LINE);
    glVertex3d(-0.8, 1, 0);
    glVertex3d(0, 0, 0);

    glVertex3d(0.8, 1, 0);
    glVertex3d(0, 0, 0);

    glVertex3d(0, 0, 0);
    glVertex3d(0, -1, 0);
    glEnd();
}

void GLWidget::drawPlane()
{
    glColor3f(0.0f, 0.0f, 0.0f);

    for(double i=PLANE_MIN_X; i<=PLANE_MAX_X;i+=0.5)
    {
        glBegin(GL_LINES);
        glVertex3d(PLANE_MIN_X, 0, i);
        glVertex3d(PLANE_MAX_X, 0, i);

        glVertex3d(i, 0, PLANE_MIN_Z);
        glVertex3d(i, 0, PLANE_MAX_Z);
        glEnd();
    }
}

//  Дополнительные

double GLWidget::ScreenToOGL(int coord, int type) {

    double opengl_pix;

    switch(type)
    {
    case COORD_X:
    {
        double proj_x = (currentOrtho.width/currentOrtho.height*(double)4);
        opengl_pix =(proj_x/currentOrtho.width);
        break;
    }
    case COORD_Y:
    {
        double proj_y=((currentOrtho.width/currentOrtho.height)*(double)2);
        opengl_pix =(proj_y/currentOrtho.height);
        break;
    }
    }


    return opengl_pix*(double)coord;
}

double GLWidget::ScreenToOGLv2(int last, int coord, int type) {

    double opengl_pix;
    double result = 0;

    switch(type)
    {

    case COORD_X:
    {
        double proj_x = (currentOrtho.width/currentOrtho.height*(double)4);
        opengl_pix =(proj_x/currentOrtho.width);
        if(coord>last)
        {
            result = opengl_pix*((double)coord-((double)last));
        }
        else if(coord<last)
        {
            result = opengl_pix*((double)coord-(double)last);
        }

        break;
    }
    case COORD_Y:
    {
        double proj_y=((currentOrtho.width/currentOrtho.height)*(double)2);
        opengl_pix =(proj_y/currentOrtho.height);

        if(coord>last)
        {
            result = (-1)*opengl_pix*((double)coord-((double)last));
        }
        else if(coord<last)
        {
            result = (-1)*opengl_pix*((double)coord-((double)last));
        }


        break;
    }
    }

    return result;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        update();
    }
}

void GLWidget::qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

// TEMP

void GLWidget::initializeLighting()
{

}

long GLWidget::getSelectedPrimitiveID(QMouseEvent *event)
{
    PAINTING_MODE = MODE_FICTIVE;
    update();
    glReadPixels(event->pos().x(), currentOrtho.height - event->pos().y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
    PAINTING_MODE = MODE_REAL;
    update();

    QList<Container*> *elements= currentWork->getList();

    if(elements->size()>0)
    {

        for(int i=0;i<elements->size();i++)
        {
            Container *cont = elements->at(i);
            MCOLOR *color = 0;// Цвет примитива из контейнера
            GLubyte ba[3] = {0};
            color = cont->getPrimitive()->getIDColor();
            ba[0] = (GLubyte)color->red;
            ba[1] = (GLubyte)color->green;
            ba[2] = (GLubyte)color->blue;

            if(ba[0]==pixel[0]&&ba[1]==pixel[1]&&ba[2]==pixel[2])
            {
                SELECTED = true;
                //делаем точку в которой кликнули началом системы координат
                prevMx = currentOrtho.width/2 - event->pos().x();
                prevMy = event->pos().y() - currentOrtho.height/2;
                pMW->selected_prim = i;
                return i;

            }
            else
            {
                SELECTED = false;
            }
        }
    }

    return -1;

}

double GLWidget::calcKoef()
{
    if(gScale<1)
    {
        return 1+(1-gScale);
    }
    qDebug()<<koef;
    return 1;
}

bool GLWidget::intersectionGroupObj(long obj1, long obj2)
{/*
    Element *prim1 = currentWork->element_list->at(obj1);
    Element *prim2 = currentWork->element_list->at(obj2);
    switch(prim1->getTypeName())
    {
        case MEL_CUBE:
        //     prim1->
            break;
        case MEL_SPHERE:
            break;
    }
*/
    return true;
}

QString GLWidget::getTextEvent(int event)
{
    switch(event)
    {
    case MEV_ROTATE:
        return QString::fromLocal8Bit("Поворот примитива");
    case MEV_TRANSLATE:
        return QString::fromLocal8Bit("Перемещение примитива");
    case MEV_SCALE:
        return QString::fromLocal8Bit("Масштабирование примитива");
    case MEV_SUBSTRACT:
        return QString::fromLocal8Bit("Вычитание примитивов");
    case MEV_STRETCH:
        return QString::fromLocal8Bit("Растягивание примитива");
    case MEV_GROUP:
        return QString::fromLocal8Bit("Групировка примитивов");
    case MEV_INTERSECT:
        return QString::fromLocal8Bit("Пересечение");
    case MEV_CAMERA_ZOOM:
        return QString::fromLocal8Bit("Масшат камеры");
    case MEV_CAMERA_TRANSLATE:
        return QString::fromLocal8Bit("Перемещени камеры");
    case MEV_CAMERA_ROTATE:
        return QString::fromLocal8Bit("Поворот камеры");
    case MEL_CUBE:
        return QString::fromLocal8Bit("Куб");
    case MEL_PYRAMID:
        return QString::fromLocal8Bit("Пирамида");
    case MEL_SPHERE:
        return QString::fromLocal8Bit("Сфера");
    case MEL_CYLINDER:
        return QString::fromLocal8Bit("Цилиндр");
    default:return "ERROR";
    }
}
