#include "mainwidget.h"
#include <QPushButton>
#include <QTextBrowser>
#include <QGridLayout>
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    button_ = new QPushButton(tr("Push Me!"));
    textBrowser_ = new QTextBrowser();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(button_, 0, 0);
    mainLayout->addWidget(textBrowser_, 1, 0);
    setLayout(mainLayout);
    setWindowTitle(tr("你好，QT！"));
    setMinimumSize(400, 300);

    connect(button_, &QPushButton::clicked, this, &MainWidget::handleButton);
}

void MainWidget::handleButton()
{
    QMessageBox::information(this, tr("HelloWidget"), tr("Button is clicked"));
}

void MainWidget::targetButton()
{
    QMessageBox::information(this, tr("HelloWidget"), tr("Target button is clicked"));
}

MainWidget::~MainWidget()
{
    delete button_;
    delete textBrowser_;
}
