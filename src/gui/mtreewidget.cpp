#define _DEBUG

#include "gui/mtreewidget.h"
#include "core/mgallery.h"

// ================ MTreeWidgetItem ================

/**
 * constructor
 * casts to an MObject and creates proper widget details
 */
gui::MTreeWidgetItem::MTreeWidgetItem(gui::MTreeWidget* widget, core::MGallery* gallery)
{
    _widget = widget;
    _obj = gallery->toObject();

    // widget details
    setText(0, QString(gallery->info().name().c_str()));

    #ifdef _DEBUG
    std::cout << "Creating new instance of MTreeWidgetItem (" << gallery->info().name().c_str() << ")" << std::endl;
    #endif
}

/**
 * constructor
 * casts to an MObject and creates proper widget details
 * Photos have different detail structure than Galleries, therefore we can't template these
 */
gui::MTreeWidgetItem::MTreeWidgetItem(gui::MTreeWidget* widget, core::MPhoto* photo)
{
    _widget = widget;
    _obj = photo->toObject();

    // widget details
    setText(0, QString(photo->info().fileInfo().baseName()));

    #ifdef _DEBUG
    std::cout << "Creating new instance of MTreeWidgetItem (" << photo->info().fileInfo().baseName().toStdString() << ")" << std::endl;
    #endif
}

/**
 * destructor
 */
gui::MTreeWidgetItem::~MTreeWidgetItem()
{ 
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MTreeWidgetItem" << std::endl;
    #endif
}

/**
 * returns a currently selected QTreeWidgetItem, casts it to an MTreeWidgetItem
 * @return MTreeWidget item
 */
gui::MTreeWidgetItem* gui::MTreeWidget::selected()
{
    return static_cast<gui::MTreeWidgetItem*>(currentItem());
}

// ================ MTreeWidget ================

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
 * removes item based on param, if none given, removes currently selected item
 * also deletes all proper core structures
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


