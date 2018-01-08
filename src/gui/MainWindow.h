// Главное окно программы

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PaintingZone.h"
#include "MenuBar.h"
#include "src/gui/toolbars/ActionPrimitiveToolBar.h"
#include "src/gui/toolbars/SelectPrimitiveToolbar.h"
#include "src/gui/toolbars/SceneControlToolbar.h"
#include "src/gui/toolbars/ListPrimitiveToolbar.h"
#include "StatusBar.h"
#include "src/Work.h"
#include "src/resource.h"
#include <QFileDialog>

class ActionPrimitiveToolBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(int max_width, int max_height, QWidget *parent = 0);                   // Конструктор
    int* getCurEvent();
    void setCurEvent(int event);
    int *getPrevEvent();
    void setPrevEvent(int event);
    Work* getWork();
    void Update();
    PaintingZone *getPaintingZone();
    SelectPrimitiveToolbar *getSelectPrimitiveToolbar();
    ActionPrimitiveToolBar* getActionPrimitiveToolbar();
    SceneControlToolbar* getSceneControlToolbar();

    StatusBar* getStatusBar();

private:
    PaintingZone                    *paintingZone;              // Виджет проекций вида
    MenuBar                         *menuBar;
    ActionPrimitiveToolBar          *actionPrimitiveToolbar;    // Панель управления примитивами
    SelectPrimitiveToolbar          *selectPrimitiveToolbar;    // Панель выбора примитивов
    ListPrimitiveToolbar            *listPrimitiveToolBar;      // Панель примитивов сцены
    SceneControlToolbar               *sceneControlPanel;         // Панель управления сценой
    StatusBar                       *statusBar;                 // Панель вывода доп. информации
    int                             cur_event;                  // Текущее событие
    int                             prev_event;                 // Предыдущее событие
    Work                            *currentWork;               // Текущая работа
    bool                             WORK_CREATED;
public:
    long selected_prim;
    QString savedPath;

public slots:
    void showAbout();
    void saveTo();
    void save();
    void open();

};

QDataStream& operator<<(QDataStream &out, const QList<Container*> *);

#endif // MAINWINDOW_H
