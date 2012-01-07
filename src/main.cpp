#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{  
    QApplication a(argc, argv);

    // splash screen
    QPixmap pix(QCoreApplication::applicationDirPath() + "/splash.jpg");
    QSplashScreen splash(pix, Qt::WindowStaysOnTopHint);
    splash.show();

    a.processEvents();
    mgui::MainWindow w;
    w.show();

    return a.exec();
}
