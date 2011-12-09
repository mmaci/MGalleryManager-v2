#ifndef MRESIZEDIALOG_H
#define MRESIZEDIALOG_H

#include <string>
#include <QIntValidator>

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

namespace gui
{
    class MResizeDialog : public QDialog
    {
	public:
	    MResizeDialog(QWidget* parent = NULL);

	    int getWidth(){ return _width; }
	    int getHeight(){ return _height; }

	public slots:
	    void accept();

	private:
	    void setWidth();
	    void setHeight();

	    int _width;
	    int _height;

	    QLineEdit* _widthEdit;
	    QLineEdit* _heightEdit;
	    QPushButton* _okButton;
	    QPushButton* _cancelButton;
	    QLabel* _widthLabel;
	    QLabel* _heightLabel;
	    QGridLayout* _buttonLayout;
	    QGridLayout* _textLayout;
	    QWidget* _buttonWidget;
	    QWidget* _textWidget;
    };
} // NAMESPACE gui

#endif // MRESIZEDIALOG_H
