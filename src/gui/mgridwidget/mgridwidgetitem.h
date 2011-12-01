#ifndef MGRIDWIDGETITEM_H
#define MGRIDWIDGETITEM_H

#include <QFrame>
#include <QLabel>
#include <QCoreApplication>

#include "gui/mgridwidget/mgridwidgetdefines.h"
#include "core/mobject.h"
#include "core/mphoto.h"

namespace core
{    
    class MGallery;    
}

namespace gui
{
    class MGridWidget;
    class MGridWidgetThumbnail;
    class MGridWidgetViewer;
    class MGridWidgetItem : public QFrame
    {
	Q_OBJECT

	public:
	    MGridWidgetItem(QWidget* parent = NULL);
	    MGridWidgetItem(MGridWidget* widget, core::MGallery* gallery);
	    MGridWidgetItem(MGridWidget* widget, core::MPhoto* photo);
	    virtual ~MGridWidgetItem(){ }

	    MGridWidgetViewer* toViewer();
	    MGridWidgetThumbnail* toThumbnail();
	    MGridWidgetItem* toItem();

	    core::MObject* object(){ return _object; }
	    MGridWidget* widget(){ return _widget; }

	public slots:
	    void handleButtonClicked(int type, gui::MGridWidgetThumbnail* thumbnail);
	    void rotateRight()
	    {

	    }

	protected:
	    int _type;
	    QLabel*			_imageLabel;

	private:	    
	    // gui
	    MGridWidget*		_widget;	    



	    // core links
	    core::MObject*		_object;	    
    };
}

#endif // MGRIDWIDGETITEM_H
