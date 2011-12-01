#ifndef MGRIDWIDGETITEMICONSET_H
#define MGRIDWIDGETITEMICONSET_H

#include <QWidget>
#include <QGridLayout>

#include "gui/mgridwidget/mgridwidgetdefines.h"

namespace core
{
    class MObject;
}

namespace gui
{
    class MGridWidgetThumbnail;
    class MGridWidgetItemButton;
    class MGridWidgetItemIconSet : public QWidget
    {
	Q_OBJECT

	public:
	    MGridWidgetItemIconSet(MGridWidgetThumbnail* parent = NULL);
	    ~MGridWidgetItemIconSet();

	    MGridWidgetThumbnail* thumbnail(){ return _thumbnail; }

	private:
	    QGridLayout* _layout;
	    MGridWidgetItemButton* _button[MAX_BUTTONS];	    
	    MGridWidgetThumbnail* _thumbnail;
    };
}

#endif // MGRIDWIDGETITEMICONSET_H
