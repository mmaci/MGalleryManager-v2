#ifndef MGRIDWIDGETVIEWER_H
#define MGRIDWIDGETVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

#include "gui/mgridwidget/mgridwidgetitem.h"
#include "core/mobject.h"
#include "core/mphoto.h"

namespace core
{
    class MPhoto;
}

namespace gui
{
    class MGridWidgetViewer : public MGridWidgetItem
    {
	public:
	    MGridWidgetViewer(QWidget* parent = NULL);
	    MGridWidgetViewer(QPixmap pixmap, MGridWidget* widget, core::MPhoto* photo);

	private:
	    QPixmap* _imagePixmap;
	    QPushButton* but;
    };
}

#endif // MGRIDWIDGETVIEWER_H
