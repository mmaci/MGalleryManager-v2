#include "gui/mainwindow.h"
#include "gui/mgridwidget/mgridwidget.h"
#include "gui/mtreewidget/mtreewidget.h"
#include "gui/mtreewidget/mtreewidgetitem.h"
#include "gui/mgridwidget/mgridwidgetitem.h"
#include "gui/mgridwidget/MGridWidgetThumbnail.h"
#include "gui/mnewobjectdialog.h"
#include "core/mphoto.h"
#include "core/mproject.h"
#include "core/mxmlhandler.h"
#include <string>

namespace mgui
{

/**
 * \brief constructor
 * a constructor called when opening the main window
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    _project = new mcore::MProject();

    setupGui(this);
}

/**
 * \brief destructor
 * a destructor called when closing the main window
 */
MainWindow::~MainWindow()
{
    // i plan to convert this to C++0x standard in the future
    // so it could be dropped and smart ptrs can be used, it looks really ugly

    // delete menu
    //
    // actions
    delete _actionSave;
    delete _actionSaveAs;
    delete _actionLoad;
    delete _actionAsHTML;
    // bars
    delete _menuProject;
    delete _menuExport;
    delete _menuHelp;
    delete _menuBar;

    // delete buttons
    //
    delete _importButton;
    delete _createGalleryButton;
    delete _removeButton;
    // delete filesystem view
    //
    delete _fileSystemModel;
    delete _fileSystemView;    
    // delete tabs
    //
    delete _projectWidget;
    delete _projectViewWidget;
    delete _tabWidget;
    // delete details
    //
    delete _detailsWidget;   
    // delete object grid (central part)
    //
    delete _objectGridWidget;            

    // delete layouts
    //
    delete _baseGrid;
    delete _baseGridWidget;
    delete _centralWidget;

    // and finally the project
    //
    delete _project;
}

////////////////////////////////////////////////////////////////
// Setups
////////////////////////////////////////////////////////////////

/**
 * \brief sets up the whole gui
 * calls setup handlers for all the proper parts of gui
 */
void MainWindow::setupGui(QMainWindow* mainWindow)
{    
    mainWindow->resize(1024, 768);

    _centralWidget = new QWidget(mainWindow);	

    _baseGridWidget = new QWidget(_centralWidget);		
	_baseGridWidget->setGeometry(QRect(0, 0, 271, 721));

    _baseGrid = new QGridLayout(_baseGridWidget);	
	_baseGrid->setMargin(1);

    setupMenu(mainWindow);
    setupFileSystemView(_baseGrid);
    setupTabs(_baseGrid);
    setupDetails(_baseGrid);
    setupObjectGrid(_centralWidget);

    mainWindow->setCentralWidget(_centralWidget);
    mainWindow->setWindowTitle(QString("GalleryManager - version beta0.1"));

    // TODO: check enabling and disabling gui features based on what we are able to use and implement them

} // ENDOF MainWindow::setupGui(QMainWindow* mainWindow)

/**
 * \brief sets up object grid
 * this is the part of gui which displays thumbnails and the image editor
 */
void MainWindow::setupObjectGrid(QWidget* parent)
{
    _objectGridWidget = new MGridWidget(parent);
	_objectGridWidget->setAutoFillBackground(true);
	_objectGridWidget->setGeometry(QRect(272, 0, 753, 747));
}

/**
 * \brief sets up menus
 */
void MainWindow::setupMenu(QMainWindow* mainWindow)
{
    _menuBar = new QMenuBar(mainWindow);    
    _menuBar->setGeometry(QRect(0, 0, 1024, 20));

    // Project
    _menuProject = new QMenu(_menuBar);	
	_menuProject->setTitle(QString("Project"));
	_menuBar->addAction(_menuProject->menuAction());

	// Actions
	// Save Project
	_actionSave = new QAction(mainWindow);
	_actionSave->setText(QString("Save Project"));
	_menuProject->addAction(_actionSave);

	// Save Project As ..
	_actionSaveAs = new QAction(mainWindow);
	_actionSaveAs->setText(QString("Save Project As ..."));
	_menuProject->addAction(_actionSaveAs);
	_menuProject->addSeparator();

	// Load Project
	_actionLoad = new QAction(mainWindow);
	_actionLoad->setText(QString("Load Project"));
	_menuProject->addAction(_actionLoad);	

    // Export
    _menuExport = new QMenu(_menuBar);
	_menuExport->setTitle(QString("Export"));
	_menuBar->addAction(_menuExport->menuAction());

	// Actions
	// As HTML ...
	_actionAsHTML = new QAction(mainWindow);
	_actionAsHTML->setText(QString("As HTML ..."));
	_menuExport->addAction(_actionAsHTML);

    // Help
    _menuHelp = new QMenu(_menuBar);
	_menuHelp->setTitle(QString("Help"));
	_menuBar->addAction(_menuHelp->menuAction());

    mainWindow->setMenuBar(_menuBar);

    connect(_actionSaveAs, SIGNAL(triggered()), this, SLOT(handleSaveAs()));
    connect(_actionSave, SIGNAL(triggered()), this, SLOT(handleSave()));
    connect(_actionLoad, SIGNAL(triggered()), this, SLOT(handleLoad()));
    connect(_actionAsHTML, SIGNAL(triggered()), this, SLOT(handleAsHTML()));

} // ENDOF MainWindow::setupMenu

/**
 * \brief sets up FileSystemView
 * this is the part of gui which displays the filesystem (used for importing)
 */
void MainWindow::setupFileSystemView(QGridLayout* layout)
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
    _fileSystemView->setColumnWidth(0, 200);

    // import button
    _importButton = new QPushButton(_baseGridWidget);
	_importButton->setText(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
	layout->addWidget(_importButton, 1, 0);

    // set signals and slots
    // import button imports a photo
    connect(_importButton, SIGNAL(clicked()), this, SLOT(importPhotos()));

} // ENDOF MainWindow::setupFileSystemView

/**
 * \brief sets up tabs
 * used to display more tabs, which looked confusing
 * atm it sets up the part where we display project content
 */
void MainWindow::setupTabs(QGridLayout* layout)
{
    _tabWidget = new QTabWidget(_baseGridWidget);

    setupProjectTab(_tabWidget);

    _removeButton = new QPushButton(_baseGridWidget);
    _removeButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));

    layout->addWidget(_tabWidget, 2, 0);
    layout->addWidget(_removeButton, 3, 0);

    _createGalleryButton = new QPushButton(_baseGridWidget);
    _createGalleryButton->setText(QString("Create Gallery"));
    layout->addWidget(_createGalleryButton, 4, 0);

    _tabWidget->setCurrentIndex(0); // makes Project Tab active

    connect(_removeButton, SIGNAL(clicked()), this, SLOT(removeItemFromProject()));
    connect(_createGalleryButton, SIGNAL(clicked()), this, SLOT(createGallery()));

} // ENDOF MainWindow::setupTabs

/**
 * \brief sets up the project view
 * sets up the view of the project
 */
void MainWindow::setupProjectTab(QTabWidget* tab)
{
    _projectViewWidget = new QWidget();
	_projectViewWidget->resize(263, 180);

    _projectWidget = new MTreeWidget(_projectViewWidget);
	_projectWidget->setHeaderLabel(QString("Content"));
	_projectWidget->resize(_projectViewWidget->size());
	_projectWidget->setColumnCount(1);

    tab->addTab(_projectViewWidget, QString());
    tab->setTabText(tab->indexOf(_projectViewWidget), QString("Project"));

    connect(_projectWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(refreshObjectGrid(QModelIndex)));
} // ENDOF MainWindow::setupProjectTab

/**
 * \brief sets up details
 * atm just exif data is displayed here (if available)
 */
void MainWindow::setupDetails(QGridLayout* layout)
{
    _detailsWidget = new QTableWidget(_baseGridWidget);
	_detailsWidget->resize(261, 200);
	_detailsWidget->setColumnCount(2);

    QStringList headers;
	headers << "EXIF" << "value";

    _detailsWidget->setHorizontalHeaderLabels(headers);
    _detailsWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
    _detailsWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    layout->addWidget(_detailsWidget, 5, 0);
} // ENDOF MainWindow::setupDetails

////////////////////////////////////////////////////////////////
// Slots
////////////////////////////////////////////////////////////////

/**
 * \brief Save As ... slot
 * called when Project -> Save As ... is pressed
 */
void MainWindow::handleSaveAs()
{    
    QString fileName = QFileDialog::getSaveFileName(this, QString("Save Project"), QString(), tr("XML files (*.xml)"));
    if (!fileName.isEmpty())
    {
	mcore::MXMLHandler* xml = new mcore::MXMLHandler();
	xml->saveProjectAs(fileName.toStdString(), _project->base());
	_project->setPath(fileName.toStdString());
	delete xml;
    }
}

/**
 * \brief Save slot
 * called when Project -> Save is pressed
 */
void MainWindow::handleSave()
{
    if (!_project->path().empty())
    {
	mcore::MXMLHandler* xml = new mcore::MXMLHandler();
	xml->saveProjectAs(_project->path(), _project->base());
	delete xml;
    }
    else
	handleSaveAs();
}

/**
 * \brief Load slot
 * called when Project -> Load is pressed
 */
void MainWindow::handleLoad()
{    
    QString fileName = QFileDialog::getOpenFileName(this, QString("Open Project"), QString(), tr("XML files (*.xml)"));
    if (!fileName.isEmpty())
    {
	mcore::MXMLHandler* xml = new mcore::MXMLHandler();
	if (mcore::MGallery* gallery = xml->loadProject(fileName.toStdString()))
	{
	    // we clear all widgets
	    _objectGridWidget->hideAllItems();
	    _projectWidget->clear();

	    _project->setBase(gallery); // also delete previous project
	    _project->setPath(fileName.toStdString());

	    _projectWidget->loadGallery(gallery);	    
	}
	delete xml;
    }
}

/**
 * \brief As HTML ... slot
 * called when Export -> As HTML ... is pressed
 */
void MainWindow::handleAsHTML()
{
    if (!_project->base())
	return;

    QString folder = QFileDialog::getExistingDirectory(this, QString("Export As HTML ..."), QString());
    if (!folder.isEmpty())
    {
	mcore::MHTMLExport* ex = new mcore::MHTMLExport();
	    ex->exportHTML(_project->base()->toObject(), folder.toStdString().append("\\"), true);
    }
}

/**
 * \brief refreshes object grid
 * refreshes the part of gui, where we display for example thumbnails
 * called when we click on an object inside the tree view of the project
 */
void MainWindow::refreshObjectGrid(QModelIndex index)
{
    typedef std::pair<QTableWidgetItem*, QTableWidgetItem*> QTableWidgetItemPair;

    // index isn't needed because when we double click on an item, we have it selected, so we just try to load the currently selected item    
    if (!_projectWidget->selected())
	return;

    mcore::MObject* object = _projectWidget->selected()->object();
    _objectGridWidget->load(object);

    // we also need to set proper exif info
    // clears old table, calls destructors
    _detailsWidget->clearContents();
    // only when a photo is active
    if (mcore::MPhoto* photo = object->toPhoto())
    {
	mcore::MPhotoInfo* info = photo->info();
	std::vector<QTableWidgetItemPair> items;
	for (int i = 0; i < MAX_EXIF_DATA; ++i)
	{
	    std::string data = info->getExif(i);
	    // gets processed only if we have data saved
	    if (data == "")
		continue;

	    QTableWidgetItem* value = new QTableWidgetItem(QString(data.c_str()));
	    QTableWidgetItem* label;
	    switch (i)
	    {
		case EXIF_ISO:
		    label = new QTableWidgetItem(QString("ISO"));
		    break;

		case EXIF_EXPOSURE_TIME:
		    label = new QTableWidgetItem(QString("Exposure Time"));
		    break;

		case EXIF_CAMERA:
		    label = new QTableWidgetItem(QString("Camera"));
		    break;

		case EXIF_FNUMBER:
		    label = new QTableWidgetItem(QString("F-number"));
		    break;

		case EXIF_FOCAL_LENGTH:
		    label = new QTableWidgetItem(QString("Focal Length"));
		    break;
	    }
	    items.push_back(std::make_pair(label, value));
	}

	// first we create a list of items
	// then based on the list size we resize the widget and create items
	if (items.size())
	{
	    _detailsWidget->setRowCount(items.size());
	    std::vector<QTableWidgetItemPair>::iterator it;
	    int i = 0;
	    for (it = items.begin(); it != items.end(); ++it, ++i)
	    {
		_detailsWidget->setItem(i, 0, (*it).first);
		_detailsWidget->setItem(i, 1, (*it).second);
	    }
	    _detailsWidget->sortByColumn(0, Qt::AscendingOrder);
	}
	// no exif data
	else
	{
	    QTableWidgetItem* item = new QTableWidgetItem(QString("No EXIF data."));
	    _detailsWidget->setItem(0, 0, item);
	}
    }
}

/**
 * \brief removes an item from the project
 * deletes only empty galleries and photos
 */
void MainWindow::removeItemFromProject()
{   
    if (mcore::MObject* object = _projectWidget->selected()->object())
    {
	// we don't want to delete gallery in case it contains photos
	// TODO: invoke a dialog allowing to drop everything
	if (mcore::MGallery* gallery = object->toGallery())	
	    if (!gallery->empty())
		return;

	object->destroy();
    }
    refreshObjectGrid(QModelIndex());
}

/**
 * basic slot for importing multiple photos
 * passes on a reference to a list of selected items
 */
void MainWindow::importPhotos()
{
    // selected list of files
    QModelIndexList selectedList = _fileSystemView->selectionModel()->selectedRows();
    QModelIndexList::const_iterator it;
    std::list<MImportStruct> list;

    // name and describe all the photos
    for (it = selectedList.begin(); it != selectedList.end(); ++it)
    {
	// do not display selected directories
	QFileInfo fileInfo = _fileSystemModel->fileInfo(*it);
	if (fileInfo.isDir())
	    continue;

	// only files
	MNewObjectDialog dialog(fileInfo.absoluteFilePath(), this, fileInfo.fileName());
	if (dialog.exec())
	{
	    if (dialog.name().empty())
	    {
		QErrorMessage message(this);
		message.showMessage(QString("A name must be specified. Photo not imported."));
		message.exec();
		continue;
	    }

	    MImportInfo info = MakeImportInfo(dialog.name(), dialog.description());
	    MImportStruct import = MakeImportStruct(*it, info);
	    list.push_back(import);
	}
    }

    importPhotos(&list); // reference is enough
    _fileSystemView->clearSelection();    
}

/**
 * handles multiple file import
 * \param list list of items to import, checks only for files
 */
void MainWindow::importPhotos(std::list<MImportStruct>* list)
{
    MTreeWidgetItem* parentItem = _projectWidget->selected();
    if (!parentItem) // must have a selected item
	return;

    mcore::MGallery* parent = parentItem->object()->toGallery();
    if (!parent) // selected item must be a gallery
	return;

    // import
    std::list<MImportStruct>::iterator it;
    for (it = list->begin(); it != list->end(); ++it)
    {
	QFileInfo fileInfo = _fileSystemModel->fileInfo(it->first);

	// only add files
	if (fileInfo.isDir())
	    continue;
	// check to find duplicates
	if (parent->find(fileInfo))
	    continue;

	mcore::MPhotoInfo info(fileInfo);
	    info.setName(it->second.first);
	    info.setDescription(it->second.second);

	// if insert into core structures succeeds we may also create an entry in list
	// constructor called in insert(MPhotoInfo)
	if (mcore::MPhoto* photo = parent->insert(info))
	{
	    _projectWidget->insert(photo, parentItem);
	    _objectGridWidget->insert(photo);
	}
    }
}


/**
 * basic slot for creating galleries
 * invokes a dialog window and sends its content
 */
void MainWindow::createGallery()
{
    MNewObjectDialog dialog(this);

    if (dialog.exec())
	createGallery(dialog.name(), dialog.description());
}

/**
 * calls gallery creation handlers on both the gui and the core level 
 * \param name gallery name from input dialog
 */
void MainWindow::createGallery(std::string name, std::string description)
{
    if (name.empty())
    {
	QErrorMessage message(this);
	message.showMessage(QString("Empty name. No gallery created."));
	message.exec();
	return;
    }

    mcore::MGalleryInfo info(name, description);
    // we have a selected gallery
    if (MTreeWidgetItem* parentItem = _projectWidget->selected())
    {
	// selected object can be a photo or a gallery, we must ensure it's a gallery
	if (mcore::MGallery* parent = parentItem->object()->toGallery())
	{
	    // calls a constructor of a new gallery based on its info
	    if (mcore::MGallery* gallery = parent->insert(info))
	    {
		if (MTreeWidgetItem* item = _projectWidget->insert(gallery, parentItem))
		    gallery->setTreeWidgetItem(item);
	    }
	}
    }
    // no gallery selected, create gallery on the base level
    else
    {
	mcore::MGallery* gallery = new mcore::MGallery(info);

	if (MTreeWidgetItem* item = _projectWidget->insert(gallery))
	    gallery->setTreeWidgetItem(item);

	_project->insert(gallery);
    }
}

} // NAMESPACE gui
