#ifndef MGRIDWIDGETITEMBUTTON_H
#define MGRIDWIDGETITEMBUTTON_H

#include <QToolButton>
#include "gui/mgridwidget/mgridwidgetitemiconset.h"

namespace gui
{    
    class MGridWidgetThumbnail;
    class MGridWidgetItem;
    class MGridWidgetItemButton : public QToolButton
    {
	Q_OBJECT

	public:
	    MGridWidgetItemButton(int type, MGridWidgetItemIconSet* iconSet);
	    MGridWidgetItemButton(int width, int height, MGridWidgetItem* item);
	    ~MGridWidgetItemButton();

	signals:
	    void clicked(int type, gui::MGridWidgetThumbnail* thumbnail);

	private slots:
	    void reemitClicked(){ emit clicked(_type, _iconSet->thumbnail()); }

	private:
	    int _type;
	    MGridWidgetItem* _item;
	    MGridWidgetItemIconSet* _iconSet;
    };
}

#endif // MGRIDWIDGETITEMBUTTON_H
