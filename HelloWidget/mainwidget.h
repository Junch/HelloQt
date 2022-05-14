#pragma once
#include <QWidget>

class QPushButton;
class QTextBrowser;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void handleButton();
    void targetButton();

private:
    QPushButton *button_;
    QTextBrowser *textBrowser_;
};
