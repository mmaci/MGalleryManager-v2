#include "gui/mnewobjectdialog.h"

namespace mgui
{

MNewObjectDialog::MNewObjectDialog(QWidget* parent, QString name) :
    QDialog(parent)
{
    _construct();

    if (name.isEmpty())
	name = NEWOBJ_TITLE;

    setWindowTitle(name);
}

MNewObjectDialog::MNewObjectDialog(QString picture, QWidget* parent, QString name) :
    QDialog(parent)
{
    _construct(picture);

    if (name.isEmpty())
	name = NEWOBJ_TITLE;

    setWindowTitle(name);
}

MNewObjectDialog::MNewObjectDialog(QWidget* parent, QString name, QString title, QString desc) :
    QDialog(parent)
{
    _construct();

    if (name.isEmpty())
	name = NEWOBJ_TITLE;

    _nameEdit->setText(title);
    _descriptionEdit->setText(desc);

    setWindowTitle(name);
}

void MNewObjectDialog::_construct(QString picture)
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


    // n o thumbnail
    if (picture.isEmpty())
    {
	resize(300, 230);
	_textWidget->resize(300, 200);
	_buttonWidget->move(0, 190);
    }
    // thumbnail
    else
    {
	resize(300, 350);
	_textWidget->resize(300, 200);
	_buttonWidget->move(0, 190);
	_image = new QLabel(this);
	_image->setPixmap(QPixmap(picture).scaledToHeight(100));
	_image->move(std::fabs(300 - _image->pixmap()->width()) / 2, 240);
    }

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void MNewObjectDialog::accept()
{
    setName();
    setDescription();

    QDialog::accept();
}

void MNewObjectDialog::setName()
{
    _name = _nameEdit->text().toStdString();
}

void MNewObjectDialog::setDescription()
{
    _description = _descriptionEdit->document()->toPlainText().toStdString();
}

} // NAMESPACE mgui
