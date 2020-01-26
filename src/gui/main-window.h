// Главное окно программы

#ifndef MYCADSYSTEM_SRC_GUI_MAIN_WINDOW_H_
#define MYCADSYSTEM_SRC_GUI_MAIN_WINDOW_H_

#include <QMainWindow>
#include "painting-zone.h"
#include "menu-bar.h"
#include "status-bar.h"
#include "src/work.h"
#include "src/constants.h"
#include <QFileDialog>

class MainWindow : public QMainWindow {
 Q_OBJECT
 public:
  explicit MainWindow(int max_width, int max_height, QWidget *parent = nullptr);                   // Конструктор
  int *GetCurEvent();
  void SetCurEvent(int event);
  int *GetPrevEvent();
  void SetPrevEvent(int event);
  Work *GetWork();
  void Update();
  PaintingZone *GetPaintingZone();

  StatusBar *GetStatusBar();

 private:
  PaintingZone *painting_zone_;              // Виджет проекций вида
  MenuBar *menu_bar_;
  StatusBar *status_bar_;                 // Панель вывода доп. информации
  int cur_event_;                  // Текущее событие
  int prev_event_;                 // Предыдущее событие
  Work *current_work_;               // Текущая работа
  bool work_created_;
 public:
  long selected_prim_;
  QString saved_path_;

 public slots:
  void ShowAbout();
  void SaveTo();
  void Save();
  void Open();

};

QDataStream &operator<<(QDataStream &out, const QList<Container *> *);

#endif //MYCADSYSTEM_SRC_GUI_MAIN_WINDOW_H_
