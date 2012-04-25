#include "toolbars/toolbar.h"

ToolBar::ToolBar(QWidget *parent):QToolBar(parent)
{
    //pMW = dynamic_cast<MainWindow*>(parent);
}


void ToolBar::changeEvent(int i)
{
    //pMW->setCurEvent(i);
}
