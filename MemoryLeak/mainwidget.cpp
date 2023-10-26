#include "mainwidget.h"
#include <QPushButton>
#include <QTextBrowser>
#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    m_button = new QPushButton(tr("Start Leak!"), this);
    m_button->setFixedWidth(150);
    m_textBrowser = new QTextBrowser(this);
    m_timer = new QTimer(this);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(m_button, 0, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_textBrowser, 1, 0);
    setLayout(mainLayout);
    setWindowTitle(tr("Memory Leak"));
    setMinimumSize(400, 300);

    connect(m_button, &QPushButton::clicked, this, &MainWidget::handleButton);
    connect(m_timer, &QTimer::timeout, this, &MainWidget::update);
}

void MainWidget::handleButton()
{
    static bool bLeak = true;
    if (bLeak)
    {
        m_timer->start(1000);
        m_button->setText(tr("Stop Leak!"));
    }
    else
    {
        m_timer->stop();
        m_button->setText(tr("Start Leak!"));
    }

    bLeak = !bLeak;
}

void MainWidget::update()
{
    static int nCount = 0;
    ++nCount;
    auto p = new char[1024];
    auto str = QString("Memory leak 1024. Total memory leaked %1").arg(1024*nCount);
    m_textBrowser->append(str);
}
