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
	    void insert(core::MGallery* gallery);
	    void insert(core::MPhoto* photo);
	    MTreeWidgetItem* selected();

	public slots:
	    void remove();
    };

    class MTreeWidgetItem : public QTreeWidgetItem
    {
	public:
	    MTreeWidgetItem(core::MGallery* gallery);
	    MTreeWidgetItem(core::MPhoto* photo);
	    ~MTreeWidgetItem(){ delete _obj; } // also removes from MDatabase and MGallery
	    QTreeWidgetItem* toQWidgetItem(){ return dynamic_cast<QTreeWidgetItem*>(this); }

	    core::MObject* object(){ return _obj; }

	private:	    
	    core::MObject* _obj;
    };
}

#endif // MTREEWIDGET_H
