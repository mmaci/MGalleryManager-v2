#ifndef MGRIDWIDGETITEMICONSET_H
#define MGRIDWIDGETITEMICONSET_H

#include <QWidget>
#include <QGridLayout>

#include "mgridwidgetdefines.h"

namespace core
{
    class MObject;
}

namespace gui
{
    class MGridWidgetItem;
    class MGridWidgetItemButton;
    class MGridWidgetItemIconSet : public QWidget
    {
	Q_OBJECT

	public:
	    MGridWidgetItemIconSet(QWidget* parent = NULL);
	    ~MGridWidgetItemIconSet();

	private:
	    QGridLayout* _layout;
	    MGridWidgetItemButton* _button[MAX_BUTTONS];	    
	    MGridWidgetItem* _item;
    };
}

#endif // MGRIDWIDGETITEMICONSET_H
