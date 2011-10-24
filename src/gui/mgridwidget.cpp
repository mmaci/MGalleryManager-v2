#include "mgridwidget.h"
#include <iostream>

gui::MGridItem::MGridItem(core::MPhoto* photo, QWidget* parent) :
    QWidget(parent)
{
    // loading image and scaling
    QPixmap tmp(photo->info().fileInfo().absoluteFilePath());
    if (tmp.width() > tmp.height())
	tmp = tmp.scaledToWidth(MAX_THUMB_SIZE);
    else
	tmp = tmp.scaledToHeight(MAX_THUMB_SIZE);

    _imageLabel = new QLabel(this);
	_imageLabel->setPixmap(tmp);
	_imageLabel->resize(_imageLabel->pixmap()->size());

    _obj = photo;
}

gui::MGridItem::~MGridItem()
{
    delete _imageLabel;
}

gui::MGridWidget::MGridWidget(QWidget* parent) :
    QWidget(parent)
{
    // widget layout
    _layout = new QGridLayout(this);
	_layout->setSpacing(6);
	_layout->setContentsMargins(11, 11, 11, 11);
	_layout->setContentsMargins(0, 0, 0, 0);
}

gui::MGridWidget::~MGridWidget()
{
    std::list<gui::MGridItem*>::iterator it;
    for (it = _items.begin(); it != _items.end(); ++it)
	delete *it;

    delete _layout;
}

void gui::MGridWidget::insert(core::MPhoto* photo)
{
    int pos_x = count() % GRID_WIDTH;
    int pos_y = count() / GRID_WIDTH;

    // we create a grid item and add it to our layout
    gui::MGridItem* item = new gui::MGridItem(photo, this);
	_layout->addWidget(item, pos_y, pos_x, 1, 1);
	_items.push_back(item);

    item->show();
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

core::MObject* gui::MGridWidget::remove(core::MObject* obj)
{
    if (gui::MGridItem* item = find(obj))
    {
	item->hide();
	_items.remove(item);
	delete item;
	return obj;
    }
    return NULL;
}
