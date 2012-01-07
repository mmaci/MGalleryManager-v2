#ifndef MRESIZEDIALOG_H
#define MRESIZEDIALOG_H

#include <string>
#include <memory>
#include <QIntValidator>

#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QCheckBox>

namespace mgui
{
    class MResizeDialog : public QDialog
    {
	Q_OBJECT

	public:
	    MResizeDialog(int width = 0, int height = 0, QWidget* parent = NULL);

	    int getWidth(){ return _width; }
	    int getHeight(){ return _height; }

	public slots:
	    void accept();
	    void recalculateWidth(QString newText);
	    void recalculateHeight(QString newText);

	private:
	    void setWidth();
	    void setHeight();

	    int _width;
	    int _height;
	    double _prop;

	    QLineEdit* _widthEdit;
	    QLineEdit* _heightEdit;
	    QCheckBox* _propCheckbox;
	    QPushButton* _okButton;
	    QPushButton* _cancelButton;
	    QLabel* _widthLabel;
	    QLabel* _heightLabel;
	    QLabel* _propLabel;
	    QGridLayout* _buttonLayout;
	    QGridLayout* _textLayout;
	    QWidget* _buttonWidget;
	    QWidget* _textWidget;
    };
} // NAMESPACE gui

#endif // MRESIZEDIALOG_H
