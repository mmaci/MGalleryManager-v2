#include "gui/mgridwidget/mgridwidgetitembutton.h"

namespace gui
{

MGridWidgetItemButton::MGridWidgetItemButton(int type, MGridWidgetItemIconSet* iconSet) :
    QToolButton(iconSet)
{
    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridWidgetItemButton" << std::endl;
    #endif

    _type = type;
    _iconSet = iconSet;

    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

MGridWidgetItemButton::~MGridWidgetItemButton()
{
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridWidgetItemButton" << std::endl;
    #endif
}

}
