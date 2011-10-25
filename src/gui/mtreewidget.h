#ifndef MTREEWIDGET_H
#define MTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <core/mobject.h>

namespace core
{
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

	private:
	    core::MObject* _obj;
	    MTreeWidget* _widget;
    };

    class MTreeWidget : public QTreeWidget
    {
	Q_OBJECT

	public:
	    MTreeWidget(QWidget* parent = 0);
	    MTreeWidgetItem* insert(core::MGallery* gallery, MTreeWidgetItem* parent = NULL);
	    MTreeWidgetItem* insert(core::MPhoto* photo, MTreeWidgetItem* parent /* = NULL */); // default value isn't set, because it should never happen
	    MTreeWidgetItem* selected();	    
	    core::MObject* remove(MTreeWidgetItem* item = NULL);
    };
}

#endif // MTREEWIDGET_H
