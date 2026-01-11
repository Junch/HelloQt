#pragma once

#include <type_traits>
#include <QMainWindow>
#include <QWidget>
#include <QPoint>
#include <QLabel>
#include <QToolButton>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QPixmap>

// Template mixin providing frameless titlebar and drag/maximize behavior
template<class Base = QMainWindow>
class FramelessWindowT : public Base
{
    static_assert(std::is_base_of<QWidget, Base>::value, "Base must derive from QWidget");
public:
    explicit FramelessWindowT(QWidget *parent = nullptr)
        : Base(parent)
    {
        this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);

        m_titleBar = new QWidget(this);
        m_titleBar->setObjectName("titleBar");

        m_titleBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        int titlebarHeight = 30;
        m_titleBar->setFixedHeight(titlebarHeight);

        m_iconLabel = new QLabel(m_titleBar);
        m_iconLabel->setScaledContents(true);
        QPixmap pix(":/icons/app.png");
        if (!pix.isNull()) {
            int iconSize = qMax(16, titlebarHeight - 6);
            m_iconLabel->setPixmap(pix.scaled(iconSize, iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            m_iconLabel->setFixedSize(iconSize, iconSize);
        }
        m_iconLabel->setContentsMargins(0, 0, 0, 0);

        m_titleLabel = new QLabel("Application", m_titleBar);
        m_titleLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

        m_menuBtn = new QToolButton(m_titleBar);
        m_menuBtn->setText("☰");
        auto menu = new QMenu(m_menuBtn);
        auto aboutAct = menu->addAction("About");
        QObject::connect(aboutAct, &QAction::triggered, [this]() {
            QMessageBox::about(this, "About", "Custom Title Bar Example\nVersion 1.0");
        });
        auto checkAct = menu->addAction("Checking for update");
        QObject::connect(checkAct, &QAction::triggered, [this]() {
            QMessageBox::information(this, "Update", "Checking for update...");
        });
        m_menuBtn->setMenu(menu);
        m_menuBtn->setPopupMode(QToolButton::InstantPopup);
        m_menuBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
        m_menuBtn->setStyleSheet("QToolButton::menu-indicator { image: none; }");

        m_minBtn = new QToolButton(m_titleBar);
        m_maxBtn = new QToolButton(m_titleBar);
        m_closeBtn = new QToolButton(m_titleBar);

        m_minBtn->setText("─");
        m_maxBtn->setText("☐");
        m_closeBtn->setText("✕");

        QObject::connect(m_minBtn, &QToolButton::clicked, this, &FramelessWindowT::showMinimized);
        QObject::connect(m_maxBtn, &QToolButton::clicked, [this]() {
            if (m_isMaximized) { this->showNormal(); m_isMaximized = false; m_maxBtn->setText("☐"); }
            else { this->showMaximized(); m_isMaximized = true; m_maxBtn->setText("❐"); }
        });
        QObject::connect(m_closeBtn, &QToolButton::clicked, this, &FramelessWindowT::close);

        auto titleLayout = new QHBoxLayout(m_titleBar);
        titleLayout->setContentsMargins(1, 0, 6, 0);
        titleLayout->addWidget(m_iconLabel);
        titleLayout->addWidget(m_titleLabel);
        titleLayout->addStretch();
        titleLayout->addWidget(m_menuBtn);
        titleLayout->addWidget(m_minBtn);
        titleLayout->addWidget(m_maxBtn);
        titleLayout->addWidget(m_closeBtn);

        // Place the title bar above the content area for QMainWindow; for widgets, create a dedicated content widget
        if constexpr (std::is_base_of<QMainWindow, Base>::value) {
            auto container = new QWidget(this);
            auto vlay = new QVBoxLayout(container);
            vlay->setContentsMargins(0, 0, 0, 0);
            vlay->setSpacing(0);
            vlay->addWidget(m_titleBar);
            // create the content widget that will host the derived class UI
            m_contentWidget = new QWidget(container);
            m_contentWidget->setObjectName("content");
            m_contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            vlay->addWidget(m_contentWidget);
            Base::setCentralWidget(container);
        } else {
            if constexpr (std::is_base_of<QWidget, Base>::value) {
                auto vlay = new QVBoxLayout(this);
                vlay->setContentsMargins(0, 0, 0, 0);
                vlay->setSpacing(0);
                vlay->addWidget(m_titleBar);
                // dedicated content widget to host the derived class UI (prevents setupUi from disrupting the titlebar)
                // For dialogs/widgets, create an instance of the Base type so callers can safely cast to Base (e.g. QDialog)
                m_contentWidget = new Base(this);
                // Ensure the content behaves like an embedded widget (not a dialog window)
                m_contentWidget->setWindowFlags(Qt::Widget);
                m_contentWidget->setObjectName("content");
                m_contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                vlay->addWidget(m_contentWidget);
            }
        }

        // Styles
        this->setStyleSheet(R"(
            #titleBar { background: #2d2d30; color: #ffffff; }
            #titleBar > QLabel { color: #ffffff; font-weight: bold; padding-left: 6px; font-size: 13px; }
            QToolButton { background: transparent; color: #ffffff; border: none; min-width: 34px; }
            QToolButton:hover { background: rgba(255,255,255,0.06); }
        )");
    }

    void setWindowTitleText(const QString &title) { if (m_titleLabel) m_titleLabel->setText(title); }

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton && m_titleBar && event->pos().y() <= m_titleBar->height()) {
            m_dragging = true;
            m_dragPos = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
            event->accept();
            return;
        }
        Base::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (m_dragging && (event->buttons() & Qt::LeftButton) && !m_isMaximized) {
            this->move(event->globalPosition().toPoint() - m_dragPos);
            event->accept();
            return;
        }
        Base::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        m_dragging = false;
        Base::mouseReleaseEvent(event);
    }

    void mouseDoubleClickEvent(QMouseEvent *event) override
    {
        if (m_titleBar && event->pos().y() <= m_titleBar->height()) {
            if (m_isMaximized) { this->showNormal(); m_isMaximized = false; m_maxBtn->setText("☐"); }
            else { this->showMaximized(); m_isMaximized = true; m_maxBtn->setText("❐"); }
            event->accept();
            return;
        }
        Base::mouseDoubleClickEvent(event);
    }

    QWidget* contentWidget() { return m_contentWidget ? m_contentWidget : static_cast<QWidget*>(this); }
    const QWidget* contentWidget() const { return m_contentWidget ? m_contentWidget : static_cast<const QWidget*>(this); }

protected:
    QWidget *m_titleBar{};
    QLabel *m_iconLabel{};
    QLabel *m_titleLabel{};
    QToolButton *m_menuBtn{};
    QToolButton *m_minBtn{};
    QToolButton *m_maxBtn{};
    QToolButton *m_closeBtn{};

    QPoint m_dragPos{};
    bool m_dragging{false};
    bool m_isMaximized{false};

    QWidget *m_contentWidget{};
};
