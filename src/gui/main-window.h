// Главное окно программы

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "painting-zone.h"
#include "menu-bar.h"
#include "status-bar.h"
#include "src/work.h"
#include "src/constants.h"
#include <QFileDialog>

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

    StatusBar* getStatusBar();

private:
    PaintingZone                    *paintingZone;              // Виджет проекций вида
    MenuBar                         *menuBar;
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
