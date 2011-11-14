#ifndef MNEWGALLERYDIALOG_H
#define MNEWGALLERYDIALOG_H

#include <string>
#include <iostream>

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#define NEWGALLERYDIALOG_TITLE "Create New Gallery"
#define NEWGALLERYDIALOG_X 300
#define NEWGALLERYDIALOG_Y 200
#define NEWGALLERYDIALOG_NAME_X 280
#define NEWGALLERYDIALOG_NAME_Y 20
#define NEWGALLERYDIALOG_DESC_X 280
#define NEWGALLERYDIALOG_DESC_Y 100
#define NEWGALLERYDIALOG_PADDING_X 10
#define NEWGALLERYDIALOG_PADDING_Y 10

namespace gui
{
    class MNewGalleryDialog : public QDialog
    {
	public:
	    MNewGalleryDialog(QWidget* parent = NULL);

	    std::string name(){ return _name; }
	    std::string description(){ return _description; }

	public slots:
	    void accept();

	private:
	    void setName();
	    void setDescription();

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
    };
}

#endif // MNEWGALLERYDIALOG_H
