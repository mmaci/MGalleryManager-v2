#include "gui/mgridwidget/mgridwidgetitembutton.h"
#include "gui/mgridwidget/mgridwidgetitem.h"

namespace mgui
{

MGridWidgetItemButton::MGridWidgetItemButton(int type, MGridWidgetItemIconSet* iconSet) :
    QToolButton(iconSet)
{
    _type = type;
    _iconSet = iconSet;
    _item = NULL;

    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

MGridWidgetItemButton::MGridWidgetItemButton(int width, int height, MGridWidgetItem* item) :
    QToolButton(item)
{
    _type = NULL;
    _iconSet = NULL;
    _item = item;

    resize(width, height);
}

MGridWidgetItemButton::~MGridWidgetItemButton()
{

}

}
