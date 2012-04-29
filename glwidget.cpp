#include "glwidget.h"
#include "paintingzone.h"
#include <QDebug>
#include "mainwindow.h"

//  Главные

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    // ПОЧИСТИТЬ!
    pMW = dynamic_cast<MainWindow*>(parent);
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
    gScale              = 1.0f;
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

    ////////////////////////
    Mx = 0; My = 0;           // Позиция Курсора (обработанная)
    prevMx = 0; prevMy = 0;   // Предыдущая позиция курсора?

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeProection(int)));

    setMouseTracking(true);
}

void GLWidget::initializeGL()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);              // цвет "очистки порта вида"
    glEnable(GL_DEPTH_TEST);                        // буфер глубины
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //glEnable(GL_COLOR_MATERIAL);                    // цвет материала
    //glEnable(GL_LIGHTING);
    //glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_AUTO_NORMAL);// авто нормаль


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
}

void GLWidget::paintGL()
{
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   // Очистка буферов
    glPolygonMode(GL_FRONT, GL_POINTS);          // Режим отрисовки

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

        this->drawPlane();
        glPopMatrix();
    }
    else if(this->getProjection()==MPJ_RIGHT)
    {
        glPushMatrix();
        glTranslated(currentOrtho.far_val, 0, 0);
        glRotatef(90, 0, 0, 1);
        this->drawPlane();
        glPopMatrix();
    }
    else
        this->drawPlane();

    currentWork->drawWork(PAINTING_MODE);

    drawAxes();
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
        PAINTING_MODE = MODE_FICTIVE;
        updateGL();
        glReadPixels(event->pos().x(), event->pos().y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);
        PAINTING_MODE = MODE_REAL;
        updateGL();

        if(currentWork->getOnlyPrimitiveList()->size()>0)
        {
            QList<int> *only_prim = currentWork->getOnlyPrimitiveList();

            for(int i=0;i<only_prim->size();i++)
            {
                int index = only_prim->at(i);   // Индексы только примитивов
                Primitive *prim = dynamic_cast<Primitive*>(currentWork->getList()->at(index));
                int *na = 0;// Цвет примитива из контейнера
                GLubyte ba[3] = {0};
                na = prim->getIDColor();
                for(int i=0;i<3;i++)
                    ba[i] = (GLubyte)na[i];
                if(ba[0]==pixel[0]&&ba[1]==pixel[1]&&ba[2]==pixel[2])
                {
                    SELECTED = true;
                    selected_prim = index;
                    //делаем точку в которой кликнули началом системы координат
                    prevMx = currentOrtho.width/2 - event->pos().x();
                    prevMy = event->pos().y() - currentOrtho.height/2;

                }
                else
                {
                    SELECTED = false;
                }
            }
        }

        break;
    default:break;
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    p_currentPos.setX(event->x() - p_lastPos.x());
    p_currentPos.setY(event->y() - p_lastPos.y());
    if(event->buttons() && Qt::LeftButton)
        selectEvent(event, p_currentPos);
    p_lastPos = event->pos();

    pMW->getStatusBar()->showMessage("Window: "+QString::number(event->pos().x())+"   "+QString::number(event->pos().y())+
                                     "      OpenGL: "+QString::number(ScreenToOGL(event->pos().x(), COORD_X))+"   "
                                     +QString::number(ScreenToOGL(event->pos().y(), COORD_Y)));
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
    this->updateGL();
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
        pMW->getPaintingZone()->setMaximum(this->PROJECTION_TYPE);
        pMW->getPaintingZone()->saveProjectionLastState();
        break;
    case MPJ_RESET:
        pMW->getPaintingZone()->setAllUnvisible(false);
        break;
    }
}

void GLWidget::SaveLastState()
{
    currentOrtho.last_height = currentOrtho.height;
    currentOrtho.last_width = currentOrtho.width;
    this->lastProjection = getProjection();

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
        eventTranslatePrimitive(event);
        break;
    case MEV_ROTATE:
        eventRotatePrimitive(event, current);
        break;
    }
}

//  Камера

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

//  Примитивы

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

void GLWidget::eventTranslatePrimitive(QMouseEvent *event)
{
    QList<Element*> *list_elements = currentWork->getList();

    if(list_elements->size()>0 && SELECTED)
    {
        Translate *translate =dynamic_cast<Translate*>(currentWork->getList()->at(selected_prim-2));

        if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_TOP)
        {
            Mx = prevMx - (currentOrtho.width/2 - event->pos().x());
            My = prevMy - (event->pos().y() - currentOrtho.height/2);
            prevMx = currentOrtho.width/2 - event->pos().x();
            prevMy = event->pos().y() - currentOrtho.height/2;

            translate->move(ScreenToOGL(Mx, COORD_X), 0, ScreenToOGL(My, COORD_Y));

            pMW->Update();
            return;
        }

        if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_FRONT)
        {
            Mx = prevMx - (currentOrtho.width/2 - event->pos().x());
            My = prevMy - (event->pos().y() - currentOrtho.height/2);
            prevMx = currentOrtho.width/2 - event->pos().x();
            prevMy = event->pos().y() - currentOrtho.height/2;

            translate->move(ScreenToOGL(Mx, COORD_X), ScreenToOGL(My, COORD_Y), 0);

            pMW->Update();
            return;
        }

        if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_RIGHT)
        {
            Mx = prevMx - (currentOrtho.width/2 - event->pos().x());
            My = prevMy - (event->pos().y() - currentOrtho.height/2);
            prevMx = currentOrtho.width/2 - event->pos().x();
            prevMy = event->pos().y() - currentOrtho.height/2;

            translate->move(0, ScreenToOGL(My, COORD_Y), ScreenToOGL(Mx, COORD_X));

            pMW->Update();
            return;
        }
        /*
    if(event->buttons() && Qt::LeftButton && this->getProjection()==MPJ_PERSPECTIVE && SELECTED)
    {
        Mx = prevMx - (w/2 - event->pos().x());
        My = prevMy - (event->pos().y() - h/2);
        prevMx = w/2 - event->pos().x();
        prevMy = event->pos().y() - h/2;

        translate->move(ScreenToOGL(Mx, COORD_X), 0, ScreenToOGL(My, COORD_Y));

        pMW->Update();
        return;
    }*/
    }
}

void GLWidget::eventRotatePrimitive(QMouseEvent *event, QPoint current)
{

    double step_rotate = 1;
    if(currentWork->getOnlyPrimitiveList()->size()>0)
    {
        QList<int> *only_prim = currentWork->getOnlyPrimitiveList();

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

// TEMP

void GLWidget::initializeLighting()
{

}
