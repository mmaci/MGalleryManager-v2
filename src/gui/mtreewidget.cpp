#include "mtreewidget.h"

// ================ MTreeWidgetItem ================

/**
 * constructor
 * casts to an MObject and creates proper widget details
 */
gui::MTreeWidgetItem::MTreeWidgetItem(core::MGallery* gallery)
{
    _obj = gallery->toObject();

    // widget details
    setText(0, QString(gallery->info().name().c_str()));
}

/**
 * constructor
 * casts to an MObject and creates proper widget details
 * Photos have different detail structure than Galleries, therefore we can't template these
 */
gui::MTreeWidgetItem::MTreeWidgetItem(core::MPhoto* photo)
{
    _obj = photo->toObject();

    // widget details
    setText(0, QString(photo->info().fileInfo().baseName()));
}

/**
 * destructor
 */
gui::MTreeWidgetItem::~MTreeWidgetItem()
{ 
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
}

/**
 * inserts a gallery into Tree Widget
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

/**
 * inserts a photo into Tree Widget
 * cannot be templated because photos behave a little different from galleries
 * @param photo photo we are inserting, needed to create widget data
 * @param parent parent widget to which we are adding, default NULL
 */
void gui::MTreeWidget::insert(core::MPhoto* photo, gui::MTreeWidgetItem* parent)
{
    gui::MTreeWidgetItem* item = new gui::MTreeWidgetItem(photo);

    parent->addChild(item); // photos must always have a parent gallery

    sortItems(0, Qt::AscendingOrder); // sort in alphabetical order
}

/**
 * removes currently selected item from the widget
 * also deletes all proper core structures
 */
core::MObject* gui::MTreeWidget::remove()
{
    gui::MTreeWidgetItem* item = selected();
    core::MObject* obj = item->object();

    // remove from widget
    takeTopLevelItem(indexOfTopLevelItem(item));
    delete item;

    return obj;
}


