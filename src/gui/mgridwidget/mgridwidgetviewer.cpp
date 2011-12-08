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

    ////////////////////////////////////////////////////////////////
    // Positioning Buttons
    ////////////////////////////////////////////////////////////////

    const int buttonWidth = MAX_VIEWER_BUTTONS*35 + 5;
    setFixedSize(std::max(pixmap.width() + 50, buttonWidth), pixmap.height() + 80);
    _imageLabel->move(25, 40);

    // button initialization
    int indent = std::max(5, (pixmap.width() + 50 - MAX_VIEWER_BUTTONS*35 - 5) / 2);
    for (int i = 0; i < MAX_VIEWER_BUTTONS; ++i)
    {
	_buttons[i] = new MGridWidgetItemButton(30, 30, this);
	_buttons[i]->move(i*(_buttons[0]->width() + 5) + indent, pixmap.height() + 45);

	switch (i)
	{
	    // image manipulation
	    case BUTTON_VIEWER_ROTATE:		
		_buttons[BUTTON_VIEWER_ROTATE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + ROTATE_ICON_PATH));
		connect(_buttons[BUTTON_VIEWER_ROTATE], SIGNAL(clicked()), this, SLOT(rotatePhoto()));
		break;
	    case BUTTON_VIEWER_RESIZE:
		_buttons[BUTTON_VIEWER_RESIZE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + RESIZE_ICON_PATH));
		connect(this, SIGNAL(clicked()), this, SLOT(resizePhoto()));
		break;
	    case BUTTON_VIEWER_CONTRAST:
		_buttons[BUTTON_VIEWER_CONTRAST]->setIcon(QIcon(QCoreApplication::applicationDirPath() + CONTRAST_ICON_PATH));
		connect(_buttons[BUTTON_VIEWER_CONTRAST], SIGNAL(clicked()), this, SLOT(contrastPhoto()));
		break;
	    case BUTTON_VIEWER_BRIGHTNESS:
		_buttons[BUTTON_VIEWER_BRIGHTNESS]->setIcon(QIcon(QCoreApplication::applicationDirPath() + BRIGHTNESS_ICON_PATH));
		connect(_buttons[BUTTON_VIEWER_BRIGHTNESS], SIGNAL(clicked()), this, SLOT(brightnessPhoto()));
		break;
	    case BUTTON_VIEWER_SATURATE:
		_buttons[BUTTON_VIEWER_SATURATE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + SATURATE_ICON_PATH));
		connect(_buttons[BUTTON_VIEWER_SATURATE], SIGNAL(clicked()), this, SLOT(saturatePhoto()));
		break;
	    case BUTTON_VIEWER_BNW:
		_buttons[BUTTON_VIEWER_BNW]->setIcon(QIcon(QCoreApplication::applicationDirPath() + BNW_ICON_PATH));
		connect(this, SIGNAL(clicked()), this, SLOT(bnwPhoto()));
		break;

	    // photo management
	    case BUTTON_VIEWER_DELETE:
		_buttons[BUTTON_VIEWER_DELETE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + DELETE_ICON_PATH));
		connect(this, SIGNAL(clicked()), this, SLOT(deletePhoto()));
		break;
	    case BUTTON_VIEWER_EDIT:
		_buttons[BUTTON_VIEWER_EDIT]->setIcon(QIcon(QCoreApplication::applicationDirPath() + EDIT_ICON_PATH));
		connect(this, SIGNAL(clicked()), this, SLOT(editPhoto()));
		break;
	    case BUTTON_VIEWER_FAV:
		_buttons[BUTTON_VIEWER_FAV]->setIcon(QIcon(QCoreApplication::applicationDirPath() + FAV_ICON_PATH));
		connect(this, SIGNAL(clicked()), this, SLOT(favPhoto()));
		break;

	    default:
		break;
	}
    }

    indent = 5;
    for (int i = 0; i < MAX_HISTORY_BUTTONS; ++i)
    {
	_historyButtons[i] = new MGridWidgetItemButton(30, 30, this);
	_historyButtons[i]->move(i*(_buttons[0]->width() + 5) + indent, indent);
	switch (i)
	{
	    // history
	    case BUTTON_HISTORY_BACK:
		_historyButtons[BUTTON_HISTORY_BACK]->setIcon(QIcon(QCoreApplication::applicationDirPath() + BACK_ICON_PATH));
		connect(_historyButtons[BUTTON_HISTORY_BACK], SIGNAL(clicked()), this, SLOT(backPhoto()));
		break;

	    case BUTTON_HISTORY_FORW:
		_historyButtons[BUTTON_HISTORY_FORW]->setIcon(QIcon(QCoreApplication::applicationDirPath() + FORW_ICON_PATH));
		connect(_historyButtons[BUTTON_HISTORY_FORW], SIGNAL(clicked()), this, SLOT(forwPhoto()));
		break;
	}
    }
    enableHistoryButtons(false);
}

void MGridWidgetViewer::enableHistoryButtons(bool enable)
{
    for (int i = 0; i < MAX_HISTORY_BUTTONS; ++i)
	_historyButtons[i]->setEnabled(enable);
}

void MGridWidgetViewer::enableHistoryButtonBack(bool enable)
{
    _historyButtons[BUTTON_HISTORY_BACK]->setEnabled(enable);
}

void MGridWidgetViewer::enableHistoryButtonForw(bool enable)
{
    _historyButtons[BUTTON_HISTORY_FORW]->setEnabled(enable);
}

void MGridWidgetViewer::moveButton(int id, int x, int y)
{
    _buttons[id]->move(x, y);
}

} // NAMESPACE GUI
