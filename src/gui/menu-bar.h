// Меню-бар
#ifndef MYCADSYSTEM_SRC_GUI_MENU_BAR_H_
#define MYCADSYSTEM_SRC_GUI_MENU_BAR_H_

#include <QMenu>
#include <QMenuBar>

class MainWindow;

class MenuBar : public QMenuBar {
 Q_OBJECT

 public:
  explicit MenuBar(QWidget *parent = 0);
  void CreateActions();
 public:
  MainWindow *p_mw_;
  QMenu *file_menu_;
  QAction *file_open_action_;
  QAction *file_save_action_;
  QAction *file_save_to_action_;
  QAction *exit_action_;
  QMenu *scene_action_menu_;
  QAction *action_translate_camera_;
  QAction *action_rotate_camera_;
  QAction *action_zoom_camera_;
  QMenu *primitive_menu_;
  QAction *action_cube_;
  QAction *action_pyramid_;
  QAction *action_sphere_;
  QMenu *primitive_action_menu_;
  QAction *action_translate_;
  QAction *action_rotate_;
  QAction *action_group_;
  QMenu *help_menu_;
  QAction *action_about_;

 private:
  void ChoosePrimitiveEvent(int i);
  void ChoosePrimitiveActionEvent(int i);

 public slots:
  void ChoosePrimitiveSphereAction();
  void ChoosePrimitivePyramidAction();
  void ChoosePrimitiveCubeAction();
  void ChoosePrimitiveTranslateAction();
  void ChoosePrimitiveRotateAction();
  void ChoosePrimitiveGroupAction();
  void ChooseCameraTranslateAction();
  void ChooseCameraRotAction();
  void ChooseCameraZoomAction();
};

#endif //MYCADSYSTEM_SRC_GUI_MENU_BAR_H_
