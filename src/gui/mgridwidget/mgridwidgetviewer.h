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

enum MainViewerButtons
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

    MAX_VIEWER_BUTTONS,
};

enum HistoryButtons
{
    BUTTON_HISTORY_BACK,
    BUTTON_HISTORY_FORW,

    MAX_HISTORY_BUTTONS
};

const QString VIEWER_ICONS_PATH =			  "/images";
const QString ROTATE_ICON_PATH = VIEWER_ICONS_PATH	+ "/rotate_anticlock.png";
const QString RESIZE_ICON_PATH = VIEWER_ICONS_PATH	+ "/resize.png";
const QString CONTRAST_ICON_PATH = VIEWER_ICONS_PATH	+ "/contrast.png";
const QString BRIGHTNESS_ICON_PATH = VIEWER_ICONS_PATH	+ "/brightness.png";
const QString SATURATE_ICON_PATH = VIEWER_ICONS_PATH	+ "/saturate.png";
const QString BNW_ICON_PATH = VIEWER_ICONS_PATH		+ "/bnw.png";
const QString DELETE_ICON_PATH = VIEWER_ICONS_PATH	+ "/delete.png";
const QString EDIT_ICON_PATH = VIEWER_ICONS_PATH	+ "/edit.png";
const QString FAV_ICON_PATH = VIEWER_ICONS_PATH		+ "/fav.png";

const QString FORW_ICON_PATH = VIEWER_ICONS_PATH	+ "/forward.png";
const QString BACK_ICON_PATH = VIEWER_ICONS_PATH	+ "/backward.png";

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
	    void enableHistoryButtons(bool enable);
	    void enableHistoryButtonForw(bool enable);
	    void enableHistoryButtonBack(bool enable);

	    void moveButton(int id, int x, int y);
	private:
	    MGridWidgetItemButton* _buttons[MAX_VIEWER_BUTTONS];
	    MGridWidgetItemButton* _historyButtons[MAX_HISTORY_BUTTONS];
    };
}

#endif // MGRIDWIDGETVIEWER_H
