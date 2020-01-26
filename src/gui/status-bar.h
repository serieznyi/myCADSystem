#ifndef MYCADSYSTEM_SRC_GUI_STATUS_BAR_H_
#define MYCADSYSTEM_SRC_GUI_STATUS_BAR_H_

#include <QStatusBar>

class StatusBar : public QStatusBar {
 Q_OBJECT
 public:
  explicit StatusBar(QWidget *parent = nullptr);
};
#endif //MYCADSYSTEM_SRC_GUI_STATUS_BAR_H_
