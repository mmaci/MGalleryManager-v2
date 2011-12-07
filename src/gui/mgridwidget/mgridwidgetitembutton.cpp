#include "gui/mgridwidget/mgridwidgetitembutton.h"
#include "gui/mgridwidget/mgridwidgetitem.h"

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
    _item = NULL;

    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

MGridWidgetItemButton::MGridWidgetItemButton(int width, int height, MGridWidgetItem* item) :
    QToolButton(item)
{
    #ifdef _DEBUG
    std::cout << "Creating new instance of MGridWidgetItemButton" << std::endl;
    #endif

    _type = NULL;
    _iconSet = NULL;
    _item = item;

    resize(width, height);
}

MGridWidgetItemButton::~MGridWidgetItemButton()
{
    #ifdef _DEBUG
    std::cout << "Deleting an instance of MGridWidgetItemButton" << std::endl;
    #endif
}

}
