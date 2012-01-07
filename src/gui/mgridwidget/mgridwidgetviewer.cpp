#include <QInputDialog>
#include <QString>

#include "gui/mgridwidget/mgridwidgetviewer.h"
#include "gui/mgridwidget/mgridwidgetitembutton.h"
#include "core/mphoto.h"

namespace mgui
{

MGridWidgetViewer::MGridWidgetViewer(QWidget* parent) :
    MGridWidgetItem(parent)
{       
    _type = GRIDTYPE_VIEWER;
}

MGridWidgetViewer::MGridWidgetViewer(QPixmap pixmap, mcore::MPhoto* photo, QWidget* parent) :
    MGridWidgetItem(photo, parent)
{
    _type = GRIDTYPE_VIEWER;
    _zoom = 100.0;

    setFixedSize(750, 720);

    _imageLabel = new QLabel(this);
	_imageLabel->setPixmap(pixmap);
	_imageLabel->setBackgroundRole(QPalette::Base);
	_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	_imageLabel->setScaledContents(true);

    _imageArea = new QScrollArea(this);
	_imageArea->setWidget(_imageLabel);
	_imageArea->setBackgroundRole(QPalette::Dark);
	_imageArea->move(0, VIEWER_BUTTON_SIZE + 2*VIEWER_MARGIN);
	// there are buttons on the bottom and on the top
	_imageArea->resize(750, 720 - 2*VIEWER_BUTTON_SIZE - 4*VIEWER_MARGIN);

    ////////////////////////////////////////////////////////////////
    // Positioning Buttons
    ////////////////////////////////////////////////////////////////

    // HISTORY BUTTONS
    //
    for (int i = 0; i < MAX_HISTORY_BUTTONS; ++i)
    {
	_historyButtons[i] = new MGridWidgetItemButton(VIEWER_BUTTON_SIZE, VIEWER_BUTTON_SIZE, this);
	_historyButtons[i]->move(i*(VIEWER_BUTTON_SIZE + VIEWER_MARGIN) + VIEWER_MARGIN, VIEWER_MARGIN);
	switch (i)
	{
	    case BUTTON_HISTORY_BACK:
		_historyButtons[BUTTON_HISTORY_BACK]->setIcon(QIcon(QCoreApplication::applicationDirPath() + BACK_ICON_PATH));
		connect(_historyButtons[BUTTON_HISTORY_BACK], SIGNAL(clicked()), this, SLOT(backPhoto()));
		break;

	    case BUTTON_HISTORY_FORW:
		_historyButtons[BUTTON_HISTORY_FORW]->setIcon(QIcon(QCoreApplication::applicationDirPath() + FORW_ICON_PATH));
		connect(_historyButtons[BUTTON_HISTORY_FORW], SIGNAL(clicked()), this, SLOT(forwPhoto()));
		break;
	}
    }
    enableHistoryButtons(false);

    // PHOTO MANIPULATION BUTTONS
    //
    for (int i = 0; i < MAX_VIEWER_BUTTONS; ++i)
    {
	_buttons[i] = new MGridWidgetItemButton(VIEWER_BUTTON_SIZE, VIEWER_BUTTON_SIZE, this);
	_buttons[i]->move(i*(VIEWER_BUTTON_SIZE + VIEWER_MARGIN) + VIEWER_MARGIN, _imageArea->height() + VIEWER_BUTTON_SIZE + 3*VIEWER_MARGIN);

	switch (i)
	{	    
	    case BUTTON_VIEWER_ROTATE:		
		_buttons[BUTTON_VIEWER_ROTATE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + ROTATE_ICON_PATH));
		connect(_buttons[BUTTON_VIEWER_ROTATE], SIGNAL(clicked()), this, SLOT(rotatePhoto()));
		break;
	    case BUTTON_VIEWER_RESIZE:
		_buttons[BUTTON_VIEWER_RESIZE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + RESIZE_ICON_PATH));
		connect(_buttons[BUTTON_VIEWER_RESIZE], SIGNAL(clicked()), this, SLOT(resizePhoto()));
		break;
	    case BUTTON_VIEWER_CONTRAST:
		_buttons[BUTTON_VIEWER_CONTRAST]->setIcon(QIcon(QCoreApplication::applicationDirPath() + CONTRAST_ICON_PATH));
		connect(_buttons[BUTTON_VIEWER_CONTRAST], SIGNAL(clicked()), this, SLOT(contrastPhoto()));
		break;
	    case BUTTON_VIEWER_BRIGHTNESS:
		_buttons[BUTTON_VIEWER_BRIGHTNESS]->setIcon(QIcon(QCoreApplication::applicationDirPath() + BRIGHTNESS_ICON_PATH));
		connect(_buttons[BUTTON_VIEWER_BRIGHTNESS], SIGNAL(clicked()), this, SLOT(brightnessPhoto()));
		break;
	    case BUTTON_VIEWER_SATURATE:
		_buttons[BUTTON_VIEWER_SATURATE]->setIcon(QIcon(QCoreApplication::applicationDirPath() + SATURATE_ICON_PATH));
		connect(_buttons[BUTTON_VIEWER_SATURATE], SIGNAL(clicked()), this, SLOT(saturatePhoto()));
		break;
	    case BUTTON_VIEWER_BNW:
		_buttons[BUTTON_VIEWER_BNW]->setIcon(QIcon(QCoreApplication::applicationDirPath() + BNW_ICON_PATH));
		connect(_buttons[BUTTON_VIEWER_BNW], SIGNAL(clicked()), this, SLOT(bnwPhoto()));
		break;

	    default:
		break;
	}
    }    
}

MGridWidgetViewer::~MGridWidgetViewer()
{
    for (int i = 0; i < MAX_VIEWER_BUTTONS; ++i)
	delete _buttons[i];

    for (int i = 0; i < MAX_HISTORY_BUTTONS; ++i)
	delete _historyButtons[i];

    delete _imageLabel;
    delete _imageArea;
}

void MGridWidgetViewer::reload(QPixmap pixmap)
{
    _imageLabel->setPixmap(pixmap);
    _imageLabel->resize(pixmap.size());
}

void MGridWidgetViewer::enableHistoryButtons(bool enable)
{
    for (int i = 0; i < MAX_HISTORY_BUTTONS; ++i)
	_historyButtons[i]->setEnabled(enable);
}

void MGridWidgetViewer::enableHistoryButtonBack(bool enable)
{
    _historyButtons[BUTTON_HISTORY_BACK]->setEnabled(enable);
}

void MGridWidgetViewer::enableHistoryButtonForw(bool enable)
{
    _historyButtons[BUTTON_HISTORY_FORW]->setEnabled(enable);
}

void MGridWidgetViewer::moveButton(int id, int x, int y)
{
    _buttons[id]->move(x, y);
}

////////////////////////////////////////////////////////////////
// Public Slots handling buttons
////////////////////////////////////////////////////////////////

void MGridWidgetViewer::rotatePhoto()
{
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Rotation"), tr("Amount:"), 0.0, 0.0, 360.0, 2, &ok);

    if (ok)
    {
       if (mcore::MPhoto* photo = object()->toPhoto())
       {
	   photo->rotate(mimage::RGB(255, 255, 255), value);
	   reload(photo->pixmapFromView());
	   // enable history
	   enableHistoryButtons(true);
       }
    }
}

void MGridWidgetViewer::resizePhoto()
{
    if (mcore::MPhoto* photo = object()->toPhoto())
    {

	MResizeDialog dialog(photo->width(), photo->height(), this);

	if (dialog.exec())
	{
	   photo->resize(static_cast<double>(dialog.getWidth()), static_cast<double>(dialog.getHeight()));
	   reload(photo->pixmapFromView());
	   // enable history
	    enableHistoryButtons(true);
	}
    }

}

void MGridWidgetViewer::contrastPhoto()
{
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Contrast"), tr("Amount:"), 0.0, -100.0, 100.0, 2, &ok);

    if (ok)
    {
       if (mcore::MPhoto* photo = object()->toPhoto())
       {
	   photo->contrast(value);
	   reload(photo->pixmapFromView());
	   // enable history
	   enableHistoryButtons(true);
       }
    }
}

void MGridWidgetViewer::brightnessPhoto()
{
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Brightness"), tr("Amount:"), 0.0, -100.0, 100.0, 2, &ok);

    if (ok)
    {
       if (mcore::MPhoto* photo = object()->toPhoto())
       {
	   photo->brightness(value);
	   reload(photo->pixmapFromView());
	   // enable history
	   enableHistoryButtons(true);
       }
    }
}

void MGridWidgetViewer::saturatePhoto()
{
    bool ok;
    double value = QInputDialog::getDouble(this, tr("Saturation"), tr("Amount:"), 0.0, -100.0, 100.0, 2, &ok);

    if (ok)
    {
       if (mcore::MPhoto* photo = object()->toPhoto())
       {
	   photo->saturation(value);
	   reload(photo->pixmapFromView());
	   // enable history
	   enableHistoryButtons(true);
       }
    }
}

void MGridWidgetViewer::bnwPhoto()
{
    if (mcore::MPhoto* photo = object()->toPhoto())
    {
	photo->blackandwhite();
	reload(photo->pixmapFromView());
	// enable history
	enableHistoryButtons(true);
    }
}

void MGridWidgetViewer::deletePhoto()
{
}

void MGridWidgetViewer::editPhoto()
{
}

void MGridWidgetViewer::favPhoto()
{
}

void MGridWidgetViewer::forwPhoto()
{
    if (mcore::MPhoto* photo = object()->toPhoto())
    {
	if (photo->forward())
	    reload(photo->pixmapFromView());
    }
}

void MGridWidgetViewer::backPhoto()
{
    if (mcore::MPhoto* photo = object()->toPhoto())
    {
	if (photo->backward())
	    reload(photo->pixmapFromView());
    }
}

} // NAMESPACE GUI
