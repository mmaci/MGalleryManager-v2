#include "gui/mgridwidget/mgridwidgetthumbnail.h"
#include "gui/mgridwidget/mgridwidgetitemiconset.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "core/mobject.h"
#include "core/mphoto.h"

namespace mgui
{

MGridWidgetThumbnail::MGridWidgetThumbnail(QWidget* parent) :
    MGridWidgetItem(parent)
{
    _type = GRIDTYPE_THUMBNAIL;

    _starLabel	= NULL;
    _imageLabel = NULL;
    _nameLabel	= NULL;
}

MGridWidgetThumbnail::MGridWidgetThumbnail(mcore::MPhoto* photo, QWidget* parent) :
    MGridWidgetItem(photo, parent)
{
    _type = GRIDTYPE_THUMBNAIL;

    _starLabel	= NULL;

    // image preview
    // loading image and scaling
    _imageLabel = new QLabel(this);
    _imageLabel->setPixmap(photo->pixmapFromFile(THUMBNAIL_PIX_SIZE));
    _imageLabel->resize(_imageLabel->pixmap()->size());
    // center the image
    _imageLabel->move(std::max(0, (THUMBNAIL_ITEM_WIDTH - _imageLabel->width()) / 2),	// x
		      10);								// y

    // label
    _nameLabel = new QLabel(QString(photo->name().c_str()), this);
    _nameLabel->move(10, THUMBNAIL_PIX_SIZE + 15);

    // sets icons
    _icons = new MGridWidgetItemIconSet(this);
    _icons->move(0, 25 + THUMBNAIL_PIX_SIZE);

    setFixedSize(THUMBNAIL_ITEM_WIDTH, THUMBNAIL_ITEM_HEIGHT);

    photo->setThumbnail(this);
}

MGridWidgetThumbnail::~MGridWidgetThumbnail()
{
    delete _imageLabel;
    delete _nameLabel;
    delete _icons;
    delete _starLabel;
}

void MGridWidgetThumbnail::showStar(bool apply)
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

} // NAMESPACE GUI
