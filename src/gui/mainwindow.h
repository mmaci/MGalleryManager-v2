#define _DEBUG
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include <QMainWindow>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGridLayout>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTabWidget>
#include <QTableWidget>
#include <QToolBar>
#include <QTreeView>
#include <QTreeWidget>
#include <QWidget>
#include <QFileSystemModel>
#include <QInputDialog>
#include <QErrorMessage>
#include <QFileDialog>

namespace core
{
    class MProject;
}

namespace gui
{
    class MGridWidget;
    class MTreeWidget;
    class MNewGalleryDialog;
    class MainWindow : public QMainWindow
    {
	Q_OBJECT

	public:
	    MainWindow(QWidget* parent = 0);
	    ~MainWindow();

	    void createGallery(std::string name, std::string description = "");
	    void importPhotos(std::list<QModelIndex>* list);

	signals:

	public slots:
	    void importPhotos();	    	    
	    void removeItemFromProject();	    
	    void createGallery();
	    void refreshObjectGrid(QModelIndex index);

	    void saveAsDialog();
	    void load();

	private:
	    void setupGui(QMainWindow* mainWindow);
	    void setupFileSystemView(QGridLayout* layout);
	    void setupMenu(QMainWindow* mainWindow);
	    void setupTabs(QGridLayout* layout);
	    void setupDetailsTab(QTabWidget* tab);
	    void setupProjectTab(QTabWidget* tab);
	    void setupObjectGrid(QWidget* parent);

	    void enableGui(bool state);

	    // layout
	    QWidget*		_centralWidget;
	    QWidget*		_baseGridWidget;
	    QGridLayout*	_baseGrid;

	    // central window
	    MGridWidget*	_objectGridWidget;
	    QGridLayout*	_objectGrid;

	    // filesystem tree view
	    QFileSystemModel*	_fileSystemModel;
	    QTreeView*		_fileSystemView;
	    QPushButton*	_importButton;
	    QPushButton*	_createGalleryButton;

	    QTabWidget*		_tabWidget;
	    QWidget* projectViewWidget;
	    QWidget* detailsWidget;

	    QPushButton* pushButton;
	    QPushButton*	_removeButton;

	    MTreeWidget*	_projectWidget;

	    QMenuBar*		_menuBar;
	    QMenu*		_menuProject;
	    QAction*		_actionSave;
	    QAction*		_actionSaveAs;
	    QAction*		_actionLoad;

	    QWidget* tableWidget;

	    QMenu* menuExport;
	    QMenu* menuView;
	    QMenu* menuHelp;
	    QMenu* menuImage;

	    QStatusBar* statusBar;

	    core::MProject*	_project;
    };

} // NAMESPACE gui

#endif // MAINWINDOW_H
