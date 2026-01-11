#pragma once

#include "framelesswindow.h"

class MainWindow : public FramelessWindowT<QMainWindow>
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
};
