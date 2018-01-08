#include "ToolBar.h"
#include "src/gui/MainWindow.h"

ToolBar::ToolBar(QWidget *parent):QToolBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);
}


void ToolBar::changeEvent(int i)
{
    pMW->setCurEvent(i);
}
