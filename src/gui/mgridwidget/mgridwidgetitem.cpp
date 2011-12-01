#include "gui/mgridwidget/mgridwidget.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/mgridwidgetitemiconset.h"
#include "gui/mgridwidget/mgridwidgetthumbnail.h"
#include "gui/mgridwidget/mgridwidgetviewer.h"
#include "core/mobject.h"
#include "core/mphoto.h"

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
