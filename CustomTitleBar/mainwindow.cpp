#include "mainwindow.h"

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QStyle>
#include <QApplication>
#include <QSizePolicy>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Remove native title bar
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);

    // Title bar
    m_titleBar = new QWidget(this);
    m_titleBar->setObjectName("titleBar");

    m_titleBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	int titlebarHeight = 30;
    m_titleBar->setFixedHeight(titlebarHeight);

    m_iconLabel = new QLabel(m_titleBar);
    m_iconLabel->setScaledContents(true);
    QPixmap pix(":/icons/app.png");
    if (!pix.isNull()) {
        int iconSize = qMax(16, titlebarHeight - 6); // use the known titlebar fixed height
        m_iconLabel->setPixmap(pix.scaled(iconSize, iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_iconLabel->setFixedSize(iconSize, iconSize);
    }
    m_iconLabel->setContentsMargins(0, 0, 0, 0);

    m_titleLabel = new QLabel("Custom Title Bar Example", m_titleBar);
    m_titleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    m_menuBtn = new QToolButton(m_titleBar);
    m_menuBtn->setText("☰"); // ≡
    auto menu = new QMenu(m_menuBtn);
    auto aboutAct = menu->addAction("About");
    connect(aboutAct, &QAction::triggered, [this]() {
        QMessageBox::about(this, "About", "Custom Title Bar Example\nVersion 1.0");
    });
    auto checkAct = menu->addAction("Checking for update");
    connect(checkAct, &QAction::triggered, [this]() {
        QMessageBox::information(this, "Update", "Checking for update...");
    });
    m_menuBtn->setMenu(menu);
    m_menuBtn->setPopupMode(QToolButton::InstantPopup);
    m_menuBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
    m_menuBtn->setStyleSheet("QToolButton::menu-indicator { image: none; }");

    m_minBtn = new QToolButton(m_titleBar);
    m_maxBtn = new QToolButton(m_titleBar);
    m_closeBtn = new QToolButton(m_titleBar);

    m_minBtn->setText("─"); // -
    m_maxBtn->setText("☐");
    m_closeBtn->setText("✕");

    connect(m_minBtn, &QToolButton::clicked, this, &MainWindow::showMinimized);
    connect(m_maxBtn, &QToolButton::clicked, [this]() {
        if (isMaximized) { showNormal(); isMaximized = false; m_maxBtn->setText("☐"); }
        else { showMaximized(); isMaximized = true; m_maxBtn->setText("❐"); }
    });
    connect(m_closeBtn, &QToolButton::clicked, this, &MainWindow::close);

    auto titleLayout = new QHBoxLayout(m_titleBar);
    titleLayout->setContentsMargins(1, 0, 6, 0);
    titleLayout->addWidget(m_iconLabel);
    titleLayout->addWidget(m_titleLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(m_menuBtn);
    titleLayout->addWidget(m_minBtn);
    titleLayout->addWidget(m_maxBtn);
    titleLayout->addWidget(m_closeBtn);

    // Central content
    auto central = new QWidget(this);
    auto vlay = new QVBoxLayout(central);
    vlay->setContentsMargins(0, 0, 0, 0);
    vlay->setSpacing(0);
    vlay->addWidget(m_titleBar);

    auto content = new QLabel("Main Window Content", central);
    content->setAlignment(Qt::AlignCenter);
    vlay->addWidget(content, 1);

    setCentralWidget(central);

    // Styles
    setStyleSheet(R"(
        #titleBar { background: #2d2d30; color: #ffffff; }
        #titleBar > QLabel { color: #ffffff; font-weight: bold; padding-left: 6px; font-size: 13px; }
        QToolButton { background: transparent; color: #ffffff; border: none; min-width: 34px; }
        QToolButton:hover { background: rgba(255,255,255,0.06); }
    )");
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->pos().y() <= m_titleBar->height()) {
        m_dragging = true;
        m_dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    } else {
        QMainWindow::mousePressEvent(event);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton) && !isMaximized) {
        move(event->globalPosition().toPoint() - m_dragPos);
        event->accept();
    } else {
        QMainWindow::mouseMoveEvent(event);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_dragging = false;
    QMainWindow::mouseReleaseEvent(event);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->pos().y() <= m_titleBar->height()) {
        if (isMaximized) { showNormal(); isMaximized = false; m_maxBtn->setText("☐"); }
        else { showMaximized(); isMaximized = true; m_maxBtn->setText("❐"); }
        event->accept();
    } else {
        QMainWindow::mouseDoubleClickEvent(event);
    }
}
