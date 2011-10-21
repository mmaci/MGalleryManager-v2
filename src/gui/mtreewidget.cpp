#include "mtreewidget.h"

#include <iostream>

gui::MTreeWidget::MTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
}

void gui::MTreeWidget::insert(core::MGallery* gallery)
{
    gui::MTreeWidgetItem* item = new gui::MTreeWidgetItem(gallery);

    if (currentItem())
	insertTopLevelItem(indexOfTopLevelItem(currentItem()), item->toQWidgetItem());
    else
	insertTopLevelItem(0, item->toQWidgetItem());
}

void gui::MTreeWidget::insert(core::MPhoto* photo)
{
    gui::MTreeWidgetItem* item = new gui::MTreeWidgetItem(photo);

    if (currentItem())
	insertTopLevelItem(indexOfTopLevelItem(currentItem()), item->toQWidgetItem());
    else
	insertTopLevelItem(0, item->toQWidgetItem());
}

gui::MTreeWidgetItem* gui::MTreeWidget::selected()
{
    return static_cast<gui::MTreeWidgetItem*>(currentItem());
}

void gui::MTreeWidget::remove()
{
    gui::MTreeWidgetItem* item = static_cast<gui::MTreeWidgetItem*>(currentItem());

    takeTopLevelItem(indexOfTopLevelItem(currentItem()));    

    delete item;
}


gui::MTreeWidgetItem::MTreeWidgetItem(core::MGallery* gallery)
{
    _obj = gallery->toObject();
    setText(0, QString(gallery->info().name().c_str()));
}

gui::MTreeWidgetItem::MTreeWidgetItem(core::MPhoto* photo)
{
    _obj = photo->toObject();
    setText(0, QString(photo->info().fileInfo().baseName()));
}
