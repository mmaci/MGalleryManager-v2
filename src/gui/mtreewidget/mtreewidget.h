#ifndef MTREEWIDGET_H
#define MTREEWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <core/mobject.h>

namespace mcore
{
    class MPhoto;
    class MGallery;
}

namespace mgui
{    
    class MTreeWidget : public QTreeWidget
    {
	Q_OBJECT

	public:
	    MTreeWidget(QWidget* parent = 0);
	    MTreeWidgetItem* insert(mcore::MGallery* gallery, MTreeWidgetItem* parent = NULL);
	    MTreeWidgetItem* insert(mcore::MPhoto* photo, MTreeWidgetItem* parent /* = NULL */); // default value isn't set, because it should never happen
												// a photo must always be inside a gallery
	    void loadGallery(mcore::MGallery* gallery, MTreeWidgetItem* parent = NULL, int depth = 0);

	    MTreeWidgetItem* selected();
	    void remove(MTreeWidgetItem* item = NULL);
    };
}

#endif // MTREEWIDGET_H
