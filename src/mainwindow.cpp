#include "mainwindow.h"

GUI::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupGUI(this);
}

GUI::MainWindow::~MainWindow()
{
    // delete the whole GUI
    // delete filesystem view
    delete fileSystemView;
    delete importButton;
    // delete tabs
    // delete project tab
    delete projectView;
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

    delete pushButton_2;
    delete statusBar;
    delete mainToolBar;

    // delete central, layout widgets
    delete tableWidget;
    delete gridLayout;
    delete gridLayoutWidget;
    delete centralWidget;
}

// SETUP: core setup handler
void GUI::MainWindow::setupGUI(QMainWindow* mainWindow)
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


    QMetaObject::connectSlotsByName(mainWindow);
} // setupGUI

// SETUP: sets menus
void GUI::MainWindow::setupMenu(QMainWindow* mainWindow)
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
} // ENDOF GUI::MainWindow::setupMenu

// SETUP: sets file system view tree
void GUI::MainWindow::setupFileSystemView(QGridLayout* layout)
{
    // init
    fileSystemView = new QTreeView(gridLayoutWidget);
    QFileSystemModel* model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    // name filters
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.jpeg" << "*.png" << "*.tiff" << "*.tif";
    model->setNameFilters(nameFilters);

    // connects Filesystem model to treeview and adds to layout
    fileSystemView->setModel(model);
    layout->addWidget(fileSystemView, 2, 0, 1, 1);

    // import button
    importButton = new QPushButton(gridLayoutWidget);
    importButton->setObjectName(QString::fromUtf8("importButton"));
    importButton->setText(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
    layout->addWidget(importButton, 3, 0, 1, 1);
} // ENDOF GUI::MainWindow::setupFileSystemView

// SETUP: sets tabs
void GUI::MainWindow::setupTabs(QGridLayout* layout)
{
    tabWidget = new QTabWidget(gridLayoutWidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

    setupProjectTab(tabWidget);
    setupDetailsTab(tabWidget);

    pushButton_2 = new QPushButton(gridLayoutWidget);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

    layout->addWidget(pushButton_2, 5, 0, 1, 1);
    layout->addWidget(tabWidget, 4, 0, 1, 1);

    pushButton_2->setText(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
    tabWidget->setCurrentIndex(1);

} // ENDOF GUI::MainWindow::setupTabs

void GUI::MainWindow::setupProjectTab(QTabWidget* tab)
{
    projectViewWidget = new QWidget();
    projectViewWidget->setObjectName(QString::fromUtf8("projectViewWidget"));

    projectView = new QTreeView(projectViewWidget);
    projectView->setObjectName(QString::fromUtf8("projectView"));
    projectView->setGeometry(QRect(0, 0, 261, 221));

    tab->addTab(projectViewWidget, QString());
    tab->setTabText(tab->indexOf(projectViewWidget), QApplication::translate("MainWindow", "Project", 0, QApplication::UnicodeUTF8));
} // ENDOF GUI::MainWindow::setupProjectTab

void GUI::MainWindow::setupDetailsTab(QTabWidget* tab)
{
    detailsWidget = new QWidget();
    detailsWidget->setObjectName(QString::fromUtf8("detailsWidget"));

    tab->addTab(detailsWidget, QString());
    tab->setTabText(tab->indexOf(detailsWidget), QApplication::translate("MainWindow", "Details", 0, QApplication::UnicodeUTF8));
} // ENDOF GUI::MainWindow::setupDetailsTab
