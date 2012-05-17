//”правление сценой

#ifndef GLOBALCONTROLPANEL_H
#define GLOBALCONTROLPANEL_H

#include <QToolBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include "resource.h"

class MainWindow;

class SceneControlToolbar : public QToolBar
{
       Q_OBJECT
public:
    SceneControlToolbar(QWidget *parent);

private:
    void createActions();
    void changeEvent(int i);

private:
    QPushButton             *pb_camera_pos;
    QPushButton             *pb_camera_rot;
    QPushButton             *pb_camera_zoom;
    QHBoxLayout             *lt_global;

    QAction                 *cameraPosAction;
    QAction                 *cameraRotAction;
    QAction                 *cameraZoomAction;

    MainWindow *pMW;

public slots:
    void setCameraTranslateAction();
    void setCameraRotAction();
    void setCameraZoomAction();

};

#endif // GLOBALCONTROLPANEL_H
