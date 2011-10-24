#ifndef MGRIDWIDGET_H
#define MGRIDWIDGET_H

#include <list>

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include <core/mgallery.h>
#include <core/mphoto.h>

// defines
#define MAX_THUMB_SIZE	200
#define GRID_WIDTH	5

namespace gui
{
    class MGridItem : public QWidget
    {
	Q_OBJECT

	public:
	    MGridItem(QWidget* parent = NULL);
	    MGridItem(core::MGallery* gallery, QWidget* parent = NULL);
	    MGridItem(core::MPhoto* photo, QWidget* parent = NULL);
	    ~MGridItem();

	    core::MObject* object(){ return _obj; }

	private:
	    QWidget* _icons;
	    QLabel* _imageLabel;
	    core::MObject* _obj;

    };

    class MGridWidget : public QWidget
    {
	Q_OBJECT

	public:
	    MGridWidget(QWidget* parent = 0);
	    ~MGridWidget();

	    void insert(core::MGallery* gallery);
	    void insert(core::MPhoto* gallery);

	    int count() const { return _items.size(); }
	    QGridLayout* layout() { return _layout; }
	    core::MObject* remove(core::MObject* obj);
	    gui::MGridItem* find(core::MObject* obj);

	private:
	    QGridLayout* _layout;
	    std::list<MGridItem*> _items;
    };
}

#endif // MGRIDWIDGET_H
