#include "gui/mtreewidget.h"
#include "gui/mtreewidgetitem.h"
#include "core/mgallery.h"
#include "core/mphoto.h"

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
 * highlights a line in the tree
 * @param apply used to display or hide the background color
 */
void gui::MTreeWidgetItem::highlight(bool apply)
{
    if (apply)
	setBackground(0, QBrush(QColor(Qt::yellow)));
    else
	setBackground(0, QBrush(QColor(Qt::white)));
}

/**
 * returns a currently selected QTreeWidgetItem, casts it to an MTreeWidgetItem
 * @return MTreeWidget item
 */
gui::MTreeWidgetItem* gui::MTreeWidget::selected()
{
    return static_cast<gui::MTreeWidgetItem*>(currentItem());
}
