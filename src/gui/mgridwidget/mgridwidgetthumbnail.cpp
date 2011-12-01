#include "gui/mgridwidget/mgridwidgetthumbnail.h"
#include "gui/mgridwidget/mgridwidgetitemiconset.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "core/mobject.h"
#include "core/mphoto.h"

namespace gui
{

MGridWidgetThumbnail::MGridWidgetThumbnail(QWidget* parent) :
    MGridWidgetItem(parent)
{
    _type = GRIDTYPE_THUMBNAIL;
}

MGridWidgetThumbnail::MGridWidgetThumbnail(MGridWidget* widget, core::MPhoto* photo) :
    MGridWidgetItem(widget, photo)
{
    _type = GRIDTYPE_THUMBNAIL;

    // set up icons
    _icons = new MGridWidgetItemIconSet(this);
	_icons->move(0, 10 + MAX_THUMB_SIZE);

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
