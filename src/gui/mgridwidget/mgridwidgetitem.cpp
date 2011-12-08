#include "gui/mgridwidget/mgridwidget.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/mgridwidgetitemiconset.h"
#include "gui/mgridwidget/mgridwidgetthumbnail.h"
#include "gui/mgridwidget/mgridwidgetviewer.h"
#include "core/mobject.h"
#include "core/mphoto.h"
#include <QInputDialog>

namespace gui
{

MGridWidgetItem::MGridWidgetItem(QWidget* parent) :
    QFrame(parent)
{
    _type = GRIDTYPE_ITEM;
}

MGridWidgetItem::MGridWidgetItem(MGridWidget* widget, core::MPhoto* photo) :
    QFrame(widget)
{
    _type = GRIDTYPE_ITEM;

    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridWidgetItem (" << photo->info().fileInfo().baseName().toStdString() << ")" << std::endl;
    #endif

    // links
    _widget = widget;
    _object = photo;    

    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setLineWidth(1);    
}

MGridWidgetViewer* MGridWidgetItem::toViewer()
{
    // static cast has no runtime check, conversion from a child to another child would fail
    return _type != GRIDTYPE_THUMBNAIL ? static_cast<MGridWidgetViewer*>(this) : NULL;
}

MGridWidgetThumbnail* MGridWidgetItem::toThumbnail()
{
    // static cast has no runtime check, conversion from a child to another child would fail
    return _type != GRIDTYPE_VIEWER ? static_cast<MGridWidgetThumbnail*>(this) : NULL;
}

MGridWidgetItem* MGridWidgetItem::toItem()
{
    return dynamic_cast<MGridWidgetItem*>(this);
}

void MGridWidgetItem::handleButtonClicked(int type, MGridWidgetThumbnail* thumbnail)
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

void MGridWidgetItem::reload(QPixmap pixmap)
{        
    if (MGridWidgetViewer* viewer = toViewer())
    {	
	_imageLabel->setPixmap(pixmap);
	_imageLabel->resize(pixmap.size());		

	viewer->setFixedSize(pixmap.width() + 50, pixmap.height() + 80);

	int indent = std::max(5, (pixmap.width() + 50 - MAX_VIEWER_BUTTONS*35 - 5) / 2);

	if (MGridWidgetViewer* viewer = toViewer())
	{
	    for (int i = 0; i < MAX_VIEWER_BUTTONS; ++i)
		viewer->moveButton(i, i*35 + indent, pixmap.height() + 45);
	}
    }
}

////////////////////////////////////////////////////////////////
// Public Slots handling buttons
////////////////////////////////////////////////////////////////

void MGridWidgetItem::rotatePhoto()
{
    bool ok;
    double value = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 0.0, -360.0, 360.0, 2, &ok);

    if (ok)
    {
       if (core::MPhoto* photo = _object->toPhoto())
       {
	   photo->rotate(mimage::RGB(255, 255, 255), value);
	   reload(photo->pixmapFromView(450));
	   // enable history
	   if (MGridWidgetViewer* viewer = toViewer())
	       viewer->enableHistoryButtons(true);
       }
    }
}

void MGridWidgetItem::resizePhoto()
{
}

void MGridWidgetItem::contrastPhoto()
{
    bool ok;
    double value = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 0.0, -100.0, 100.0, 2, &ok);

    if (ok)
    {
       if (core::MPhoto* photo = _object->toPhoto())
       {
	   photo->contrast(value);
	   reload(photo->pixmapFromView(450));
	   // enable history
	   if (MGridWidgetViewer* viewer = toViewer())
	       viewer->enableHistoryButtons(true);
       }
    }
}

void MGridWidgetItem::brightnessPhoto()
{
    bool ok;
    double value = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"), tr("Amount:"), 0.0, -100.0, 100.0, 2, &ok);

    if (ok)
    {
       if (core::MPhoto* photo = _object->toPhoto())
       {
	   photo->brightness(value);
	   reload(photo->pixmapFromView(450));
	   // enable history
	   if (MGridWidgetViewer* viewer = toViewer())
	       viewer->enableHistoryButtons(true);
       }
    }
}

void MGridWidgetItem::saturatePhoto()
{
}

void MGridWidgetItem::bnwPhoto()
{
}

void MGridWidgetItem::deletePhoto()
{
}

void MGridWidgetItem::editPhoto()
{
}

void MGridWidgetItem::favPhoto()
{
}

void MGridWidgetItem::forwPhoto()
{
    if (core::MPhoto* photo = _object->toPhoto())
    {
	if (photo->forward())
	    reload(photo->pixmapFromView(450));
    }
}

void MGridWidgetItem::backPhoto()
{
    if (core::MPhoto* photo = _object->toPhoto())
    {
	if (photo->backward())
	    reload(photo->pixmapFromView(450));
    }
}

} // NAMESPACE gui
