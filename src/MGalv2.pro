#-------------------------------------------------
#
# Project created by QtCreator 2011-09-28T13:14:48
#
#-------------------------------------------------

QT	    += core gui
INCLUDEPATH = C:/msys/1.0/local/include
LIBS	    += C:/msys/1.0/local/bin/libexif.dll

TARGET	    = MGalv2
TEMPLATE    = app

SOURCES += main.cpp\        
    gui/mainwindow.cpp \
    core/mdatabase.cpp \
    core/mgallery.cpp \
    core/mphoto.cpp \
    gui/mtreewidget.cpp \
    core/mobject.cpp \
    gui/mgridwidget.cpp \
    gui/mgridwidgetitem.cpp \
    gui/mgridwidgetitemiconset.cpp \
    gui/mgridwidgetitembutton.cpp \
    gui/mtreewidgetitem.cpp \
    gui/mnewgallerydialog.cpp

HEADERS  += gui/mainwindow.h \
    core/mdatabase.h \
    core/mgallery.h \
    core/mphoto.h \
    gui/mtreewidget.h \
    core/mobject.h \
    gui/mgridwidget.h \
    gui/mgridwidgetitem.h \
    gui/mgridwidgetitemiconset.h \
    gui/mgridwidgetitembutton.h \
    gui/mgridwidgetdefines.h \
    gui/mtreewidgetitem.h \
    gui/mnewgallerydialog.h
