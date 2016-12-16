#include "mainwindow.h"
#include "welcome.h"
#include "options.h"
#include "ui_welcome.h"
#include "ui_options.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setVersion(4,1);
    //format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
    // MainWindow w;
    welcome w;
    // options w;
    w.show();

    return a.exec();
}
