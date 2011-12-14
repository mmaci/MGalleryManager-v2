#include "gui/mainwindow.h"
#include "gui/mgridwidget/mgridwidget.h"
#include "gui/mtreewidget/mtreewidget.h"
#include "gui/mtreewidget/mtreewidgetitem.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/MGridWidgetThumbnail.h"
#include "gui/mnewgallerydialog.h"
#include "core/mphoto.h"
#include "core/mproject.h"
#include "core/mxmlhandler.h"
#include <string>

gui::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    _project = new core::MProject();

    setupGui(this);
}

gui::MainWindow::~MainWindow()
{
    // delete the whole gui
    // delete filesystem view
    delete _fileSystemModel;
    delete _fileSystemView;
    delete _importButton;
    delete _createGalleryButton;
    // delete tabs
    // delete project tab
    delete _projectWidget;
    delete projectViewWidget;
    // delete details tab
    delete detailsWidget;
    delete _tabWidget;
    // delete menu
    delete _menuProject;
    delete menuExport;
    delete menuView;
    delete menuHelp;
    delete menuImage;
    delete _menuBar;

    delete _objectGridWidget;

    delete _removeButton;
    delete statusBar;

    // delete central, layout widgets
    delete _baseGrid;
    delete _baseGridWidget;
    delete _centralWidget;

}

// SETUP: core setup handler
void gui::MainWindow::setupGui(QMainWindow* mainWindow)
{
    if (mainWindow->objectName().isEmpty())
	mainWindow->setObjectName(QString::fromUtf8("MainWindow"));

    mainWindow->resize(1024, 768);

    _centralWidget = new QWidget(mainWindow);
	_centralWidget->setObjectName(QString::fromUtf8("_centralWidget"));

    _baseGridWidget = new QWidget(_centralWidget);	
	_baseGridWidget->setObjectName(QString::fromUtf8("_baseGridWidget"));
	_baseGridWidget->setGeometry(QRect(0, 0, 271, 561));

    _baseGrid = new QGridLayout(_baseGridWidget);	
	_baseGrid->setObjectName(QString::fromUtf8("_baseGrid"));
	_baseGrid->setMargin(1);

    setupMenu(mainWindow);
    setupFileSystemView(_baseGrid);
    setupTabs(_baseGrid);
    setupObjectGrid(_centralWidget);

    mainWindow->setCentralWidget(_centralWidget);

    statusBar = new QStatusBar(mainWindow);
	statusBar->setObjectName(QString::fromUtf8("statusBar"));
	mainWindow->setStatusBar(statusBar);

    mainWindow->setWindowTitle(QApplication::translate("MGallery", "MGallery", 0, QApplication::UnicodeUTF8));

    // at the beginning we disable all kinds of buttons, menus, ...
    // to enable them later on, when we create a project
    // enableGui(false);

} // ENDOF gui::MainWindow::setupGui(QMainWindow* mainWindow)

void gui::MainWindow::enableGui(bool state)
{
    _importButton->setEnabled(state);
}

void gui::MainWindow::setupObjectGrid(QWidget* parent)
{
    _objectGridWidget = new gui::MGridWidget(parent);
	_objectGridWidget->setAutoFillBackground(true);
	_objectGridWidget->setGeometry(QRect(272, 0, 753, 747));
}

// SETUP: sets menus
void gui::MainWindow::setupMenu(QMainWindow* mainWindow)
{
    _menuBar = new QMenuBar(mainWindow);
    _menuBar->setObjectName(QString::fromUtf8("_menuBar"));
    _menuBar->setGeometry(QRect(0, 0, 1024, 20));

    _menuProject = new QMenu(_menuBar);
	_menuProject->setObjectName(QString::fromUtf8("_menuProject"));
	_menuProject->setTitle(QApplication::translate("MainWindow", "Project", 0, QApplication::UnicodeUTF8));	

	// Actions
	// Save Project
	_menuBar->addAction(_menuProject->menuAction());
	_actionSave = new QAction(mainWindow);
	_actionSave->setText(QString("Save Project"));
	_actionSave->setDisabled(true);
	_menuProject->addAction(_actionSave);

	// Save Project As ..
	_actionSaveAs = new QAction(mainWindow);
	_actionSaveAs->setText(QString("Save Project as ..."));
	_menuProject->addAction(_actionSaveAs);
	_menuProject->addSeparator();

	// Load Project
	_actionLoad = new QAction(mainWindow);
	_actionLoad->setText(QString("Load Project"));
	_menuProject->addAction(_actionLoad);

    menuExport = new QMenu(_menuBar);
    menuExport->setObjectName(QString::fromUtf8("menuExport"));
    menuView = new QMenu(_menuBar);
    menuView->setObjectName(QString::fromUtf8("menuView"));
    menuHelp = new QMenu(_menuBar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    menuImage = new QMenu(_menuBar);
    menuImage->setObjectName(QString::fromUtf8("menuImage"));

    mainWindow->setMenuBar(_menuBar);

    _menuBar->addAction(_menuProject->menuAction());
    _menuBar->addAction(menuExport->menuAction());
    _menuBar->addAction(menuView->menuAction());
    _menuBar->addAction(menuImage->menuAction());
    _menuBar->addAction(menuHelp->menuAction());

    menuExport->setTitle(QApplication::translate("MainWindow", "Export", 0, QApplication::UnicodeUTF8));
    menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    menuImage->setTitle(QApplication::translate("MainWindow", "Image", 0, QApplication::UnicodeUTF8));

	/// Submenus
	_menuProject = new QMenu(_menuBar);
	_menuProject->setTitle(QString("Project")); ///< Title

    connect(_actionSaveAs, SIGNAL(triggered()), this, SLOT(saveAsDialog()));
    connect(_actionLoad, SIGNAL(triggered()), this, SLOT(load()));

    #ifdef DEBUG
    std::cout << "Menu created." << endl;
    #endif

} // ENDOF gui::MainWindow::setupMenu

void gui::MainWindow::saveAsDialog()
{
    core::MXMLHandler* xml = new core::MXMLHandler();

    xml->saveProjectAs(std::string("c:/atest/test.xml"), _project->base());

    delete xml;
}

void gui::MainWindow::load()
{
    core::MXMLHandler* xml = new core::MXMLHandler();

    QString fileName = QFileDialog::getOpenFileName(this, QString("Open Project"), QString(), tr("XML files (*.xml)"));

    core::MGallery* gallery = xml->loadProject(fileName.toStdString());
    _project->setBase(gallery);
    _projectWidget->loadGallery(gallery);

    delete xml;
}

// SETUP: sets file system view tree
void gui::MainWindow::setupFileSystemView(QGridLayout* layout)
{
    // init
    _fileSystemView = new QTreeView(_baseGridWidget);
    _fileSystemModel = new QFileSystemModel;
	_fileSystemModel->setRootPath(QDir::currentPath());

    // name filters
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.jpeg" << "*.png" << "*.tiff" << "*.tif";
    _fileSystemModel->setNameFilters(nameFilters);

    // connects Filesystem model to treeview and adds to layout
    _fileSystemView->setModel(_fileSystemModel);
    _fileSystemView->setSelectionMode(QAbstractItemView::MultiSelection);
    layout->addWidget(_fileSystemView, 0, 0);

    // import button
    _importButton = new QPushButton(_baseGridWidget);
	_importButton->setObjectName(QString::fromUtf8("importButton"));
	_importButton->setText(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
	layout->addWidget(_importButton, 1, 0);

    // set signals and slots
    // import button imports a photo
    connect(_importButton, SIGNAL(clicked()), this, SLOT(importPhotos()));    

} // ENDOF gui::MainWindow::setup_fileSystemView

void gui::MainWindow::refreshObjectGrid(QModelIndex index)
{
    // index isn't needed because when we double click on an item, we have it selected, so we just try to load the currently selected item
    // safechecks in load
    _objectGridWidget->load(_projectWidget->selected()->object());
}

void gui::MainWindow::removeItemFromProject()
{   
    if (core::MObject* object = _projectWidget->selected()->object())
    {
	// we don't want to delete gallery in case it contains photos
	// TODO: invoke a dialog
	if (core::MGallery* gallery = object->toGallery())
	{
	    if (!gallery->empty())
		return;
	}
	object->destroy();
    }
}

// ================ PHOTOS ================

/**
 * basic slot for importing multiple photos
 * passes on a reference to a list of selected items
 */
void gui::MainWindow::importPhotos()
{
    // selected list of files
    std::list<QModelIndex> selectedList = _fileSystemView->selectionModel()->selectedRows().toStdList();
    importPhotos(&selectedList); // reference is enough    
    _fileSystemView->clearSelection();
}

/**
 * handles multiple file import
 * @param list list of items to import, checks only for files
 */
void gui::MainWindow::importPhotos(std::list<QModelIndex>* list)
{
    gui::MTreeWidgetItem* parentItem =_projectWidget->selected();
    if (!parentItem) // must have a selected item
	return;

    core::MGallery* parent = parentItem->object()->toGallery();
    if (!parent) // selected item must be a gallery
	return;

    // import
    std::list<QModelIndex>::iterator it;
    for (it = list->begin(); it != list->end(); ++it)
    {
	QFileInfo fileInfo = _fileSystemModel->fileInfo(*it);

	// only add files
	if (fileInfo.isDir())
	    continue;
	// check to find duplicates
	if (parent->find(fileInfo))
	    continue;

	core::MPhotoInfo info(fileInfo);
	// if insert into core structures succeeds we may also create an entry in list
	// constructor called in insert(MPhotoInfo)
	if (core::MPhoto* photo = parent->insert(info))
	{
	    _projectWidget->insert(photo, parentItem);
	    _objectGridWidget->insert(photo);
	}
    }    
}

// ================ GALLERIES ================

/**
 * basic slot for creating galleries
 * invokes a dialog window and sends its content
 */
void gui::MainWindow::createGallery()
{
    gui::MNewGalleryDialog dialog(this);

    if (dialog.exec())
	createGallery(dialog.name(), dialog.description());
}

/**
 * calls gallery creation handlers on both the gui and the core level 
 * @param name gallery name from input dialog
 */
void gui::MainWindow::createGallery(std::string name, std::string description)
{
    if (name.empty())
	return;

    core::MGalleryInfo info(name, description);
    // we have a selected gallery
    if (gui::MTreeWidgetItem* parentItem = _projectWidget->selected())
    {
	// selected object can be a photo or a gallery, we must ensure it's a gallery
	if (core::MGallery* parent = parentItem->object()->toGallery())
	{
	    // calls a constructor of a new gallery based on its info
	    if (core::MGallery* gallery = parent->insert(info))
	    {
		if (gui::MTreeWidgetItem* item = _projectWidget->insert(gallery, parentItem))
		    gallery->setTreeWidgetItem(item);
	    }
	}
    }
    // no gallery selected, create gallery on the base level
    else
    {
	core::MGallery* gallery = new core::MGallery(info);

	if (gui::MTreeWidgetItem* item = _projectWidget->insert(gallery))
	    gallery->setTreeWidgetItem(item);

	_project->insert(gallery);
    }
}

// SETUP: sets tabs
void gui::MainWindow::setupTabs(QGridLayout* layout)
{
    _tabWidget = new QTabWidget(_baseGridWidget);
    _tabWidget->setObjectName(QString::fromUtf8("_tabWidget"));

    setupProjectTab(_tabWidget);
    setupDetailsTab(_tabWidget);

    _removeButton = new QPushButton(_baseGridWidget);
    _removeButton->setObjectName(QString::fromUtf8("removeButton"));
    _removeButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));

    layout->addWidget(_tabWidget, 2, 0);
    layout->addWidget(_removeButton, 3, 0);

    _createGalleryButton = new QPushButton(_baseGridWidget);
    _createGalleryButton->setObjectName(QString::fromUtf8("removeButton"));
    _createGalleryButton->setText(QApplication::translate("MainWindow", "Create Gallery", 0, QApplication::UnicodeUTF8));
    layout->addWidget(_createGalleryButton, 4, 0);

    _tabWidget->setCurrentIndex(0); // makes Project Tab active

    connect(_removeButton, SIGNAL(clicked()), this, SLOT(removeItemFromProject()));
    connect(_createGalleryButton, SIGNAL(clicked()), this, SLOT(createGallery()));

} // ENDOF gui::MainWindow::setupTabs

void gui::MainWindow::setupProjectTab(QTabWidget* tab)
{
    projectViewWidget = new QWidget();
	projectViewWidget->setObjectName(QString::fromUtf8("projectViewWidget"));

    _projectWidget = new gui::MTreeWidget(projectViewWidget);
	_projectWidget->setObjectName(QString::fromUtf8("projectWidget"));
	_projectWidget->setGeometry(QRect(0, 0, 261, 221));
	_projectWidget->setColumnCount(1);

    tab->addTab(projectViewWidget, QString());
    tab->setTabText(tab->indexOf(projectViewWidget), QApplication::translate("MainWindow", "Project", 0, QApplication::UnicodeUTF8));

    connect(_projectWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(refreshObjectGrid(QModelIndex)));
} // ENDOF gui::MainWindow::setupProjectTab

void gui::MainWindow::setupDetailsTab(QTabWidget* tab)
{
    detailsWidget = new QWidget();
	detailsWidget->setObjectName(QString::fromUtf8("detailsWidget"));

    tab->addTab(detailsWidget, QString());
    tab->setTabText(tab->indexOf(detailsWidget), QApplication::translate("MainWindow", "Details", 0, QApplication::UnicodeUTF8));
} // ENDOF gui::MainWindow::setupDetailsTab
