#define _DEBUG

#include "gui/mgridwidget.h"

gui::MGridItemButton::MGridItemButton(int type, gui::MGridItem* item) :
    QToolButton(item)
{
    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridItemButton" << std::endl;
    #endif

    _type = type;
    _item = item;

    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

gui::MGridItemButton::~MGridItemButton()
{
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridItemButton" << std::endl;
    #endif
}

gui::MGridItemIcons::MGridItemIcons(QWidget* parent) :
    QWidget(parent)
{
    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridItemIcons" << std::endl;
    #endif

    _item = static_cast<gui::MGridItem*>(parent);
    _layout = new QGridLayout(this);

    for (int i = 0; i < MAX_BUTTONS; ++i)
    {
	_button[i] = new gui::MGridItemButton(i, _item);
	switch (i)
	{
	    case BUTTON_DELETE:
		_button[i]->setIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/images/but_delete.png")));
		break;
	    case BUTTON_FAV:
		_button[i]->setIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/images/but_fav.png")));
		break;
	    case BUTTON_SELECT:
		_button[i]->setIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/images/but_select.png")));
		break;
	    case BUTTON_EDIT:
		_button[i]->setIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/images/but_edit.png")));
		break;
	}
	_layout->addWidget(_button[i], 0, i);

	connect(_button[i], SIGNAL(clicked(int, gui::MGridItem*)), _item, SLOT(handleButtonClicked(int, gui::MGridItem*)));
    }
}

gui::MGridItemIcons::~MGridItemIcons()
{
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridItemIcons" << std::endl;
    #endif

    for (int i = 0; i < MAX_BUTTONS; ++i)
	delete _button[i];
    delete _layout;
}

void gui::MGridItem::handleButtonClicked(int type, gui::MGridItem* item)
{
    switch (type)
    {
	case BUTTON_DELETE:
	    item->object()->remove();
	    break;
    }
}

gui::MGridItem::MGridItem(gui::MGridWidget* widget, core::MPhoto* photo) :
    QFrame(widget)
{
    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridItem (" << photo->info().fileInfo().baseName().toStdString() << ")" << std::endl;
    #endif

    // links
    _widget = widget;
    _obj = photo;

    // loading image and scaling
    QPixmap tmp(photo->info().fileInfo().absoluteFilePath());
    if (tmp.width() > tmp.height())
	tmp = tmp.scaledToWidth(MAX_THUMB_SIZE);
    else
	tmp = tmp.scaledToHeight(MAX_THUMB_SIZE);

    _imageLabel = new QLabel(this);
	_imageLabel->setPixmap(tmp);
	_imageLabel->resize(_imageLabel->pixmap()->size());
	_imageLabel->move((MAX_ITEM_W -_imageLabel->width()) / 2, std::min(10, MAX_ITEM_H - _imageLabel->height() / 2));

    setFixedSize(MAX_ITEM_W, MAX_ITEM_H);
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setLineWidth(1);

    // set up icons
    _icons = new gui::MGridItemIcons(this);
	_icons->move(0, 10 + MAX_THUMB_SIZE);
}

gui::MGridItem::~MGridItem()
{
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridItem" << std::endl;
    #endif

    delete _imageLabel;
    delete _icons;
}

gui::MGridWidget::MGridWidget(QWidget* parent) :
    QWidget(parent)
{
    // widget layout
    _layout = new QGridLayout(this);
	_layout->setSpacing(6);
	_layout->setContentsMargins(0, 0, 0, 0);	
	_layout->setSizeConstraint(QLayout::SetFixedSize);


    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridWidget" << std::endl;
    #endif
}

gui::MGridWidget::~MGridWidget()
{
    std::list<gui::MGridItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
	delete *it;

    delete _layout;

    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridItem" << std::endl;
    #endif
}

gui::MGridItem* gui::MGridWidget::insert(core::MPhoto* photo)
{
    int pos_x = count() % GRID_WIDTH;
    int pos_y = count() / GRID_WIDTH;

    // we create a grid item and add it to our layout
    gui::MGridItem* item = new gui::MGridItem(this, photo);
	_layout->addWidget(item, pos_y, pos_x, Qt::AlignLeft|Qt::AlignTop);
	_items.push_back(item);

    item->show();    
    return item;
}

void gui::MGridWidget::load(core::MObject* object)
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
		if ((*it)->typeId() == TYPEID_PHOTO)
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
    }
}

void gui::MGridWidget::hideAllItems()
{
    std::list<gui::MGridItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
    {
	_layout->removeWidget(*it);
	(*it)->hide();
    }    
}

gui::MGridItem* gui::MGridWidget::find(core::MObject* obj)
{
    std::list<gui::MGridItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
    {
	if ((*it)->object() == obj)
	    return *it;
    }
    return NULL;
}

core::MObject* gui::MGridWidget::remove(gui::MGridItem* item)
{
    item->hide();
    _items.remove(item);
    delete item;
    return item->object();
}

core::MObject* gui::MGridWidget::remove(core::MObject* obj)
{
    if (gui::MGridItem* item = find(obj))
	return remove(item);

    return NULL;
}
