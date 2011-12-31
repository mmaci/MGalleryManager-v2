#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/mgridwidgetthumbnail.h"
#include "gui/mgridwidget/mgridwidgetitemiconset.h"
#include "gui/mgridwidget/mgridwidgetitembutton.h"

namespace gui
{

MGridWidgetItemIconSet::MGridWidgetItemIconSet(MGridWidgetThumbnail* parent) :
    QWidget(parent->toItem())
{
    _thumbnail = parent;
    _layout = new QGridLayout(this);

    for (int i = 0; i < MAX_BUTTONS; ++i)
    {
	_button[i] = new MGridWidgetItemButton(i, this);
	switch (i)
	{
	    case BUTTON_DELETE:
		_button[i]->setIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/images/but_delete.png")));
		break;
	    case BUTTON_FAV:
		_button[i]->setIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/images/but_fav.png")));
		break;
	    case BUTTON_SELECT:
		_button[i]->setIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/images/but_select.png")));
		break;
	    case BUTTON_EDIT:
		_button[i]->setIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/images/but_edit.png")));
		break;
	}
	_layout->addWidget(_button[i], 0, i);

	// don't remove the gui:: namespace in signals !
	connect(_button[i], SIGNAL(clicked(int, gui::MGridWidgetThumbnail*)), _thumbnail, SLOT(handleButtonClicked(int, gui::MGridWidgetThumbnail*)));
    }
}

MGridWidgetItemIconSet::~MGridWidgetItemIconSet()
{  
    for (int i = 0; i < MAX_BUTTONS; ++i)
	delete _button[i];
    delete _layout;
}

}
