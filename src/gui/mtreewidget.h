#ifndef MTREEWIDGET_H
#define MTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <core/mobject.h>
#include <core/mgallery.h>
#include <core/mphoto.h>
#include <iostream>
#include <string>

namespace gui
{

    class MTreeWidgetItem;

    class MTreeWidget : public QTreeWidget
    {
	Q_OBJECT

	public:
	    MTreeWidget(QWidget* parent = 0);
	    void insert(core::MGallery* gallery, MTreeWidgetItem* parent = NULL);
	    void insert(core::MPhoto* photo, MTreeWidgetItem* parent /* = NULL */); // default value isn't set, because it should never happen
	    MTreeWidgetItem* selected();
	    core::MObject* remove();
    };

    class MTreeWidgetItem : public QTreeWidgetItem
    {
	public:
	    MTreeWidgetItem(core::MGallery* gallery);
	    MTreeWidgetItem(core::MPhoto* photo);
	    ~MTreeWidgetItem();

	    QTreeWidgetItem* toQWidgetItem(){ return dynamic_cast<QTreeWidgetItem*>(this); }

	    core::MObject* object(){ return _obj; }

	private:	    
	    core::MObject* _obj;
    };
}

#endif // MTREEWIDGET_H
