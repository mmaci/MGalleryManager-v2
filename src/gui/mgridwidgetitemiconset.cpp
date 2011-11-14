#include "gui/mgridwidgetitem.h"
#include "gui/mgridwidgetitemiconset.h"
#include "gui/mgridwidgetitembutton.h"

gui::MGridWidgetItemIconSet::MGridWidgetItemIconSet(QWidget* parent) :
    QWidget(parent)
{
    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridWidgetItemIconSet" << std::endl;
    #endif

    _item = static_cast<gui::MGridWidgetItem*>(parent);
    _layout = new QGridLayout(this);

    for (int i = 0; i < MAX_BUTTONS; ++i)
    {
	_button[i] = new gui::MGridWidgetItemButton(i, _item);
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

	connect(_button[i], SIGNAL(clicked(int, gui::MGridWidgetItem*)), _item, SLOT(handleButtonClicked(int, gui::MGridWidgetItem*)));
    }
}

gui::MGridWidgetItemIconSet::~MGridWidgetItemIconSet()
{
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridWidgetItemIconSet" << std::endl;
    #endif

    for (int i = 0; i < MAX_BUTTONS; ++i)
	delete _button[i];
    delete _layout;
}
