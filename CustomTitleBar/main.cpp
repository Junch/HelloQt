#include <QApplication>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QIcon appIcon(":/icons/app.ico");
    if (appIcon.isNull()) appIcon = QIcon(":/icons/app.png");
    app.setWindowIcon(appIcon);
    MainWindow w;
    w.setWindowIcon(appIcon);
    w.resize(800, 600);
    w.show();
    return app.exec();
}
