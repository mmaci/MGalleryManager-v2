#ifndef MGRIDWIDGETTHUMBNAIL_H
#define MGRIDWIDGETTHUMBNAIL_H

#include <QWidget>

#include "gui/mgridwidget/mgridwidgetdefines.h"
#include "gui/mgridwidget/mgridwidgetitem.h"

namespace core
{
    class MPhoto;
}

namespace gui
{
    class MGridWidget;
    class MGridWidgetItemIconSet;
    class MGridWidgetThumbnail : public MGridWidgetItem
    {
	public:
	    MGridWidgetThumbnail(QWidget* parent = NULL);
	    MGridWidgetThumbnail(MGridWidget* widget, core::MPhoto* photo);

	    void showStar(bool apply);

	private:
	    void setupIcons();

	    QLabel*			_starLabel;
	    MGridWidgetItemIconSet*	_icons;
    };
}

#endif // MGRIDWIDGETTHUMBNAIL_H
