
#include "gui/mgridwidget/mgridwidget.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/mgridwidgetviewer.h"
#include "gui/mgridwidget/MGridWidgetThumbnail.h"

namespace mgui
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
}

MGridWidget::~MGridWidget()
{
    std::set<MGridWidgetItem*>::iterator it;    
    while (!_items.empty())
    {
	it = _items.begin();
	delete *it;
	_items.erase(it);
    }

    delete _layout;
}

MGridWidgetThumbnail* MGridWidget::insert(mcore::MPhoto* photo, int x, int y)
{

    // we create a grid item and add it to our layout
    MGridWidgetThumbnail* item;
    if (!photo->gridThumbnail())
	item = new MGridWidgetThumbnail(photo, this);
    else
	item = photo->gridThumbnail();

    // when x and y are -1 we place the thumbnail at the end
    if (x == -1)
	x = count() % GRID_WIDTH;
    if (y == -1)
	y = count() / GRID_WIDTH;

    _layout->addWidget(item, y, x, Qt::AlignLeft|Qt::AlignTop);
    _items.insert(item);
    item->show();

    return item;
}

void MGridWidget::load(mcore::MObject* object)
{
    hideAllItems();

    if (object->typeId() == TYPEID_GALLERY)
    {
	// displays gallery content
	mcore::MGallery* gallery = object->toGallery();
	std::vector<mcore::MObject*> galleryContent = gallery->content();
	std::vector<mcore::MObject*>::iterator it;

	int pos_x, pos_y, cnt = 0;	
	for (it = galleryContent.begin(); it != galleryContent.end(); ++it)
	{
	    pos_x = cnt % GRID_WIDTH;
	    pos_y = cnt / GRID_WIDTH;
	    if ((*it)->typeId() == TYPEID_PHOTO) // check for gridItem isn't needed here atm, but might be in the future
		insert((*it)->toPhoto(), pos_x, pos_y);

	    ++cnt;
	}
    }
    else
    if (object->typeId() == TYPEID_PHOTO)
    {
	mcore::MPhoto* photo = object->toPhoto();
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

MGridWidgetViewer* MGridWidget::generateGridViewer(mcore::MPhoto* photo, int maxSize)
{
    QPixmap pixmap = photo->pixmapFromFile(maxSize);

    MGridWidgetViewer* viewer = new MGridWidgetViewer(pixmap, photo, this);

    return viewer;
}

void MGridWidget::hideAllItems()
{
    std::set<MGridWidgetItem*>::iterator it;
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

MGridWidgetItem* MGridWidget::find(mcore::MObject* obj)
{
    std::set<MGridWidgetItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
    {
	if ((*it)->object() == obj)
	    return *it;
    }
    return NULL;
}

bool MGridWidget::remove(MGridWidgetItem* item)
{
    item->hide();
    _items.erase(item);
    _layout->removeWidget(item);

    return true;
}

bool MGridWidget::remove(mcore::MObject* obj)
{
    if (MGridWidgetItem* item = find(obj))    
	return remove(item);

    return false;
}

} // NAMESPACE GUI
