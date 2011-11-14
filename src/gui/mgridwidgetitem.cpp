#include "gui/mgridwidget.h"
#include "gui/mgridwidgetitem.h"
#include "gui/mgridwidgetitemiconset.h"

#include "core/mobject.h"
#include "core/mphoto.h"

void gui::MGridWidgetItem::handleButtonClicked(int type, gui::MGridWidgetItem* item)
{
    switch (type)
    {
	case BUTTON_DELETE:
	    item->object()->destroy();
	    break;
	case BUTTON_FAV:
	    item->object()->setFavourite();
	    break;
    }
}

void gui::MGridWidgetItem::showStar(bool apply)
{
    if (!_starLabel)
    {
	_starLabel = new QLabel(this);
	QPixmap tmp(QCoreApplication::applicationDirPath() + QString("/images/but_fav.png"));
	_starLabel->setPixmap(tmp);
	_starLabel->resize(_starLabel->pixmap()->size());
	_starLabel->move(5, 5);
    }

    apply ? _starLabel->show() : _starLabel->hide();
}

gui::MGridWidgetItem::MGridWidgetItem(gui::MGridWidget* widget, core::MPhoto* photo) :
    QFrame(widget)
{
    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridWidgetItem (" << photo->info().fileInfo().baseName().toStdString() << ")" << std::endl;
    #endif

    // links
    _widget = widget;
    _object = photo;

    // loading image and scaling
    QPixmap tmp(photo->info().fileInfo().absoluteFilePath());
    if (tmp.width() > tmp.height())
	tmp = tmp.scaledToWidth(MAX_THUMB_SIZE);
    else
	tmp = tmp.scaledToHeight(MAX_THUMB_SIZE);

    _starLabel = NULL;

    _imageLabel = new QLabel(this);
	_imageLabel->setPixmap(tmp);
	_imageLabel->resize(_imageLabel->pixmap()->size());
	_imageLabel->move((MAX_ITEM_W -_imageLabel->width()) / 2, std::min(10, MAX_ITEM_H - _imageLabel->height() / 2));

    setFixedSize(MAX_ITEM_W, MAX_ITEM_H);
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setLineWidth(1);

    // set up icons
    _icons = new gui::MGridWidgetItemIconSet(this);
	_icons->move(0, 10 + MAX_THUMB_SIZE);
}

gui::MGridWidgetItem::~MGridWidgetItem()
{
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridWidgetItem" << std::endl;
    #endif

    delete _imageLabel;
    delete _icons;
}
