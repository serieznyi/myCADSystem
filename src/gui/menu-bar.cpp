#include "menu-bar.h"
#include "src/gui/main-window.h"

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent) {
  p_mw_ = dynamic_cast<MainWindow *>(parent);

  file_menu_ = new QMenu("Файл");
  this->addMenu(file_menu_);

  scene_action_menu_ = new QMenu("Сцена");
  this->addMenu(scene_action_menu_);

  primitive_menu_ = new QMenu("Примитивы");
  this->addMenu(primitive_menu_);

  primitive_action_menu_ = new QMenu("Действия над примитивами");
  this->addMenu(primitive_action_menu_);

  help_menu_ = new QMenu("Помощь");
  this->addMenu(help_menu_);

  CreateActions();
}

void MenuBar::CreateActions() {

  // File
  file_open_action_ = new QAction("Открыть", this);
  file_menu_->addAction(file_open_action_);

  file_menu_->addSeparator();

  file_save_action_ = new QAction("Сохранить", this);
  file_menu_->addAction(file_save_action_);

  file_save_to_action_ = new QAction("Сохранить как...", this);
  file_menu_->addAction(file_save_to_action_);
  connect(file_save_to_action_, SIGNAL(triggered()), p_mw_, SLOT(saveTo()));

  file_menu_->addSeparator();

  exit_action_ = new QAction("Выход", this);
  file_menu_->addAction(exit_action_);
  connect(exit_action_, SIGNAL(triggered()), p_mw_, SLOT(close()));

  // About
  action_about_ = new QAction("О программе", this);
  help_menu_->addAction(action_about_);

  // Camera actions
  action_translate_camera_ = new QAction("Переместить камеру", this);
  scene_action_menu_->addAction(action_translate_camera_);
  connect(action_translate_camera_, SIGNAL(triggered()), SLOT(ChooseCameraTranslateAction()));

  action_rotate_camera_ = new QAction("Повернуть камеру", this);
  scene_action_menu_->addAction(action_rotate_camera_);
  connect(action_rotate_camera_, SIGNAL(triggered()), SLOT(ChooseCameraRotAction()));

  action_zoom_camera_ = new QAction("Изменить масштаб", this);
  scene_action_menu_->addAction(action_zoom_camera_);
  connect(action_zoom_camera_, SIGNAL(triggered()), SLOT(ChooseCameraZoomAction()));

  // Primitives
  action_cube_ = new QAction("Куб", this);
  primitive_menu_->addAction(action_cube_);
  connect(action_cube_, SIGNAL(triggered()), SLOT(ChoosePrimitiveCubeAction()));

  action_sphere_ = new QAction("Сфера", this);
  primitive_menu_->addAction(action_sphere_);
  connect(action_sphere_, SIGNAL(triggered()), SLOT(ChoosePrimitiveSphereAction()));

  action_pyramid_ = new QAction("Пирамида", this);
  primitive_menu_->addAction(action_pyramid_);
  connect(action_pyramid_, SIGNAL(triggered()), SLOT(ChoosePrimitivePyramidAction()));

  // Primitive actions
  action_translate_ = new QAction("Переместить", this);
  primitive_action_menu_->addAction(action_translate_);
  connect(action_translate_, SIGNAL(triggered()), SLOT(ChoosePrimitiveTranslateAction()));

  action_rotate_ = new QAction("Повернуть", this);
  primitive_action_menu_->addAction(action_rotate_);
  connect(action_rotate_, SIGNAL(triggered()), SLOT(ChoosePrimitiveRotateAction()));

  action_group_ = new QAction("Сгрупировать", this);
  primitive_action_menu_->addAction(action_group_);
  connect(action_group_, SIGNAL(triggered()), SLOT(ChoosePrimitiveGroupAction()));

}

void MenuBar::ChoosePrimitiveCubeAction() {

  ChoosePrimitiveEvent(MEL_CUBE);
}

void MenuBar::ChoosePrimitivePyramidAction() {
  ChoosePrimitiveEvent(MEL_PYRAMID);
}

void MenuBar::ChoosePrimitiveSphereAction() {
  ChoosePrimitiveEvent(MEL_SPHERE);
}

void MenuBar::ChoosePrimitiveEvent(int i) {
  p_mw_->SetPrevEvent(*(p_mw_->GetCurEvent()));
  p_mw_->SetCurEvent(i);
}

void MenuBar::ChoosePrimitiveTranslateAction() {
  ChoosePrimitiveActionEvent(ACTION_TRANSLATE);
}

void MenuBar::ChoosePrimitiveRotateAction() {
  ChoosePrimitiveActionEvent(ACTION_ROTATE);
}

void MenuBar::ChoosePrimitiveGroupAction() {
  ChoosePrimitiveActionEvent(ACTION_GROUP);
}

void MenuBar::ChoosePrimitiveActionEvent(int i) {
  p_mw_->SetCurEvent(i);
}

void MenuBar::ChooseCameraTranslateAction() {
  p_mw_->SetCurEvent(CAMERA_TRANSLATE);
}

void MenuBar::ChooseCameraRotAction() {
  p_mw_->SetCurEvent(CAMERA_ROTATE);
}

void MenuBar::ChooseCameraZoomAction() {
  p_mw_->SetCurEvent(CAMERA_ZOOM);
}