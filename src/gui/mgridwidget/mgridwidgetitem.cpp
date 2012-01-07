#include "gui/mgridwidget/mgridwidget.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/mgridwidgetitemiconset.h"
#include "gui/mgridwidget/mgridwidgetthumbnail.h"
#include "gui/mgridwidget/mgridwidgetviewer.h"
#include "gui/mnewobjectdialog.h"
#include <QInputDialog>
#include "gui/mnewobjectdialog.h"
#include "gui/mresizedialog.h"

namespace mgui
{

MGridWidgetItem::MGridWidgetItem(QWidget* parent) :
    QFrame(parent)
{
    _type = GRIDTYPE_ITEM;
}

MGridWidgetItem::MGridWidgetItem(mcore::MPhoto* photo, QWidget* parent) :
    QFrame(parent)
{
    _type = GRIDTYPE_ITEM;

    // links
    _object = photo;

    // gui
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setLineWidth(1);    
}

MGridWidgetItem::~MGridWidgetItem()
{
    if (MGridWidget* p = dynamic_cast<MGridWidget*>(parent()))
	p->remove(this);
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
	    return;

	case BUTTON_EDIT:
	    QString name, title, description;
	    switch (thumbnail->object()->typeId())
	    {
		case TYPEID_GALLERY:
		    if (mcore::MGallery* gallery = thumbnail->object()->toGallery())
		    {
			name = QString(gallery->name().c_str());
			description = QString(gallery->description().c_str());
			title = QString(gallery->name().c_str());
		    }
		    break;
		case TYPEID_PHOTO:
		    if (mcore::MPhoto* photo = thumbnail->object()->toPhoto())
		    {
			name = QString(photo->name().c_str());
			description = QString(photo->description().c_str());
			title = QString(photo->name().c_str());
		    }
		    break;
	    }

	    MNewObjectDialog dialog(this, name, title, description);
	    if (dialog.exec())
	    {
		switch (thumbnail->object()->typeId())
		{
		    case TYPEID_GALLERY:
			if (mcore::MGallery* gallery = thumbnail->object()->toGallery())
			{
			    gallery->setName(dialog.name());
			    gallery->setDescription(dialog.description());
			}
			break;
		    case TYPEID_PHOTO:
			if (mcore::MPhoto* photo = thumbnail->object()->toPhoto())
			{
			    photo->setName(dialog.name());
			    photo->setDescription(dialog.description());
			}
			break;
		}
	    }
	    break;
    }
}

void MGridWidgetItem::destroy()
{
    hide();

    if (MGridWidget* p = dynamic_cast<MGridWidget*>(parent()))
	p->remove(this);

    delete this;
}



} // NAMESPACE gui
