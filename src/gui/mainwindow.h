#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <string>

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
#include <QInputDialog>

#include <core/mdatabase.h>
#include <core/mgallery.h>
#include <gui/mtreewidget.h>

namespace gui
{
    class MainWindow : public QMainWindow
    {
	Q_OBJECT

	public:
	    MainWindow(QWidget* parent = 0);
	    ~MainWindow();

	    void createGallery(std::string name);
	    void importPhotos(std::list<QModelIndex>* list);

	signals:

	public slots:
	    void importPhotos();	    	    
	    void removeItemFromProject();	    
	    void createGallery();

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
	    QPushButton* _importButton;
	    QPushButton* _createGalleryButton;

	    QTabWidget* tabWidget;
	    QWidget* projectViewWidget;
	    QWidget* detailsWidget;

	    QPushButton* pushButton;
	    QPushButton* _removeButton;


	    MTreeWidget* _projectWidget;

	    QTableWidget* tableWidget;
	    QMenuBar* menuBar;
	    QMenu* menuProject;
	    QMenu* menuExport;
	    QMenu* menuView;
	    QMenu* menuHelp;
	    QMenu* menuImage;
	    QToolBar* mainToolBar;
	    QStatusBar* statusBar;

	    core::MDatabase* _database;
    };
}

#endif // MAINWINDOW_H
