#pragma once

#include <QMainWindow>
#include <QPoint>

class QWidget;
class QLabel;
class QToolButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QWidget *m_titleBar{};
    QLabel *m_titleLabel{};
    QToolButton *m_minBtn{};
    QToolButton *m_maxBtn{};
    QToolButton *m_closeBtn{};

    QPoint m_dragPos{};
    bool m_dragging{false};
    bool isMaximized{false};
};
