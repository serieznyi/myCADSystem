#include "mainwindow.h"

MainWindow::MainWindow(int max_width, int max_height, QWidget *parent): QMainWindow(parent)
{
    //инициализация переменных
    cur_event                   = MEV_CAMERA_TRANSLATE;
    selected_prim = -1;
    WORK_CREATED                = false;
    prev_event                  = 0;
    currentWork                 = new Work(this);
    menuBar                     = new MenuBar(this);
    actionPrimitiveToolbar      = new ActionPrimitiveToolBar(this);
    selectPrimitiveToolbar      = new SelectPrimitiveToolbar(this);
    sceneControlPanel           = new SceneControlPanel(this);
    paintingZone                = new PaintingZone(this);
    listPrimitiveToolBar        = new ListPrimitiveToolbar(this);
    statusBar                   = new StatusBar();

    this->setMenuBar(menuBar);
    this->addToolBar(actionPrimitiveToolbar);
    this->addToolBar(selectPrimitiveToolbar);
    this->addToolBar(sceneControlPanel);
    this->addToolBar(Qt::RightToolBarArea, listPrimitiveToolBar);
    this->setCentralWidget(paintingZone);
    this->setStatusBar(statusBar);

    //настройки окна
    this->resize(900, 700);
    //this->setFixedSize(max_width, max_height);
    this->setWindowState(Qt::WindowMaximized);
    //this->move(10, 10);
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

PaintingZone* MainWindow::getPaintingZone()
{
    return paintingZone;
}

ListPrimitiveToolbar* MainWindow::getListPrimitiveTollBar()
{
    return listPrimitiveToolBar;
}

StatusBar *MainWindow::getStatusBar()
{
    return statusBar;
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("About Recent Files"),
             tr("The <b>Recent Files</b> example demonstrates how to provide a "
                "recently used file menu in a Qt application."));
}
