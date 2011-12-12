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
    class MTreeWidget : public QTreeWidget
    {
	Q_OBJECT

	public:
	    MTreeWidget(QWidget* parent = 0);
	    MTreeWidgetItem* insert(core::MGallery* gallery, MTreeWidgetItem* parent = NULL);
	    MTreeWidgetItem* insert(core::MPhoto* photo, MTreeWidgetItem* parent /* = NULL */); // default value isn't set, because it should never happen
												// a photo must always be inside a gallery

	    void loadGallery(core::MGallery* gallery, MTreeWidgetItem* parent = NULL, int depth = 0);

	    MTreeWidgetItem* selected();
	    core::MObject* remove(MTreeWidgetItem* item = NULL);
    };
}

#endif // MTREEWIDGET_H
