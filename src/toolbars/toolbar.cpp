#include "toolbars/toolbar.h"
#include "mainwindow.h"

ToolBar::ToolBar(QWidget *parent):QToolBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);
}


void ToolBar::changeEvent(int i)
{
    pMW->setCurEvent(i);
}
