#include "gui/mainwindow.h"

gui::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    _database = new core::MDatabase();

    setupGui(this);
}

gui::MainWindow::~MainWindow()
{
    // delete the whole gui
    // delete filesystem view
    delete fileSystemModel;
    delete fileSystemView;
    delete _importButton;
    delete _createGalleryButton;
    // delete tabs
    // delete project tab
    delete _projectWidget;
    delete projectViewWidget;
    // delete details tab
    delete detailsWidget;
    delete tabWidget;
    // delete menu
    delete menuProject;
    delete menuExport;
    delete menuView;
    delete menuHelp;
    delete menuImage;
    delete menuBar;

    delete _removeButton;
    delete statusBar;
    delete mainToolBar;

    // delete central, layout widgets
    delete tableWidget;
    delete gridLayout;
    delete gridLayoutWidget;
    delete centralWidget;
}

// SETUP: core setup handler
void gui::MainWindow::setupGui(QMainWindow* mainWindow)
{
    if (mainWindow->objectName().isEmpty())
	mainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    mainWindow->resize(1035, 650);
    centralWidget = new QWidget(mainWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    gridLayoutWidget = new QWidget(centralWidget);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(10, 20, 271, 561));
    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);

    setupMenu(mainWindow);
    setupFileSystemView(gridLayout);
    setupTabs(gridLayout);

    tableWidget = new QTableWidget(centralWidget);
    tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
    tableWidget->setGeometry(QRect(290, 20, 731, 561));
    mainWindow->setCentralWidget(centralWidget);

    mainToolBar = new QToolBar(mainWindow);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    mainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(mainWindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    mainWindow->setStatusBar(statusBar);



    mainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));

    // at the beginning we disable all kinds of buttons, menus, ...
    // to enable them later on, when we create a project
    // enableGui(false);
} // ENDOF gui::MainWindow::setupGui(QMainWindow* mainWindow)

void gui::MainWindow::enableGui(bool state)
{
    _importButton->setEnabled(state);
}

// SETUP: sets menus
void gui::MainWindow::setupMenu(QMainWindow* mainWindow)
{
    menuBar = new QMenuBar(mainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 1035, 21));
    menuProject = new QMenu(menuBar);
    menuProject->setObjectName(QString::fromUtf8("menuProject"));
    menuExport = new QMenu(menuBar);
    menuExport->setObjectName(QString::fromUtf8("menuExport"));
    menuView = new QMenu(menuBar);
    menuView->setObjectName(QString::fromUtf8("menuView"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    menuImage = new QMenu(menuBar);
    menuImage->setObjectName(QString::fromUtf8("menuImage"));

    mainWindow->setMenuBar(menuBar);

    menuBar->addAction(menuProject->menuAction());
    menuBar->addAction(menuExport->menuAction());
    menuBar->addAction(menuView->menuAction());
    menuBar->addAction(menuImage->menuAction());
    menuBar->addAction(menuHelp->menuAction());

    menuProject->setTitle(QApplication::translate("MainWindow", "Project", 0, QApplication::UnicodeUTF8));
    menuExport->setTitle(QApplication::translate("MainWindow", "Export", 0, QApplication::UnicodeUTF8));
    menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
    menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    menuImage->setTitle(QApplication::translate("MainWindow", "Image", 0, QApplication::UnicodeUTF8));
} // ENDOF gui::MainWindow::setupMenu

// SETUP: sets file system view tree
void gui::MainWindow::setupFileSystemView(QGridLayout* layout)
{
    // init
    fileSystemView = new QTreeView(gridLayoutWidget);
    fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath(QDir::currentPath());

    // name filters
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.jpeg" << "*.png" << "*.tiff" << "*.tif";
    fileSystemModel->setNameFilters(nameFilters);

    // connects Filesystem model to treeview and adds to layout
    fileSystemView->setModel(fileSystemModel);
    fileSystemView->setSelectionMode(QAbstractItemView::MultiSelection);
    layout->addWidget(fileSystemView, 2, 0, 1, 1);

    // import button
    _importButton = new QPushButton(gridLayoutWidget);
    _importButton->setObjectName(QString::fromUtf8("importButton"));
    _importButton->setText(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
    layout->addWidget(_importButton, 3, 0, 1, 1);

    // set signals and slots
    // import button imports a photo
    connect(_importButton, SIGNAL(clicked()), this, SLOT(importPhotos()));

} // ENDOF gui::MainWindow::setupFileSystemView

void gui::MainWindow::selectFileInView(const QModelIndex& index)
{
}


void gui::MainWindow::removeItemFromProject()
{   
    _projectWidget->remove(); // removes currently selected item
}

// ================ PHOTOS ================

/**
 * basic slot for importing multiple photos
 * passes on a reference to a list of selected items
 */
void gui::MainWindow::importPhotos()
{
    // selected list of files
    std::list<QModelIndex> selectedList = fileSystemView->selectionModel()->selectedRows().toStdList();
    importPhotos(&selectedList); // reference is enough
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
	QFileInfo fileInfo = fileSystemModel->fileInfo(*it);

	// only add files
	if (fileInfo.isDir())
	    continue;
	// check to find duplicates
	if (_database->find(fileInfo))
	    continue;

	core::MPhotoInfo info(fileInfo);
	// if insert into core structures succeeds we may also create an entry in list
	// constructor called in insert(MPhotoInfo)
	if (core::MPhoto* photo = parent->insert(info))
	    _projectWidget->insert(photo, parentItem);
    }
}

// ================ GALLERIES ================

/**
 * basic slot for creating galleries
 * invokes a dialog window and sends its content
 */
void gui::MainWindow::createGallery()
{
    // reads an input dialog
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("User name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);

    // input text handling
    if (ok)
	createGallery(text.toStdString());
}

/**
 * calls gallery creation handlers on both the gui and the core level
 * must have a selected gallery otherwise it ends here
 * @param name gallery name from input dialog
 */
void gui::MainWindow::createGallery(std::string name)
{
    core::MGalleryInfo info(name);
    // we have a selected gallery
    if (gui::MTreeWidgetItem* parentItem =_projectWidget->selected())
    {
	// selected object can be a photo or a gallery, we must ensure it's a gallery
	if (core::MGallery* parent = parentItem->object()->toGallery())
	{
	    // calls a constructor of a new gallery based on its info
	    if (core::MGallery* gallery = parent->insert(info))
		_projectWidget->insert(gallery, parentItem);
	}
    }
    // no gallery selected, create gallery on the base level
    else
    {
	core::MGallery* gallery = new core::MGallery(info);
	_database->insert(gallery);
	_projectWidget->insert(gallery);
    }
}

// SETUP: sets tabs
void gui::MainWindow::setupTabs(QGridLayout* layout)
{
    tabWidget = new QTabWidget(gridLayoutWidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

    setupProjectTab(tabWidget);
    setupDetailsTab(tabWidget);

    _removeButton = new QPushButton(gridLayoutWidget);
    _removeButton->setObjectName(QString::fromUtf8("removeButton"));
    _removeButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));

    layout->addWidget(tabWidget, 4, 0, 1, 1);
    layout->addWidget(_removeButton, 5, 0, 1, 1);

    _createGalleryButton = new QPushButton(gridLayoutWidget);
    _createGalleryButton->setObjectName(QString::fromUtf8("removeButton"));
    _createGalleryButton->setText(QApplication::translate("MainWindow", "Create Gallery", 0, QApplication::UnicodeUTF8));
    layout->addWidget(_createGalleryButton, 6, 0, 1, 1);

    tabWidget->setCurrentIndex(0); // makes Project Tab active

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
} // ENDOF gui::MainWindow::setupProjectTab

void gui::MainWindow::setupDetailsTab(QTabWidget* tab)
{
    detailsWidget = new QWidget();
    detailsWidget->setObjectName(QString::fromUtf8("detailsWidget"));

    tab->addTab(detailsWidget, QString());
    tab->setTabText(tab->indexOf(detailsWidget), QApplication::translate("MainWindow", "Details", 0, QApplication::UnicodeUTF8));
} // ENDOF gui::MainWindow::setupDetailsTab
