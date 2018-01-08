#include "list_primitive_toolbar.h"
#include "../mainwindow.h"

ListPrimitiveToolbar::ListPrimitiveToolbar(QWidget *parent) :  QToolBar(parent)
{
    pMW = dynamic_cast<MainWindow*>(parent);
    currentWork          = pMW->getWork();
    lt_global            = new QHBoxLayout();
    lstWidget_primList   = new QListWidget();

    lt_global->addWidget(lstWidget_primList);
    lstWidget_primList->clear();
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
    QListWidgetItem *item = new QListWidgetItem(lstWidget_primList);
    item->setText(getName(prim));
    pMW->repaint();
    //lstWidget_primList->addItem(item);
}

QString ListPrimitiveToolbar::getName(Primitive *element)
{
    switch(element->getTypeName())
    {
        case MEL_CUBE: return "Куб";
        case MEL_PYRAMID: return "Пирамида";
        default: return "";
    }
}

