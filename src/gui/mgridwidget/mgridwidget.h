#ifndef MGRIDWIDGET_H
#define MGRIDWIDGET_H

#include <set>

#include <QWidget>
#include <QGridLayout>
#include <QCoreApplication>
#include <QLabel>

#include "gui/mgridwidget/mgridwidgetdefines.h"

#include "core/mgallery.h"

namespace mcore
{
    class MPhoto;
    class MObject;
}

namespace mgui
{
    class MGridWidget;    
    class MGridWidgetItem;
    class MGridWidget : public QWidget
    {
	Q_OBJECT

	public:
	    MGridWidget(QWidget* parent = 0);
	    ~MGridWidget();

	    MGridWidgetItem* insert(mcore::MGallery* gallery);
	    MGridWidgetThumbnail* insert(mcore::MPhoto* photo, int x = -1, int y = -1);

	    void load(mcore::MObject* object);
	    void hideAllItems();

	    int count() const { return _items.size(); }
	    QGridLayout* layout() { return _layout; }

	    bool remove(MGridWidgetItem* item);
	    bool remove(mcore::MObject* obj);
	    MGridWidgetItem* find(mcore::MObject* obj);

	    MGridWidgetViewer* generateGridViewer(mcore::MPhoto* photo, int maxSize = 0); // 0 means no scaling

	private:
	    QGridLayout* _layout;
	    std::set<MGridWidgetItem*> _items;
	    MGridWidgetViewer* _viewer;
    };
}

#endif // MGRIDWIDGET_H
