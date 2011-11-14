#ifndef MGRIDWIDGETITEMBUTTON_H
#define MGRIDWIDGETITEMBUTTON_H

#include <QToolButton>

namespace gui
{
    class MGridWidgetItem;
    class MGridWidgetItemButton : public QToolButton
    {
	Q_OBJECT

	public:
	    MGridWidgetItemButton(int type, MGridWidgetItem* item);
	    ~MGridWidgetItemButton();

	signals:
	    void clicked(int type, gui::MGridWidgetItem* item);

	private slots:
	    void reemitClicked(){ emit clicked(_type, _item); }

	private:
	    int _type;
	    MGridWidgetItem* _item;
    };
}

#endif // MGRIDWIDGETITEMBUTTON_H
