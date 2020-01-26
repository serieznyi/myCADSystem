#ifndef MYCADSYSTEM_SRC_GUI_CONTEXT_MENU_H_
#define MYCADSYSTEM_SRC_GUI_CONTEXT_MENU_H_

#include <QMenu>
#include <QAction>
#include "src/constants.h"

class GLWidget;

class ContextMenu : public QMenu {
 public:
  ContextMenu(int type, QWidget *parent);
  void CreatePrimitiveContextMenu();
  void CreateSceneContextMenu();
 public:
  GLWidget *p_glw_;
  QAction *primitive_delete_action_;
  QAction *primitive_properties_action_;

};

#endif //MYCADSYSTEM_SRC_GUI_CONTEXT_MENU_H_
