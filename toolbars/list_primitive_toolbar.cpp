#include "list_primitive_toolbar.h"
#include "mainwindow.h"

ListPrimitiveToolbar::ListPrimitiveToolbar(QWidget *parent) :  QToolBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);
    currentWork          = pMW->getWork();
    lt_global            = new QHBoxLayout();
    lstWidget_primList   = new QListWidget();

    lt_global->addWidget(lstWidget_primList);
    this->setLayout(lt_global);
}

void ListPrimitiveToolbar::delPrimitive(Primitive *a)
{
   // ListWidgetElement *element = new ListWidgetElement();
}


void ListPrimitiveToolbar::UpdateList()
{

}

void ListPrimitiveToolbar::addPrimitive(Primitive *prim)
{
    lstWidget_primList->addItem(new QListWidgetItem(getName(prim)));
}

QString ListPrimitiveToolbar::getName(Primitive *element)
{
    switch(element->getTypeName())
    {
        case MEL_CUBE: return "Куб"; break;
        case MEL_PYRAMID: return "Пирамида"; break;
    }
}

