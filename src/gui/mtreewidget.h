#ifndef MTREEWIDGET_H
#define MTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <core/mobject.h>
#include <iostream>
#include <string>

namespace gui
{

    class MTreeWidget : public QTreeWidget
    {
	Q_OBJECT

	public:
	    MTreeWidget(QWidget* parent = 0);
	    void insert(core::MObject* obj);	    

	public slots:
	    void remove();
    };

    class MTreeWidgetItem : public QTreeWidgetItem
    {
	public:
	    MTreeWidgetItem(core::MObject* obj = 0);
	    ~MTreeWidgetItem(){ delete _obj; } // also removes from MDatabase and MGallery

	private:	    
	    core::MObject* _obj;
    };
}

#endif // MTREEWIDGET_H
