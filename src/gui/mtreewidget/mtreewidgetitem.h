#ifndef MTREEWIDGETITEM_H
#define MTREEWIDGETITEM_H

#include <QTreeWidgetItem>

namespace mcore
{
    class MObject;
    class MPhoto;
    class MGallery;
}

namespace mgui
{
    class MTreeWidget;
    class MTreeWidgetItem : public QTreeWidgetItem
    {
	public:
	    MTreeWidgetItem(MTreeWidget* widget, mcore::MGallery* gallery);
	    MTreeWidgetItem(MTreeWidget* widget, mcore::MPhoto* photo);
	    ~MTreeWidgetItem();

	    QTreeWidgetItem* toQWidgetItem(){ return dynamic_cast<QTreeWidgetItem*>(this); }

	    mcore::MObject* object(){ return _obj; }

	    MTreeWidget* widget(){ return _widget; }

	    void destroy();

	    void setFavourite(bool apply);

	private:
	    mcore::MObject* _obj;
	    MTreeWidget* _widget;
    };
}

#endif // MTREEWIDGETITEM_H
