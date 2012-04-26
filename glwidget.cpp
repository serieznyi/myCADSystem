#include "glwidget.h"
#include "paintingzone.h"
#include <QDebug>
#include "mainwindow.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    //color_selected_prim = {0};
    mode                = MODE_REAL;
    w                   =0;
    h                   =0;
    last_w              =0;
    last_h              =0;
    lastProjection      =0;
    pMW = dynamic_cast<MainWindow*>(parent);
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
    gScale              = 0.7f;
    p_currentPos        = QPoint();
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


    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeProection(int)));

    setMouseTracking(true);
}

void GLWidget::initializeGL()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);              // цвет "очистки порта вида"
    glEnable(GL_DEPTH_TEST);// буфер глубины
    glEnable(GL_COLOR_MATERIAL);                    // цвет материала
    glEnable(GL_LIGHTING);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);// авто нормаль


    glMatrixMode(GL_MODELVIEW);                     // включить матрицу вида
}

void GLWidget::resizeGL(int w, int h)
{
    if(w!=0&&h!=0)
    {
        this->w=w;
        this->h=h;
    }
    else
    {
        this->w=this->last_w;
        this->h=this->last_h;
        //this->comboBox->
    }

    glViewport(0, 0, this->w, this->h);                         // Установка порт вида
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double l=-this->w/this->h*2,
            r=this->w/this->h*2,
            t=-this->w/this->h,
            d=this->w/this->h,
            n=-10.0f,
            f=10.0f;
    glOrtho(l, r, t, d, n, f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::paintGL()
{
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   // Очистка буферов
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);          // Режим отрисовки

    glScalef(gScale, gScale, gScale);
    glTranslatef(xTranslate, yTranslate, zTranslate);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    //drawX();

    if(this->getProjection()==MPJ_FRONT)
    {
        glPushMatrix();
        //glScaled(-1, -1, -1);
        glTranslated(0,0,9);
        glRotated(-90, 1, 0, 0);

        this->drawPlane();                                  // Отрисовка плоскости
        glPopMatrix();
    }
    else if(this->getProjection()==MPJ_RIGHT)
    {
        glPushMatrix();
        glTranslated(-(w/h*2)*2, 0, 0);
        glRotatef(90, 0, 0, 1);
        this->drawPlane();                                  // Отрисовка плоскости
        glPopMatrix();
    }
    else
        this->drawPlane();                               // Отрисовка плоскости

    currentWork->drawWork(mode);

    drawAxes();

}

void GLWidget::drawAxes()
{
    glLoadIdentity();
    glTranslated(2.9, -1.4, 0);
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
    //glPushAttrib(GL_COLOR_BUFFER_BIT);
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
    //glPopAttrib();
}

void GLWidget::setProjection(int i)
{
    this->type_projection = i;
    glLoadIdentity();
    switch(i)
    {
    case MPJ_FRONT:
        xRot = 0;
        yRot = 180*16;
        zRot = 0;
        this->comboBox->setCurrentIndex(3);
        break;
    case MPJ_TOP:
        xRot     = -90.0f*16;
        yRot = 0;
        zRot = 0;
        this->comboBox->setCurrentIndex(1);
        break;
    case MPJ_RIGHT:
        xRot = 0;
        yRot = -90.0f*16;
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
    this->updateGL();
}

int GLWidget::getProjection()
{
    return type_projection;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    p_lastPos = event->pos();

    switch(*currenEvent)
    {
    case MEV_PRIM_SPHERE:
    case MEV_PRIM_QUAD:
    case MEV_PRIM_PYRAMID:
    case MEV_PRIM_POINT:
    case MEV_PRIM_CYLINDER:
    case MEV_PRIM_LINE:
        /*if(event->buttons()&&Qt::LeftButton&&isTopW)
            addPrimitive(event->pos());
        else */addPrimitive();
        previousEvent = currenEvent;
        pMW->setCurEvent(MEV_CAMERA_TRANSLATE);
        break;
    case MEV_TRANSLATE:
    case MEV_ROTATE:
        mode = MODE_FICTIVE;
        glDisable(GL_COLOR_MATERIAL);                    // цвет материала
        glDisable(GL_LIGHTING);
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
        glDisable(GL_LIGHT0);
        updateGL();
        glReadPixels(event->pos().x(), event->pos().y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color_selected_prim);
        mode = MODE_REAL;
        updateGL();
        qDebug()<<"PIXEL COLOR"<<color_selected_prim[0]<<" "<<color_selected_prim[1]<<" "<<color_selected_prim[2];

        break;
    default:break;
    }

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

    p_currentPos.setX(event->x() - p_lastPos.x());
    p_currentPos.setY(event->y() - p_lastPos.y());    
    if(event->buttons() && Qt::LeftButton )
        selectEvent(event, p_currentPos);
    p_lastPos = event->pos();
}

void GLWidget::selectEvent(QMouseEvent *event, QPoint current)
{
    switch(*currenEvent)
    {
    case MEV_CAMERA_TRANSLATE:
        eventTranslateCamera(event, current);
        break;
    case MEV_CAMERA_ZOOM:
        eventZoomCamera(event, current);
        break;
    case MEV_CAMERA_ROTATE:
        eventRotateCamera(event, current);
        break;
    case MEV_TRANSLATE:
        eventTranslatePrimitive(event, current);
        break;
    case MEV_ROTATE:
        eventRotatePrimitive(event, current);
        break;
    }

    //absMainWindow->getPaintZ()->Update();
}

void GLWidget::eventTranslateCamera(QMouseEvent *event, QPoint current)
{
    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_TOP){
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
        this->updateGL();
        return;
    }

    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_RIGHT){
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

        this->updateGL();
        return;
    }

    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_FRONT){
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
        this->updateGL();
        return;
    }

    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_PERSPECTIVE){
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
        this->updateGL();
        return;
    }

    //R = sqrt((xCamLook-xCamPos)*(xCamLook-xCamPos)+(zCamLook-zCamPos)*(zCamLook-zCamPos));
}

void GLWidget::eventTranslatePrimitive(QMouseEvent *event, QPoint current)
{


    //double step_translate_y = (w/h)/w;
    //double step_translate_x = ((w/h)*2)/h;
    double step_translate_y = 0.03;
    double step_translate_x = 0.03;
    if(currentWork->getOnlyPrimitiveList()->size()>0)
    {
        QList<int> *only_prim = currentWork->getOnlyPrimitiveList();

        //foreach (int i, only_prim)
        for(int i=0;i<only_prim->size();i++)
        {
            int index = only_prim->at(i);   // ИНдексы только примитивов
            Primitive *prim = dynamic_cast<Primitive*>(currentWork->getList()->at(index));
            int *na = 0;// Цвет примитива из контейнера
            GLubyte ba[3] = {0};
            na =prim->getIDColor();
            for(int i=0;i<3;i++)
                ba[i] = (GLubyte)na[i];

            if(ba[0]== color_selected_prim[0]&&ba[1]==color_selected_prim[1]&&ba[2]==color_selected_prim[2])
            {
                Translate *translate =dynamic_cast<Translate*>(currentWork->getList()->at(index-2));

                if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_TOP)
                {
                    if(current.x()>0){
                        translate->move(step_translate_x,0,0);
                    }
                    else if(current.x()<0){
                        translate->move(-step_translate_x,0,0);
                    }
                    if(current.y()>0){
                        translate->move(0,0,-step_translate_y);
                    }
                    else if(current.y()<0){
                        translate->move(0,0,step_translate_y);
                    }
                    pMW->Update();
                    return;
                }
                if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_FRONT)
                {
                    if(current.x()>0){
                        translate->move(-step_translate_x,0,0);
                    }
                    else if(current.x()<0){
                        translate->move(step_translate_x,0,0);
                    }
                    if(current.y()>0){
                        translate->move(0,-step_translate_y,0);
                    }
                    else if(current.y()<0){
                        translate->move(0,step_translate_y,0);
                    }
                    pMW->Update();
                    return;
                }
                if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_RIGHT)
                {
                    if(current.x()>0){
                        translate->move(0,0,-step_translate_x);
                    }
                    else if(current.x()<0){
                        translate->move(0,0,step_translate_x);
                    }
                    if(current.y()>0){
                        translate->move(0,-step_translate_y,0);
                    }
                    else if(current.y()<0){
                        translate->move(0,step_translate_y,0);
                    }
                    pMW->Update();
                    return;
                }
                if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_PERSPECTIVE)
                {

                }
                return;
            }
        }
    }
}

void GLWidget::eventRotatePrimitive(QMouseEvent *event, QPoint current)
{

    double step_rotate = 1;
    if(currentWork->getOnlyPrimitiveList()->size()>0)
    {
        QList<int> *only_prim = currentWork->getOnlyPrimitiveList();

        //foreach (int i, only_prim)
        for(int i=0;i<only_prim->size();i++)
        {
            int index = only_prim->at(i);
            Primitive *prim = dynamic_cast<Primitive*>(currentWork->getList()->at(index));
            int *na = 0;
            GLubyte ba[3] = {0};
            na =prim->getIDColor();
            for(int i=0;i<3;i++)
                ba[i] = (GLubyte)na[i];

            if(ba[0]==na[0]&&ba[1]==na[1]&&ba[2]==na[2])
            {
                Rotate *rotate =dynamic_cast<Rotate*>(currentWork->getList()->at(index-1));

                if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_TOP)
                {
                    if(current.x()>0){
                        rotate->RotateZ(step_rotate);
                    }
                    else if(current.x()<0){
                        rotate->RotateZ(-step_rotate);
                    }
                    if(current.y()>0){
                        rotate->RotateX(step_rotate);
                    }
                    else if(current.y()<0){
                        rotate->RotateX(-step_rotate);
                    }
                    pMW->Update();
                    return;
                }
                if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_FRONT)
                {

                }
                if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_RIGHT)
                {

                }
                if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_PERSPECTIVE)
                {

                }


                //translate->move(step_translate,step_translate,step_translate);
                //pMW->Update();
                return;
            }
        }
    }
}

void GLWidget::eventZoomCamera(QMouseEvent *event, QPoint current)
{
    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_TOP){
        if(current.y()>0)
            gScale -= step_scale;
        else if(current.y()<0)
            gScale += step_scale;

        this->updateGL();
        return;
    }

    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_RIGHT){
        if(current.y()>0)
            gScale -= step_scale;
        else if(current.y()<0)
            gScale += step_scale;
        this->updateGL();
        return;
    }

    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_FRONT){
        if(current.y()>0)
            gScale -= step_scale;
        else if(current.y()<0)
            gScale += step_scale;

        this->updateGL();
        return;
    }
    /*
    if(event->buttons() && Qt::LeftButton && isPerspectiveW){
        if(current.y()>0){
            yCamPos -= step_translate;
            zCamPos -= step_translate;
        }
        else if(current.y()<0){
            yCamPos += step_translate;
            zCamPos += step_translate;
        }
        this->updateGL();
        return;
    }
*/
}

void GLWidget::eventRotateCamera(QMouseEvent *event, QPoint current)
{
    if(event->buttons()&&Qt::LeftButton&&this->getProjection()==MPJ_TOP){
        if(current.x()>0)
            setYRotation(yRot + 8 * current.x());
        if(current.x()<0)
            setYRotation(yRot + 8 * current.x());
    }

    if(event->buttons()&&Qt::LeftButton&&this->getProjection()==MPJ_FRONT){
        if(current.x()>0)
            setZRotation(zRot + 8 * current.x());
        if(current.x()<0)
            setZRotation(zRot + 8 * current.x());
    }

    if(event->buttons()&&Qt::LeftButton&&this->getProjection()==MPJ_RIGHT){
        if(current.x()>0)
            setXRotation(xRot + 8 * current.x());
        if(current.x()<0)
            setXRotation(xRot + 8 * current.x());
    }

    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_PERSPECTIVE){

        //int sector = 50000;

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
            //n -= 3.14/sector;
            //xCamLook -=R*sin(n);
            // zCamLook -=R*cos(n);
        }
        /*

            QString a = QString::number(xCamLook);
            a.append(" : ");
            a.append(QString::number(zCamLook));
            qDebug(a.toStdString().c_str());

            glBegin(GL_POLYGON);
            for(GLfloat i = 0.0f;i<(2.0f*3.14);i+=(3.14/sector))
            {
                x = R_circle*sin(i);
                y = R_circle*cos(i);
                glVertex3f(x,y,0.5f);
            }
            glEnd();

            if(current.y()>0){
                yCamLook -= step_translate;
            }
            else if(current.y()<0){
                yCamLook += step_translate;
            }*/
    }

    this->updateGL();
    return;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
    }
}

void GLWidget::qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
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
        pMW->getPaintZ()->saveAllLastState();
        pMW->getPaintZ()->setMaximum(this->type_projection);
        break;
    case MPJ_RESET:
        pMW->getPaintZ()->setAllUnvisible(false);
        break;
    }
}

void GLWidget::addPrimitive()
{
    currentWork->addPrimitive(*currenEvent);
    pMW->Update();
}

void GLWidget::addPrimitive(QPoint current)
{
    double modelview[16], projection[16];
    GLdouble obj[3];
    int viewport[4];
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    gluUnProject(current.x(), current.y(), 0, modelview, projection, viewport, &obj[0], &obj[1], &obj[2]);

    currentWork->addAction(MEV_TRANSLATE, obj);
    currentWork->addPrimitive(*currenEvent);
}

void GLWidget::SaveLastState()
{
    this->last_h = this->h;
    this->last_w = this->w;
    this->lastProjection = getProjection();

}
