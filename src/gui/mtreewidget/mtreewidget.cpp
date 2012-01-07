

#include "gui/mtreewidget/mtreewidget.h"
#include "gui/mtreewidget/mtreewidgetitem.h"
#include "core/mgallery.h"

namespace mgui
{

MTreeWidget::MTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
}

void MTreeWidget::loadGallery(mcore::MGallery* gallery, MTreeWidgetItem* parent, int depth)
{
    std::set<mcore::MObject*>::iterator it;
    std::set<mcore::MObject*> content = gallery->content();

    MTreeWidgetItem* item;
    mcore::MGallery* tmpGal;   
    for (it = content.begin(); it != content.end(); ++it)
    {
	switch ((*it)->typeId())
	{
	    case TYPEID_GALLERY:
		tmpGal = (*it)->toGallery();
		item = insert(tmpGal, parent);
		loadGallery(tmpGal, item, depth+1);
		break;
	    case TYPEID_PHOTO:
		insert((*it)->toPhoto(), parent);
		break;
	}
    }
}

/**
 * inserts a gallery into Tree Widget
 * \param gallery gallery we are inserting, needed to create widget data
 * \param parent parent widget to which we are adding, default NULL
 */
MTreeWidgetItem* MTreeWidget::insert(mcore::MGallery* gallery, MTreeWidgetItem* parent)
{
    // creates a new widget item based on gallery data
    MTreeWidgetItem* item = new MTreeWidgetItem(this, gallery);
    parent ? parent->addChild(item) : insertTopLevelItem(0, item);

    sortItems(0, Qt::AscendingOrder); // sort in alphabetical order

    return item;
}

/**
 * inserts a photo into Tree Widget
 * cannot be templated because photos behave a little different from galleries
 * \param photo photo we are inserting, needed to create widget data
 * \param parent parent widget to which we are adding, default NULL
 */
MTreeWidgetItem* MTreeWidget::insert(mcore::MPhoto* photo, MTreeWidgetItem* parent)
{
    MTreeWidgetItem* item = new MTreeWidgetItem(this, photo);

    parent->addChild(item); // photos must always have a parent gallery

    sortItems(0, Qt::AscendingOrder); // sort in alphabetical order

    return item;
}

/**
 * removes and deletes an item from MTreeWidget
 * shouldn't be used on its own, only called from destroy() by a core object
 * \param item from a list which we want to remove
 * \return object linked to an item being removed
 */
void MTreeWidget::remove(MTreeWidgetItem* item)
{
    // no item given to remove, we take selected
    // atm this shouldn't happen, because we always call this with a param
    if (!item)
	item = selected();

    // no item selected
    if (!item)
	return;

    // remove from widget
    takeTopLevelItem(indexOfTopLevelItem(item));
}

} // NAMESPACE GUI
