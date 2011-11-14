#define _DEBUG

#include "gui/mgridwidget.h"
#include "gui/mgridwidgetitem.h"


gui::MGridWidget::MGridWidget(QWidget* parent) :
    QWidget(parent)
{
    // widget layout
    _layout = new QGridLayout(this);
	_layout->setSpacing(6);
	_layout->setContentsMargins(0, 0, 0, 0);	
	_layout->setSizeConstraint(QLayout::SetFixedSize);

    _displayPhoto = NULL;

    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridWidget" << std::endl;
    #endif
}

gui::MGridWidget::~MGridWidget()
{
    std::list<gui::MGridWidgetItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
	delete *it;

    delete _layout;

    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridWidgetItem" << std::endl;
    #endif
}

gui::MGridWidgetItem* gui::MGridWidget::insert(core::MPhoto* photo)
{
    int pos_x = count() % GRID_WIDTH;
    int pos_y = count() / GRID_WIDTH;

    // we create a grid item and add it to our layout
    gui::MGridWidgetItem* item = new gui::MGridWidgetItem(this, photo);
	_layout->addWidget(item, pos_y, pos_x, Qt::AlignLeft|Qt::AlignTop);
	_items.push_back(item);

    item->show();    
    return item;
}

void gui::MGridWidget::load(core::MObject* object)
{
    hideAllItems();
    if (_displayPhoto)
    {
	_layout->removeWidget(_displayPhoto);
	_displayPhoto->hide();
	delete _displayPhoto;
	_displayPhoto = NULL;
    }

    if (object->typeId() == TYPEID_GALLERY)
    {
	// displays gallery content
	    core::MGallery* gallery = object->toGallery();
	    std::set<core::MObject*> galleryContent = gallery->content();
	    std::set<core::MObject*>::iterator it;

	    int pos_x, pos_y, cnt = 0;
	    for (it = galleryContent.begin(); it != galleryContent.end(); ++it)
	    {		
		pos_x = cnt % GRID_WIDTH;
		pos_y = cnt / GRID_WIDTH;
		if ((*it)->typeId() == TYPEID_PHOTO && (*it)->gridItem()) // check for gridItem isn't needed here atm, but might be in the future
		{		    		    		    
		    _layout->addWidget((*it)->gridItem(), pos_y, pos_x, Qt::AlignLeft|Qt::AlignTop);
		    (*it)->gridItem()->show();		    
		    cnt++;
		}
	    }
    }
    else
    if (object->typeId() == TYPEID_PHOTO)
    {
	// hacky way of implementing a photo display
	// we should implement this by subclassing MGridWidgetItem to MGridWidgetThumbnail and MGridWidgetDisplay
	core::MPhoto* photo = object->toPhoto();
	_displayPhoto = new QLabel(this);
	    _displayPhoto->setPixmap(photo->generateImage(500));
	    _layout->addWidget(_displayPhoto);
	    _displayPhoto->show();
    }
}

void gui::MGridWidget::hideAllItems()
{
    std::list<gui::MGridWidgetItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
    {
	_layout->removeWidget(*it);
	(*it)->hide();
    }    
}

gui::MGridWidgetItem* gui::MGridWidget::find(core::MObject* obj)
{
    std::list<gui::MGridWidgetItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
    {
	if ((*it)->object() == obj)
	    return *it;
    }
    return NULL;
}

core::MObject* gui::MGridWidget::remove(gui::MGridWidgetItem* item)
{
    item->hide();
    _items.remove(item);
    delete item;
    return item->object();
}

core::MObject* gui::MGridWidget::remove(core::MObject* obj)
{
    if (gui::MGridWidgetItem* item = find(obj))
	return remove(item);

    return NULL;
}
