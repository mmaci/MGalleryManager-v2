#include "gui/mgridwidgetitem.h"
#include "gui/mgridwidgetitembutton.h"

gui::MGridWidgetItemButton::MGridWidgetItemButton(int type, gui::MGridWidgetItem* item) :
    QToolButton(item)
{
    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridWidgetItemButton" << std::endl;
    #endif

    _type = type;
    _item = item;

    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

gui::MGridWidgetItemButton::~MGridWidgetItemButton()
{
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridWidgetItemButton" << std::endl;
    #endif
}
