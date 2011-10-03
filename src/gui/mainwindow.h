#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>
#include <QFileSystemModel>

#include <core/mphoto.h>
#include <core/mdatabase.h>
#include <core/mgallery.h>

namespace gui
{
    class MainWindow : public QMainWindow
    {
	Q_OBJECT

	public:
	    MainWindow(QWidget* parent = 0);
	    ~MainWindow();

	signals:

	public slots:
	    void importPhoto();

	private:
	    void setupGui(QMainWindow* mainWindow);
	    void setupFileSystemView(QGridLayout* layout);
	    void setupMenu(QMainWindow* mainWindow);
	    void setupTabs(QGridLayout* layout);
	    void setupDetailsTab(QTabWidget* tab);
	    void setupProjectTab(QTabWidget* tab);

	    void enableGui(bool state);

	    // central widgets
	    QWidget* centralWidget;
	    QWidget* gridLayoutWidget;
	    QGridLayout* gridLayout;

	    // filesystem tree view
	    QFileSystemModel* fileSystemModel;
	    QTreeView* fileSystemView;
	    QPushButton* importButton;

	    QTabWidget* tabWidget;
	    QWidget* projectViewWidget;
	    QWidget* detailsWidget;

	    QPushButton* pushButton;
	    QPushButton* pushButton_2;	    


	    QTreeView* projectView;

	    QTableWidget* tableWidget;
	    QMenuBar* menuBar;
	    QMenu* menuProject;
	    QMenu* menuExport;
	    QMenu* menuView;
	    QMenu* menuHelp;
	    QMenu* menuImage;
	    QToolBar* mainToolBar;
	    QStatusBar* statusBar;

	    core::MDatabase* activeDatabase;
	    core::MGallery* activeGallery;
    };
}

#endif // MAINWINDOW_H
