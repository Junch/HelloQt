#include "undotest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    undoTest w;
    w.show();
    return a.exec();
}
