#include "mtreewidget.h"

#include <iostream>

gui::MTreeWidget::MTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
}

/**
 * inserts an item into Tree Widget
 * @param gallery gallery we are inserting, needed to create widget data
 * @param parent parent widget to which we are adding, default NULL
 */
void gui::MTreeWidget::insert(core::MGallery* gallery, gui::MTreeWidgetItem* parent)
{
    // creates a new widget item based on gallery data
    gui::MTreeWidgetItem* item = new gui::MTreeWidgetItem(gallery);
    parent ? parent->addChild(item) : insertTopLevelItem(0, item);

    sortItems(0, Qt::AscendingOrder); // sort in alphabetical order
}

void gui::MTreeWidget::insert(core::MPhoto* photo, gui::MTreeWidgetItem* parent)
{
    gui::MTreeWidgetItem* item = new gui::MTreeWidgetItem(photo);

    parent->addChild(item); // photos must always have a parent gallery

    sortItems(0, Qt::AscendingOrder); // sort in alphabetical order
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
