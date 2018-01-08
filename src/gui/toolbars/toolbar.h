#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>

class MainWindow;

class ToolBar : public QToolBar
{
public:
    explicit ToolBar(QWidget *parent);
    void changeEvent(int i);

private:
    MainWindow *pMW;
    ToolBar();
};

#endif // TOOLBAR_H
