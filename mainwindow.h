// Главное окно программы

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "paintingzone.h"
#include "menubar.h"
#include "toolbars/action_primitive_toolbar.h"
#include "toolbars/select_primitive_toolbar.h"
#include "toolbars/scene_control_toolbar.h"
#include "toolbars/list_primitive_toolbar.h"
#include "statusbar.h"
#include "work.h"
#include "resource.h"

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(int max_width, int max_height, QWidget *parent = 0);                   // Конструктор
    int* getCurEvent();
    void setCurEvent(int event);
    int *getPrevEvent();
    void setPrevEvent(int event);
    Work* getWork();
    void Update();
    PaintingZone *getPaintingZone();
    ListPrimitiveToolbar *getListPrimitiveTollBar();
    StatusBar* getStatusBar();
private:
    PaintingZone                    *paintingZone;              // Виджет проекций вида
    MenuBar                         *menuBar;
    ActionPrimitiveToolBar          *actionPrimitiveToolbar;    // Панель управления примитивами
    SelectPrimitiveToolbar          *selectPrimitiveToolbar;    // Панель выбора примитивов
    ListPrimitiveToolbar            *listPrimitiveToolBar;      // Панель примитивов сцены
    SceneControlPanel               *sceneControlPanel;         // Панель управления сценой
    StatusBar                       *statusBar;                 // Панель вывода доп. информации
    int                             cur_event;                  // Текущее событие
    int                             prev_event;                 // Предыдущее событие
    Work                            *currentWork;               // Текущая работа
    bool                             WORK_CREATED;
public:
    long selected_prim;
public slots:
    void showAbout();

};

#endif // MAINWINDOW_H
