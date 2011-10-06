#include "mtreewidget.h"

#include <iostream>

gui::MTreeWidget::MTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
}

void gui::MTreeWidget::insert(core::MObject* obj)
{
    gui::MTreeWidgetItem* item = new gui::MTreeWidgetItem(obj);	

    if (currentItem())
	insertTopLevelItem(indexOfTopLevelItem(currentItem()), dynamic_cast<QTreeWidgetItem*>(item));
    else
	insertTopLevelItem(0, dynamic_cast<QTreeWidgetItem*>(item));
}

void gui::MTreeWidget::remove()
{
    gui::MTreeWidgetItem* item = static_cast<gui::MTreeWidgetItem*>(currentItem());

    takeTopLevelItem(indexOfTopLevelItem(currentItem()));    

    delete item;
}

gui::MTreeWidgetItem::MTreeWidgetItem(core::MObject* obj)
{
    _obj = obj;
    setText(0, QString(obj->name().c_str()));
}
