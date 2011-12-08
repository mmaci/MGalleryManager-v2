#define _DEBUG

#include "gui/mgridwidget/mgridwidget.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/mgridwidgetviewer.h"
#include "gui/mgridwidget/MGridWidgetThumbnail.h"

namespace gui
{

MGridWidget::MGridWidget(QWidget* parent) :
    QWidget(parent)
{
    // widget layout
    _layout = new QGridLayout(this);
	_layout->setSpacing(6);
	_layout->setContentsMargins(0, 0, 0, 0);	
	_layout->setSizeConstraint(QLayout::SetFixedSize);

    _viewer = NULL;

    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridWidget" << std::endl;
    #endif
}

MGridWidget::~MGridWidget()
{
    std::list<MGridWidgetItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
	delete *it;

    delete _layout;

    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridWidgetItem" << std::endl;
    #endif
}

MGridWidgetThumbnail* MGridWidget::insert(core::MPhoto* photo)
{
    int pos_x = count() % GRID_WIDTH;
    int pos_y = count() / GRID_WIDTH;

    // we create a grid item and add it to our layout
    MGridWidgetThumbnail* item = new MGridWidgetThumbnail(this, photo);
	_layout->addWidget(item, pos_y, pos_x, Qt::AlignLeft|Qt::AlignTop);
	_items.push_back(item);

    item->show();    
    return item;
}

void MGridWidget::load(core::MObject* object)
{
    hideAllItems();

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
	    if ((*it)->typeId() == TYPEID_PHOTO && (*it)->gridThumbnail()) // check for gridItem isn't needed here atm, but might be in the future
	    {
		_layout->addWidget((*it)->gridThumbnail(), pos_y, pos_x, Qt::AlignLeft|Qt::AlignTop);
		(*it)->gridThumbnail()->show();
		cnt++;
	    }
	}
    }
    else
    if (object->typeId() == TYPEID_PHOTO)
    {
	core::MPhoto* photo = object->toPhoto();
	// usually every viewer is deleted the moment it's not used, not to use up lots of memory
	// so every time we want to show a new viewer, we have to generate it
	// in the future this might change to cache some viewers so we better check if it isn't already created
	if (!photo->gridViewer())
	    photo->setGridViewer(generateGridViewer(photo));

	_viewer = photo->gridViewer();
	_layout->addWidget(photo->gridViewer(), 0, 0);
	photo->gridViewer()->show();
    }
}

MGridWidgetViewer* MGridWidget::generateGridViewer(core::MPhoto* photo, int maxSize)
{
    QPixmap pixmap = photo->pixmapFromFile(maxSize);

    MGridWidgetViewer* viewer = new MGridWidgetViewer(pixmap, this, photo);

    return viewer;
}

void MGridWidget::hideAllItems()
{
    std::list<MGridWidgetItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
    {
	_layout->removeWidget(*it);
	(*it)->hide();
    }    

    if (_viewer)
    {
	_layout->removeWidget(_viewer);
	_viewer->hide();
	_viewer = NULL;
    }
}

MGridWidgetItem* MGridWidget::find(core::MObject* obj)
{
    std::list<MGridWidgetItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
    {
	if ((*it)->object() == obj)
	    return *it;
    }
    return NULL;
}

core::MObject* MGridWidget::remove(MGridWidgetItem* item)
{
    item->hide();
    _items.remove(item);
    delete item;
    return item->object();
}

core::MObject* MGridWidget::remove(core::MObject* obj)
{
    if (MGridWidgetItem* item = find(obj))
	return remove(item);

    return NULL;
}

} // NAMESPACE GUI
