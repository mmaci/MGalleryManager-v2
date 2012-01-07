#ifndef MNEWOBJECTDIALOG_H
#define MNEWOBJECTDIALOG_H

#include <string>
#include <iostream>

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <cmath>

const QString NEWOBJ_TITLE = "New Gallery";
#define NEWGALLERYDIALOG_X 300
#define NEWGALLERYDIALOG_Y 200
#define NEWGALLERYDIALOG_NAME_X 280
#define NEWGALLERYDIALOG_NAME_Y 20
#define NEWGALLERYDIALOG_DESC_X 280
#define NEWGALLERYDIALOG_DESC_Y 100
#define NEWGALLERYDIALOG_PADDING_X 10
#define NEWGALLERYDIALOG_PADDING_Y 10

namespace mgui
{
    class MNewObjectDialog : public QDialog
    {
	public:	    
	    MNewObjectDialog(QWidget* parent = NULL, QString name = QString());
	    MNewObjectDialog(QString picture, QWidget* parent = NULL, QString name = QString());
	    MNewObjectDialog(QWidget* parent, QString name, QString title = QString(), QString desc = QString());


	    std::string name(){ return _name; }
	    std::string description(){ return _description; }

	public slots:
	    void accept();

	private:
	    void setName();
	    void setDescription();

	    void _construct(QString picture = QString());

	    std::string _name;
	    std::string _description;

	    QLineEdit* _nameEdit;
	    QTextEdit* _descriptionEdit;
	    QPushButton* _okButton;
	    QPushButton* _cancelButton;
	    QLabel* _nameLabel;
	    QLabel* _descriptionLabel;
	    QGridLayout* _buttonLayout;
	    QGridLayout* _textLayout;
	    QWidget* _buttonWidget;
	    QWidget* _textWidget;
	    QLabel* _image;
    };
}

#endif // MNEWOBJECTDIALOG_H
