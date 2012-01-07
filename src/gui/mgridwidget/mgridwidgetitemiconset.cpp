#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/mgridwidgetthumbnail.h"
#include "gui/mgridwidget/mgridwidgetitemiconset.h"
#include "gui/mgridwidget/mgridwidgetitembutton.h"

namespace mgui
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
	    case BUTTON_EDIT:
		_button[i]->setIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/images/but_edit.png")));
		break;
	}
	_layout->addWidget(_button[i], 0, i);

	// don't remove the mgui:: namespace in signals !
	connect(_button[i], SIGNAL(clicked(int, mgui::MGridWidgetThumbnail*)), _thumbnail, SLOT(handleButtonClicked(int, mgui::MGridWidgetThumbnail*)));
    }
}

MGridWidgetItemIconSet::~MGridWidgetItemIconSet()
{  
    for (int i = 0; i < MAX_BUTTONS; ++i)
	delete _button[i];
    delete _layout;
}

}
