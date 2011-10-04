#ifndef MTREEWIDGET_H
#define MTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <core/mobject.h>

namespace gui
{

    class MTreeWidget : public QTreeWidget
    {
	public:
	    MTreeWidget();
    };

    class MTreeWidgetItem : public QTreeWidgetItem
    {
	public:
	    MTreeWidgetItem(MTreeWidget* parent, MTreeWidgetItem* preceding, core::MObject* obj)
	    {
		_widgetItem = new QTreeWidgetItem();
		_obj = obj;
	    }

	private:
	    QTreeWidgetItem* _widgetItem;
	    core::MObject* _obj;
    };
}

#endif // MTREEWIDGET_H
