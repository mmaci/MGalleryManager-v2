#include "gui/mresizedialog.h"

namespace gui
{

MResizeDialog::MResizeDialog(QWidget* parent) :
    QDialog(parent)
{
    // texts
    _textWidget = new QWidget(this);
    _widthLabel = new QLabel(tr("Width:"), _textWidget);
    _widthEdit = new QLineEdit(_textWidget);
	_widthEdit->setValidator(new QIntValidator(_widthEdit));

    _heightLabel = new QLabel(tr("Height:"), _textWidget);
    _heightEdit = new QLineEdit(_textWidget);
	_heightEdit->setValidator(new QIntValidator(_heightEdit));

    // buttons
    _buttonWidget = new QWidget(this);
    _okButton = new QPushButton(_buttonWidget);
	_okButton->setText(tr("Ok"));

    _cancelButton = new QPushButton(_buttonWidget);
	_cancelButton->setText(tr("Cancel"));


    // add everything to layout
    _textLayout = new QGridLayout(_textWidget);
	_textLayout->addWidget(_widthLabel);
	_textLayout->addWidget(_widthEdit);
	_textLayout->addWidget(_heightLabel);
	_textLayout->addWidget(_heightEdit);

    _buttonLayout = new QGridLayout(_buttonWidget);
	_buttonLayout->addWidget(_okButton, 0, 0);
	_buttonLayout->addWidget(_cancelButton, 0, 1);

	resize(300, 230);
	_textWidget->resize(300, 200);
	_buttonWidget->move(0, 190);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setWindowTitle(tr("Resize"));
}

void MResizeDialog::accept()
{
    setWidth();
    setHeight();

    QDialog::accept();
}

void MResizeDialog::setWidth()
{
    _width = _widthEdit->text().toInt();
}

void MResizeDialog::setHeight()
{
    _height = _widthEdit->text().toInt();
}

} // NAMESPACE gui

