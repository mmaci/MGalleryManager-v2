#ifndef MGRIDWIDGET_H
#define MGRIDWIDGET_H

#include <set>

#include <QWidget>
#include <QGridLayout>
#include <QCoreApplication>
#include <QLabel>

#include "gui/mgridwidget/mgridwidgetdefines.h"

#include "core/mgallery.h"

namespace core
{
    class MPhoto;
    class MObject;
}

namespace gui
{
    class MGridWidget;    
    class MGridWidgetItem;
    class MGridWidget : public QWidget
    {
	Q_OBJECT

	public:
	    MGridWidget(QWidget* parent = 0);
	    ~MGridWidget();

	    MGridWidgetItem* insert(core::MGallery* gallery);
	    MGridWidgetThumbnail* insert(core::MPhoto* photo, int x = -1, int y = -1);

	    void load(core::MObject* object);
	    void hideAllItems();

	    int count() const { return _items.size(); }
	    QGridLayout* layout() { return _layout; }

	    core::MObject* remove(gui::MGridWidgetItem* item);
	    core::MObject* remove(core::MObject* obj);
	    MGridWidgetItem* find(core::MObject* obj);

	    MGridWidgetViewer* generateGridViewer(core::MPhoto* photo, int maxSize = 0); // 0 means no scaling

	private:
	    QGridLayout* _layout;
	    std::set<MGridWidgetItem*> _items;
	    MGridWidgetViewer* _viewer;
    };
}

#endif // MGRIDWIDGET_H
