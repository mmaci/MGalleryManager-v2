#ifndef MGRIDWIDGETITEM_H
#define MGRIDWIDGETITEM_H

#include <QFrame>
#include <QLabel>
#include <QCoreApplication>

#include "gui/mgridwidgetdefines.h"

namespace core
{
    class MObject;
    class MGallery;
    class MPhoto;
}

namespace gui
{
    class MGridWidget;
    class MGridWidgetItemIconSet;
    class MGridWidgetItem : public QFrame
    {
	Q_OBJECT

	public:
	    MGridWidgetItem(QWidget* parent = NULL);
	    MGridWidgetItem(MGridWidget* widget, core::MGallery* gallery);
	    MGridWidgetItem(MGridWidget* widget, core::MPhoto* photo);
	    ~MGridWidgetItem();

	    core::MObject* object(){ return _object; }
	    MGridWidget* widget(){ return _widget; }

	    void showStar(bool apply);

	public slots:
	    void handleButtonClicked(int type, gui::MGridWidgetItem* item);

	private:
	    void setupIcons();

	    // gui
	    MGridWidget*		_widget;

	    MGridWidgetItemIconSet*	_icons;

	    QLabel*			_imageLabel;
	    QLabel*			_starLabel;

	    // core links
	    core::MObject*		_object;
    };
}

#endif // MGRIDWIDGETITEM_H
