QT	    += core gui
INCLUDEPATH = C:/libs/boost_1_47_0 C:/libs/jpeg-8c
LIBS	    += C:/libs/jpeg-8c/libjpeg-8.dll

TARGET	    = MGalv2
TEMPLATE    = app

SOURCES += main.cpp\        
    gui/mainwindow.cpp \
    core/mdatabase.cpp \
    core/mgallery.cpp \
    core/mphoto.cpp \
    gui/mtreewidget/mtreewidget.cpp \
    core/mobject.cpp \
    gui/mgridwidget/mgridwidget.cpp \
    gui/mgridwidget/mgridwidgetitem.cpp \
    gui/mgridwidget/mgridwidgetitemiconset.cpp \
    gui/mgridwidget/mgridwidgetitembutton.cpp \
    gui/mtreewidget/mtreewidgetitem.cpp \
    gui/mnewgallerydialog.cpp \
    gui/mgridwidget/mgridwidgetviewer.cpp \
    gui/mgridwidget/mgridwidgetthumbnail.cpp \
    gui/mresizedialog.cpp

HEADERS  += gui/mainwindow.h \
    core/mdatabase.h \
    core/mgallery.h \
    core/mphoto.h \
    gui/mtreewidget/mtreewidget.h \
    core/mobject.h \
    gui/mgridwidget/mgridwidget.h \
    gui/mgridwidget/mgridwidgetitem.h \
    gui/mgridwidget/mgridwidgetitemiconset.h \
    gui/mgridwidget/mgridwidgetitembutton.h \
    gui/mgridwidget/mgridwidgetdefines.h \
    gui/mtreewidget/mtreewidgetitem.h \
    gui/mnewgallerydialog.h \
    gui/mgridwidget/mgridwidgetviewer.h \
    gui/mgridwidget/mgridwidgetthumbnail.h \
    core/mnumeric.h \
    core/mimage.h \
    shareddefines.h \
    gui/mresizedialog.h
