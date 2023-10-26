#pragma once
#include <QWidget>

class QPushButton;
class QTextBrowser;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);

private slots:
    void handleButton();
    void update();

private:
    QPushButton *m_button;
    QTextBrowser *m_textBrowser;
    QTimer *m_timer;
};
