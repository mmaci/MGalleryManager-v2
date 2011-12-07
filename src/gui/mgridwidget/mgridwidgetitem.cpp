#include "gui/mgridwidget/mgridwidget.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/mgridwidgetitemiconset.h"
#include "gui/mgridwidget/mgridwidgetthumbnail.h"
#include "gui/mgridwidget/mgridwidgetviewer.h"
#include "core/mobject.h"
#include "core/mphoto.h"
#include <QInputDialog>

gui::MGridWidgetItem::MGridWidgetItem(QWidget* parent) :
    QFrame(parent)
{
    _type = gui::GRIDTYPE_ITEM;
}

gui::MGridWidgetItem::MGridWidgetItem(gui::MGridWidget* widget, core::MPhoto* photo) :
    QFrame(widget)
{
    _type = gui::GRIDTYPE_ITEM;

    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridWidgetItem (" << photo->info().fileInfo().baseName().toStdString() << ")" << std::endl;
    #endif

    // links
    _widget = widget;
    _object = photo;    

    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setLineWidth(1);    
}

gui::MGridWidgetViewer* gui::MGridWidgetItem::toViewer()
{
    // static cast has no runtime check, conversion from a child to another child would fail
    return _type != gui::GRIDTYPE_THUMBNAIL ? static_cast<gui::MGridWidgetViewer*>(this) : NULL;
}

gui::MGridWidgetThumbnail* gui::MGridWidgetItem::toThumbnail()
{
    // static cast has no runtime check, conversion from a child to another child would fail
    return _type != gui::GRIDTYPE_VIEWER ? static_cast<gui::MGridWidgetThumbnail*>(this) : NULL;
}

gui::MGridWidgetItem* gui::MGridWidgetItem::toItem()
{
    return dynamic_cast<gui::MGridWidgetItem*>(this);
}

void gui::MGridWidgetItem::handleButtonClicked(int type, gui::MGridWidgetThumbnail* thumbnail)
{
    switch (type)
    {
	case BUTTON_DELETE:
	    thumbnail->object()->destroy();
	    break;
	case BUTTON_FAV:
	    thumbnail->object()->setFavourite();
	    break;
    }
}

void gui::MGridWidgetItem::reload(QPixmap pixmap)
{        
    if (gui::MGridWidgetViewer* viewer = toViewer())
    {
	delete _imageLabel;

	_imageLabel = new QLabel(this);
	_imageLabel->setPixmap(pixmap);
	_imageLabel->resize(pixmap.size());
	_imageLabel->move(25, 25);
	_imageLabel->show();

	viewer->setFixedSize(pixmap.width() + 50, pixmap.height() + 100);
    }
}

////////////////////////////////////////////////////////////////
// Public Slots handling buttons
////////////////////////////////////////////////////////////////

void gui::MGridWidgetItem::rotatePhoto()
{
    bool ok;
    double value = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 0.0, -360.0, 360.0, 2, &ok);

    if (ok)
    {
       if (core::MPhoto* photo = _object->toPhoto())
       {
	   photo->rotate(mimage::RGB(255, 255, 255), value);
	   reload(photo->pixmapFromView(450));
       }
    }
}

void gui::MGridWidgetItem::resizePhoto()
{
}

void gui::MGridWidgetItem::contrastPhoto()
{
    bool ok;
    double value = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 0.0, -100.0, 100.0, 2, &ok);

    if (ok)
    {
       if (core::MPhoto* photo = _object->toPhoto())
       {
	   photo->contrast(value);
	   reload(photo->pixmapFromView(450));
       }
    }
}

void gui::MGridWidgetItem::brightnessPhoto()
{
    bool ok;
    double value = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 0.0, -100.0, 100.0, 2, &ok);

    if (ok)
    {
       if (core::MPhoto* photo = _object->toPhoto())
       {
	   photo->brightness(value);
	   reload(photo->pixmapFromView(450));
       }
    }
}

void gui::MGridWidgetItem::saturatePhoto()
{
}

void gui::MGridWidgetItem::bnwPhoto()
{
}

void gui::MGridWidgetItem::deletePhoto()
{
}

void gui::MGridWidgetItem::editPhoto()
{
}

void gui::MGridWidgetItem::favPhoto()
{
}

void gui::MGridWidgetItem::forwPhoto()
{
    if (core::MPhoto* photo = _object->toPhoto())
    {
	if (photo->forward())
	    reload(photo->pixmapFromView(450));
    }
}

void gui::MGridWidgetItem::backPhoto()
{
    if (core::MPhoto* photo = _object->toPhoto())
    {
	if (photo->backward())
	    reload(photo->pixmapFromView(450));
    }
}
