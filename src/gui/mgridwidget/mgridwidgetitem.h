#ifndef MGRIDWIDGETITEM_H
#define MGRIDWIDGETITEM_H

#include <QFrame>
#include <QLabel>
#include <QCoreApplication>

#include "gui/mgridwidget/mgridwidgetdefines.h"
#include "core/mobject.h"
#include "core/mphoto.h"
#include "core/mgallery.h"

namespace mgui
{
    class MGridWidget;
    class MGridWidgetThumbnail;
    class MGridWidgetViewer;
    class MGridWidgetItem : public QFrame
    {
	Q_OBJECT

	public:
	    MGridWidgetItem(QWidget* parent = NULL);
	    MGridWidgetItem(mcore::MGallery* gallery, QWidget* parent = NULL);
	    MGridWidgetItem(mcore::MPhoto* photo, QWidget* parent = NULL);
	    virtual ~MGridWidgetItem();

	    MGridWidgetViewer* toViewer();
	    MGridWidgetThumbnail* toThumbnail();
	    MGridWidgetItem* toItem();

	    mcore::MObject* object(){ return _object; }
	    void destroy();

	public slots:    
	    void handleButtonClicked(int type, mgui::MGridWidgetThumbnail* thumbnail);

	protected:
	    int _type;	    

	private:	       
	    // core links
	    mcore::MObject*		_object;	    
    };
}

#endif // MGRIDWIDGETITEM_H
