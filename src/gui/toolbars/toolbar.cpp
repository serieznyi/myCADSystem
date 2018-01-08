#include "toolbar.h"
#include "src/gui/mainwindow.h"

ToolBar::ToolBar(QWidget *parent):QToolBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);
}


void ToolBar::changeEvent(int i)
{
    pMW->setCurEvent(i);
}
