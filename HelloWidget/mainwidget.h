#pragma once
#include <QWidget>

class QPushButton;
class QTextBrowser;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
	MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    QPushButton* button_;
    QTextBrowser*  textBrowser_;
};

