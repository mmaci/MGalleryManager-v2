#ifndef MGRIDWIDGETTHUMBNAIL_H
#define MGRIDWIDGETTHUMBNAIL_H

#include <QWidget>

#include "gui/mgridwidget/mgridwidgetdefines.h"
#include "gui/mgridwidget/mgridwidgetitem.h"

const int THUMBNAIL_ITEM_WIDTH	    = 170;
const int THUMBNAIL_ITEM_HEIGHT	    = 200;
const int THUMBNAIL_PIX_SIZE	    = 140;

namespace mcore
{
    class MPhoto;
}

namespace mgui
{
    class MGridWidget;
    class MGridWidgetItemIconSet;
    class MGridWidgetThumbnail : public MGridWidgetItem
    {
	public:
	    MGridWidgetThumbnail(QWidget* parent = NULL);
	    MGridWidgetThumbnail(mcore::MPhoto* photo, QWidget* parent = NULL);
	    ~MGridWidgetThumbnail();

	    void showStar(bool apply);

	private:
	    void setupIcons();

	    QLabel*	_imageLabel;
	    QLabel*	_starLabel;
	    QLabel*	_nameLabel;
	    MGridWidgetItemIconSet* _icons;
    };
}

#endif // MGRIDWIDGETTHUMBNAIL_H
