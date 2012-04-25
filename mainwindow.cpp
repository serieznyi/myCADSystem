#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    //инициализация переменных
    cur_event                   = MEV_CAMERA_TRANSLATE;
    prev_event                  = 0;
    currentWork                 = new Work();
    menuBar                     = new MenuBar();
    actionPrimitiveToolbar      = new ActionPrimitiveToolBar(this);
    selectPrimitiveToolbar      = new SelectPrimitiveToolbar(this);
    sceneControlPanel           = new SceneControlPanel(this);
    paintingZone                = new PaintingZone(this);
    //listPrimitiveTollBar        = new ListPrimitiveToolbar(this);
    statusBar                   = new StatusBar();

    this->setMenuBar(menuBar);
    this->addToolBar(actionPrimitiveToolbar);
    this->addToolBar(selectPrimitiveToolbar);
    this->addToolBar(sceneControlPanel);
    //this->addToolBar(listPrimitiveTollBar);
    this->setCentralWidget(paintingZone);
    this->setStatusBar(statusBar);

    //настройки окна
    this->resize(900, 700);
    this->setWindowState(Qt::WindowMaximized);
    this->move(10, 10);
    this->setMinimumSize(700, 500);
    this->setWindowTitle(QString::fromLocal8Bit("MyCADSystem v1"));
    this->show();
}

int *MainWindow::getCurEvent()
{
    return &cur_event;
}

void MainWindow::setCurEvent(int a)
{
    cur_event = a;
}

int* MainWindow::getPrevEvent()
{
    return &prev_event;
}

void MainWindow::setPrevEvent(int a)
{
    prev_event = a;
}

Work* MainWindow::getWork()
{
    return currentWork;
}

void MainWindow::Update()
{
    paintingZone->widFront->repaint();
    paintingZone->widTop->repaint();
    paintingZone->widRight->repaint();
    paintingZone->widPerspective->repaint();
}

/*
ListPrimitiveToolbar *MainWindow::getListPrimTB()
{
    return listPrimitiveTollBar;
}
*/
