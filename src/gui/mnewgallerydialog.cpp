#include "mnewgallerydialog.h"

gui::MNewGalleryDialog::MNewGalleryDialog(QWidget* parent) :
    QDialog(parent)
{        
    // texts
    _textWidget = new QWidget(this);
    _nameLabel = new QLabel(tr("Name:"), _textWidget);
    _nameEdit = new QLineEdit(_textWidget);

    _descriptionLabel = new QLabel(tr("Description:"), _textWidget);
    _descriptionEdit = new QTextEdit(_textWidget);

    // buttons
    _buttonWidget = new QWidget(this);
    _okButton = new QPushButton(_buttonWidget);
	_okButton->setText(tr("Ok"));

    _cancelButton = new QPushButton(_buttonWidget);
	_cancelButton->setText(tr("Cancel"));


    // add everything to layout
    _textLayout = new QGridLayout(_textWidget);
	_textLayout->addWidget(_nameLabel);
	_textLayout->addWidget(_nameEdit);
	_textLayout->addWidget(_descriptionLabel);
	_textLayout->addWidget(_descriptionEdit);

    _buttonLayout = new QGridLayout(_buttonWidget);
	_buttonLayout->addWidget(_okButton, 0, 0);
	_buttonLayout->addWidget(_cancelButton, 0, 1);

	resize(300, 230);
	_textWidget->resize(300, 200);
	_buttonWidget->move(0, 190);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setWindowTitle(tr(NEWGALLERYDIALOG_TITLE));
}

void gui::MNewGalleryDialog::accept()
{
    setName();
    setDescription();

    QDialog::accept();
}

void gui::MNewGalleryDialog::setName()
{
    _name = _nameEdit->text().toStdString();
}

void gui::MNewGalleryDialog::setDescription()
{
    _description = _descriptionEdit->document()->toPlainText().toStdString();
}
