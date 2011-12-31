#define _DEBUG
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <vector>

#include <QHeaderView>
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
#include <QTableWidget>

#include "core/mhtmlexport.h"

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

	    void handleSave();
	    void handleSaveAs();
	    void handleLoad();
	    void handleAsHTML();

	private:
	    void setupGui(QMainWindow* mainWindow);
	    void setupFileSystemView(QGridLayout* layout);
	    void setupMenu(QMainWindow* mainWindow);
	    void setupTabs(QGridLayout* layout);
	    void setupDetails(QGridLayout* layout);
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
	    QWidget*		_projectViewWidget;
	    MTreeWidget*	_projectWidget;
	    QTableWidget*	_detailsWidget;

	    QPushButton*	_removeButton;

	    QMenuBar*		_menuBar;
	    QMenu*		_menuProject;
	    QMenu*		_menuExport;
	    QMenu*		_menuHelp;
	    QAction*		_actionSave;
	    QAction*		_actionSaveAs;
	    QAction*		_actionLoad;
	    QAction*		_actionAsHTML;

	    core::MProject*	_project;
    };

} // NAMESPACE gui

#endif // MAINWINDOW_H
