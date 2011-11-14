#ifndef MGRIDWIDGET_H
#define MGRIDWIDGET_H

#include <list>

#include <QWidget>
#include <QGridLayout>
#include <QCoreApplication>
#include <QLabel>

#include "gui/mgridwidgetdefines.h"

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
	    MGridWidgetItem* insert(core::MPhoto* gallery);

	    void load(core::MObject* object);
	    void hideAllItems();

	    int count() const { return _items.size(); }
	    QGridLayout* layout() { return _layout; }

	    core::MObject* remove(gui::MGridWidgetItem* item);
	    core::MObject* remove(core::MObject* obj);
	    gui::MGridWidgetItem* find(core::MObject* obj);

	private:
	    QGridLayout* _layout;
	    std::list<MGridWidgetItem*> _items;
	    QLabel* _displayPhoto;
    };
}

#endif // MGRIDWIDGET_H
