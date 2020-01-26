// Панель проекций вида

#ifndef MYCADSYSTEM_SRC_GUI_PAINTING_ZONE_H_
#define MYCADSYSTEM_SRC_GUI_PAINTING_ZONE_H_

#include <QSplitter>
#include "src/gl-widget.h"
#include "src/constants.h"

class PaintingZone : public QWidget {
 public:
  explicit PaintingZone(QWidget *parent = nullptr);
  void Update();
  // TODO split on showAllView / hideAllView
  void SetAllUnvisible(bool a);
  void SaveProjectionLastState();
  void LoadProjectionLastState();

 public:
  QSplitter *sp_global_;
  QSplitter *sp_top_;
  QSplitter *sp_down_;
  GLWidget *wid_perspective_;           // Перспективная проекция
  GLWidget *wid_top_;                   // YOX
  GLWidget *wid_front_;                 // ZOX
  GLWidget *wid_right_;                 // XOY
  QVBoxLayout *lay_global_;               // Глобальный менеджер компоновки
 public slots:
  void SetMaximum(int i);
};

#endif //MYCADSYSTEM_SRC_GUI_PAINTING_ZONE_H_
