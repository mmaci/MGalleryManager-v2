#define _DEBUG

#include "gui/mtreewidget.h"
#include "gui/mtreewidgetitem.h"
#include "core/mgallery.h"

gui::MTreeWidget::MTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    #ifdef _DEBUG
    std::cout << "Creating new instance of MTreeWidget" << std::endl;
    #endif
}

/**
 * inserts a gallery into Tree Widget
 * @param gallery gallery we are inserting, needed to create widget data
 * @param parent parent widget to which we are adding, default NULL
 */
gui::MTreeWidgetItem* gui::MTreeWidget::insert(core::MGallery* gallery, gui::MTreeWidgetItem* parent)
{
    // creates a new widget item based on gallery data
    gui::MTreeWidgetItem* item = new gui::MTreeWidgetItem(this, gallery);
    parent ? parent->addChild(item) : insertTopLevelItem(0, item);

    sortItems(0, Qt::AscendingOrder); // sort in alphabetical order

    return item;
}

/**
 * inserts a photo into Tree Widget
 * cannot be templated because photos behave a little different from galleries
 * @param photo photo we are inserting, needed to create widget data
 * @param parent parent widget to which we are adding, default NULL
 */
gui::MTreeWidgetItem* gui::MTreeWidget::insert(core::MPhoto* photo, gui::MTreeWidgetItem* parent)
{
    gui::MTreeWidgetItem* item = new gui::MTreeWidgetItem(this, photo);

    parent->addChild(item); // photos must always have a parent gallery

    sortItems(0, Qt::AscendingOrder); // sort in alphabetical order

    return item;
}

/**
 * removes and deletes an item from MTreeWidget
 * shouldn't be used on its own, only called from destroy() by a core object
 * @param item from a list which we want to remove
 * @return object linked to an item being removed
 */
core::MObject* gui::MTreeWidget::remove(gui::MTreeWidgetItem* item)
{
    // no item given to remove, we take selected
    // atm this shouldn't happen, because we always call this with a param
    if (!item)
	item = selected();

    // no item selected
    if (!item)
	return NULL;

    core::MObject* obj = item->object();

    // remove from widget
    takeTopLevelItem(indexOfTopLevelItem(item));
    delete item;

    return obj;
}


