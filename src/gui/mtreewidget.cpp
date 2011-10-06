#include "mtreewidget.h"

gui::MTreeWidget::MTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
}

void gui::MTreeWidget::insert(core::MObject* obj)
{
    gui::MTreeWidgetItem* item = new gui::MTreeWidgetItem(obj);
	item->setText(0, QString(obj->name().c_str()));

    insertTopLevelItem(0, dynamic_cast<QTreeWidgetItem*>(item));
}

void gui::MTreeWidget::remove()
{
    takeTopLevelItem(indexOfTopLevelItem(currentItem()));

    delete currentItem();
}
