#include "gui/mgridwidget/mgridwidgetviewer.h"
#include "core/mphoto.h"
#include <iostream>

namespace gui
{

MGridWidgetViewer::MGridWidgetViewer(QWidget* parent) :
    MGridWidgetItem(parent)
{
    _type = GRIDTYPE_VIEWER;
}

MGridWidgetViewer::MGridWidgetViewer(QPixmap pixmap, MGridWidget* widget, core::MPhoto* photo) :
    MGridWidgetItem(widget, photo)
{
    _type = GRIDTYPE_VIEWER;

    _imageLabel = new QLabel(this);
	_imageLabel->setPixmap(pixmap);
	_imageLabel->resize(pixmap.size());

    setFixedSize(pixmap.width() + 50, pixmap.height() + 100);
    _imageLabel->move(25, 25);

    but = new QPushButton(QString("Rotate"), this);

    connect(but, SIGNAL(clicked()), this, SLOT(rotateRight()));
}

} // NAMESPACE GUI
