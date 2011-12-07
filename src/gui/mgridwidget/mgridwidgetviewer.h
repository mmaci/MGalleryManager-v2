#ifndef MGRIDWIDGETVIEWER_H
#define MGRIDWIDGETVIEWER_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

#include "gui/mgridwidget/mgridwidgetitem.h"
#include "core/mobject.h"
#include "core/mphoto.h"

#include "shareddefines.h"

enum ViewerButtons
{
    BUTTON_VIEWER_ROTATE,
    BUTTON_VIEWER_RESIZE,
    BUTTON_VIEWER_CONTRAST,
    BUTTON_VIEWER_BRIGHTNESS,
    BUTTON_VIEWER_SATURATE,
    BUTTON_VIEWER_BNW,

    BUTTON_VIEWER_DELETE,
    BUTTON_VIEWER_EDIT,
    BUTTON_VIEWER_FAV,

    BUTTON_VIEWER_BACK,
    BUTTON_VIEWER_FORW,

    MAX_VIEWER_BUTTONS
};

const QString viewer_icons_path =			  "/images";
const QString rotate_icon_path = viewer_icons_path	+ "/rotate_anticlock.png";
const QString resize_icon_path = viewer_icons_path	+ "/resize.png";
const QString contrast_icon_path = viewer_icons_path	+ "/contrast.png";
const QString brightness_icon_path = viewer_icons_path	+ "/brightness.png";
const QString saturate_icon_path = viewer_icons_path	+ "/saturate.png";
const QString bnw_icon_path = viewer_icons_path		+ "/bnw.png";
const QString delete_icon_path = viewer_icons_path	+ "/delete.png";
const QString edit_icon_path = viewer_icons_path	+ "/edit.png";
const QString fav_icon_path = viewer_icons_path		+ "/fav.png";
const QString forw_icon_path = viewer_icons_path	+ "/forward.png";
const QString back_icon_path = viewer_icons_path	+ "/backward.png";

namespace core
{
    class MPhoto;
}

namespace gui
{
    class MGridWidgetItemButton;

    class MGridWidgetViewer : public MGridWidgetItem
    {
	public:
	    MGridWidgetViewer(QWidget* parent = NULL);
	    MGridWidgetViewer(QPixmap pixmap, MGridWidget* widget, core::MPhoto* photo);
	    void reload();

	private:
	    QPixmap* _imagePixmap;
	    MGridWidgetItemButton* _buttons[MAX_VIEWER_BUTTONS];
    };
}

#endif // MGRIDWIDGETVIEWER_H
