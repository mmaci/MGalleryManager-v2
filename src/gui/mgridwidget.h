#ifndef MGRIDWIDGET_H
#define MGRIDWIDGET_H

#include <list>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QToolButton>
#include <QCoreApplication>

#include "core/mgallery.h"

// defines
#define MAX_THUMB_SIZE	150
#define MAX_ITEM_H	200
#define MAX_ITEM_W	170
#define GRID_WIDTH	4

enum Buttons
{
    BUTTON_EDIT,
    BUTTON_DELETE,
    BUTTON_FAV,
    BUTTON_SELECT,

    MAX_BUTTONS
};

namespace core
{
    class MPhoto;
    class MObject;
}

namespace gui
{
    class MGridItemButton : public QToolButton
    {
	Q_OBJECT

	public:
	    MGridItemButton(int type, MGridItem* item);
	    ~MGridItemButton();

	signals:
	    void clicked(int type, gui::MGridItem* item);

	private slots:
	    void reemitClicked(){ emit clicked(_type, _item); }

	private:
	    int _type;
	    MGridItem* _item;
    };

    class MGridItemIcons : public QWidget
    {
	Q_OBJECT

	public:
	    MGridItemIcons(QWidget* parent = NULL);
	    ~MGridItemIcons();

	private:
	    QGridLayout* _layout;
	    MGridItemButton* _button[MAX_BUTTONS];
	    core::MObject* _obj;
	    MGridItem* _item;
    };

    class MGridWidget;

    class MGridItem : public QFrame
    {
	Q_OBJECT

	public:
	    MGridItem(QWidget* parent = NULL);
	    MGridItem(MGridWidget* widget, core::MGallery* gallery);
	    MGridItem(MGridWidget* widget, core::MPhoto* photo);
	    ~MGridItem();

	    core::MObject* object(){ return _obj; }
	    MGridWidget* widget(){ return _widget; }

	public slots:
	    void handleButtonClicked(int type, gui::MGridItem* item);

	private:
	    void setupIcons();

	    MGridItemIcons* _icons;
	    QLabel* _imageLabel;
	    core::MObject* _obj;
	    MGridWidget* _widget;
    };

    class MGridWidget : public QWidget
    {
	Q_OBJECT

	public:
	    MGridWidget(QWidget* parent = 0);
	    ~MGridWidget();

	    MGridItem* insert(core::MGallery* gallery);
	    MGridItem* insert(core::MPhoto* gallery);

	    int count() const { return _items.size(); }
	    QGridLayout* layout() { return _layout; }

	    core::MObject* remove(gui::MGridItem* item);
	    core::MObject* remove(core::MObject* obj);
	    gui::MGridItem* find(core::MObject* obj);

	private:
	    QGridLayout* _layout;
	    std::list<MGridItem*> _items;
    };
}

#endif // MGRIDWIDGET_H
