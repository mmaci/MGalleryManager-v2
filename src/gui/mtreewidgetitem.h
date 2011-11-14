#ifndef MTREEWIDGETITEM_H
#define MTREEWIDGETITEM_H

#include <QTreeWidgetItem>

namespace core
{
    class MObject;
    class MPhoto;
    class MGallery;
}

namespace gui
{
    class MTreeWidget;
    class MTreeWidgetItem : public QTreeWidgetItem
    {
	public:
	    MTreeWidgetItem(MTreeWidget* widget, core::MGallery* gallery);
	    MTreeWidgetItem(MTreeWidget* widget, core::MPhoto* photo);
	    ~MTreeWidgetItem();

	    QTreeWidgetItem* toQWidgetItem(){ return dynamic_cast<QTreeWidgetItem*>(this); }

	    core::MObject* object(){ return _obj; }

	    MTreeWidget* widget(){ return _widget; }

	    void highlight(bool apply);

	private:
	    core::MObject* _obj;
	    MTreeWidget* _widget;
    };
}

#endif // MTREEWIDGETITEM_H
