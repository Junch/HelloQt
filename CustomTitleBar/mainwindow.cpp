#include "mainwindow.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : FramelessWindowT(parent)
{
    // Set title text for the frameless title bar
    setWindowTitleText("Custom Title Bar Example");

    // Add central content below the title bar (the base class already added the title bar)
    auto central = centralWidget();
    if (central) {
        if (auto vlay = qobject_cast<QVBoxLayout*>(central->layout())) {
            auto content = new QLabel("Main Window Content", central);
            content->setAlignment(Qt::AlignCenter);
            vlay->addWidget(content, 1);
        }
    }
}
