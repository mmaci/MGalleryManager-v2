#include <QInputDialog>
#include <QString>

#include "gui/mgridwidget/mgridwidgetviewer.h"
#include "gui/mgridwidget/mgridwidgetitembutton.h"
#include "core/mphoto.h"

namespace gui
{

MGridWidgetViewer::MGridWidgetViewer(QWidget* parent) :
    MGridWidgetItem(parent)
{
    _type = GRIDTYPE_VIEWER;
}

MGridWidgetViewer::MGridWidgetViewer(QPixmap pixmap, MGridWidget* widget, core::MPhoto* photo) :
    MGridWidgetItem(widget, photo)
{
    _type = GRIDTYPE_VIEWER;

    _imageLabel = new QLabel(this);
	_imageLabel->setPixmap(pixmap);
	_imageLabel->resize(pixmap.size());

    setFixedSize(pixmap.width() + 50, pixmap.height() + 100);
    _imageLabel->move(25, 25);

    // button initialization
    int indent = (pixmap.width() + 50 - MAX_VIEWER_BUTTONS*35 - 5) / 2;
    for (int i = 0; i < MAX_VIEWER_BUTTONS; ++i)
    {
	_buttons[i] = new MGridWidgetItemButton(30, 30, this);
	_buttons[i]->move(i*(_buttons[0]->width() + 5) + indent, pixmap.height() + 35);

	switch (i)
	{
	    // image manipulation
	    case BUTTON_VIEWER_ROTATE:		
		_buttons[BUTTON_VIEWER_ROTATE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + rotate_icon_path));
		connect(_buttons[BUTTON_VIEWER_ROTATE], SIGNAL(clicked()), this, SLOT(rotatePhoto()));
		break;
	    case BUTTON_VIEWER_RESIZE:
		_buttons[BUTTON_VIEWER_RESIZE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + resize_icon_path));
		connect(this, SIGNAL(clicked()), this, SLOT(resizePhoto()));
		break;
	    case BUTTON_VIEWER_CONTRAST:
		_buttons[BUTTON_VIEWER_CONTRAST]->setIcon(QIcon(QCoreApplication::applicationDirPath() + contrast_icon_path));
		connect(_buttons[BUTTON_VIEWER_CONTRAST], SIGNAL(clicked()), this, SLOT(contrastPhoto()));
		break;
	    case BUTTON_VIEWER_BRIGHTNESS:
		_buttons[BUTTON_VIEWER_BRIGHTNESS]->setIcon(QIcon(QCoreApplication::applicationDirPath() + brightness_icon_path));
		connect(_buttons[BUTTON_VIEWER_BRIGHTNESS], SIGNAL(clicked()), this, SLOT(brightnessPhoto()));
		break;
	    case BUTTON_VIEWER_SATURATE:
		_buttons[BUTTON_VIEWER_SATURATE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + saturate_icon_path));
		connect(this, SIGNAL(clicked()), this, SLOT(saturatePhoto()));
		break;
	    case BUTTON_VIEWER_BNW:
		_buttons[BUTTON_VIEWER_BNW]->setIcon(QIcon(QCoreApplication::applicationDirPath() + bnw_icon_path));
		connect(this, SIGNAL(clicked()), this, SLOT(bnwPhoto()));
		break;

	    // photo management
	    case BUTTON_VIEWER_DELETE:
		_buttons[BUTTON_VIEWER_DELETE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + delete_icon_path));
		connect(this, SIGNAL(clicked()), this, SLOT(deletePhoto()));
		break;
	    case BUTTON_VIEWER_EDIT:
		_buttons[BUTTON_VIEWER_EDIT]->setIcon(QIcon(QCoreApplication::applicationDirPath() + edit_icon_path));
		connect(this, SIGNAL(clicked()), this, SLOT(editPhoto()));
		break;
	    case BUTTON_VIEWER_FAV:
		_buttons[BUTTON_VIEWER_FAV]->setIcon(QIcon(QCoreApplication::applicationDirPath() + fav_icon_path));
		connect(this, SIGNAL(clicked()), this, SLOT(favPhoto()));
		break;

	    // history
	    case BUTTON_VIEWER_BACK:
		_buttons[BUTTON_VIEWER_BACK]->setIcon(QIcon(QCoreApplication::applicationDirPath() + back_icon_path));
		connect(_buttons[BUTTON_VIEWER_BACK], SIGNAL(clicked()), this, SLOT(backPhoto()));
		break;
	    case BUTTON_VIEWER_FORW:
		_buttons[BUTTON_VIEWER_FORW]->setIcon(QIcon(QCoreApplication::applicationDirPath() + forw_icon_path));
		connect(_buttons[BUTTON_VIEWER_FORW], SIGNAL(clicked()), this, SLOT(forwPhoto()));
		break;
	    default:
		break;
	}
    }

}



} // NAMESPACE GUI
