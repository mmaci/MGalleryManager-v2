#include "gui/mresizedialog.h"

namespace mgui
{

MResizeDialog::MResizeDialog(int width, int height, QWidget* parent) :
    QDialog(parent)
{
    // texts
    _textWidget = new QWidget(this);
    _widthLabel = new QLabel(tr("Width (px):"), _textWidget);
    _widthEdit = new QLineEdit(_textWidget);
	_widthEdit->setValidator(new QIntValidator(_widthEdit));
	if (width)
	    _widthEdit->insert(QString().setNum(width));

    _heightLabel = new QLabel(tr("Height (px):"), _textWidget);
    _heightEdit = new QLineEdit(_textWidget);
	_heightEdit->setValidator(new QIntValidator(_heightEdit));
	if (height)
	    _heightEdit->insert(QString().setNum(height));

    // scale checkbox
    _propCheckbox = new QCheckBox(this);
	_propCheckbox->setChecked(true);
    _propLabel = new QLabel(tr("Keep proportions?"), _textWidget);

    // buttons
    _buttonWidget = new QWidget(this);
    _okButton = new QPushButton(_buttonWidget);
	_okButton->setText(tr("Ok"));

    _cancelButton = new QPushButton(_buttonWidget);
	_cancelButton->setText(tr("Cancel"));


    // add everything to layout
    _textLayout = new QGridLayout(_textWidget);
	_textLayout->addWidget(_widthLabel, 0, 0);
	_textLayout->addWidget(_widthEdit, 0, 1);
	_textLayout->addWidget(_heightLabel, 1, 0);
	_textLayout->addWidget(_heightEdit, 1, 1);
	_textLayout->addWidget(_propLabel, 2, 0);
	_textLayout->addWidget(_propCheckbox, 2, 1);

    _buttonLayout = new QGridLayout(_buttonWidget);
	_buttonLayout->addWidget(_okButton, 0, 0);
	_buttonLayout->addWidget(_cancelButton, 0, 1);

	resize(200, 110);
	_textWidget->resize(200, 80);
	_buttonWidget->move(0, 70);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    connect(_widthEdit, SIGNAL(textEdited(QString)), this, SLOT(recalculateHeight(QString)));
    connect(_heightEdit, SIGNAL(textEdited(QString)), this, SLOT(recalculateWidth(QString)));

    _width = width;
    _height = height;
    _prop = static_cast<double>(width) / static_cast<double>(height);

    setWindowTitle(tr("Resize"));
}

void MResizeDialog::recalculateWidth(QString newText)
{
    if (_prop == 0.0)
	return;

    if (_propCheckbox->isChecked())
	_widthEdit->setText(QString().setNum(static_cast<int>(newText.toDouble() * _prop)));
}

void MResizeDialog::recalculateHeight(QString newText)
{
    if (_prop == 0.0)
	return;

    if (_propCheckbox->isChecked())
	_heightEdit->setText(QString().setNum(static_cast<int>(newText.toDouble() / _prop)));
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
    _height = _heightEdit->text().toInt();
}

} // NAMESPACE gui

