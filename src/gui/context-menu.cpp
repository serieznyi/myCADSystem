#include "context-menu.h"
#include "src/gl-widget.h"

ContextMenu::ContextMenu(int type, QWidget *parent) : QMenu(parent) {
  p_glw_ = dynamic_cast<GLWidget *>(parent);
  switch (type) {
    case MCM_SCENE: CreateSceneContextMenu();
      break;
    case MCM_PRIMITIVE: CreatePrimitiveContextMenu();
      break;
  }
}

void ContextMenu::CreatePrimitiveContextMenu() {
  primitive_delete_action_ = new QAction("&Удалить", this);
  connect(primitive_delete_action_, SIGNAL(triggered()), p_glw_, SLOT(deletePrimitive()));
  this->addSeparator();
  this->addAction(primitive_delete_action_);

  primitive_properties_action_ = new QAction("&Свойства", this);
  this->addAction(primitive_properties_action_);
}

void ContextMenu::CreateSceneContextMenu() {

}
