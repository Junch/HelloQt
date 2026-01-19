#include <QApplication>
#include <QVBoxLayout>
#include <QMainWindow>
#include "QWebView2.h"
#include <objbase.h> // 用于 CoInitializeEx
#include <QDir>
#include <QFile>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QKeySequence>


int main(int argc, char *argv[]) {
    // 1. 初始化 COM 库（WebView2 是基于 COM 的）
    // Qt 通常会处理此操作，但在某些复杂多线程环境下手动初始化更安全
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    QApplication a(argc, argv);

    // 2. 创建主窗口
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Qt WebView2 Demo");
    mainWindow.resize(1024, 768);

    // 3. 创建我们的自定义 WebView2 控件
    QWebView2 *webView = new QWebView2(&mainWindow);

    // 4. 设置布局
    QWidget *centralWidget = new QWidget(&mainWindow);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0); // 让网页充满窗口
    layout->addWidget(webView);
    
    mainWindow.setCentralWidget(centralWidget);

    // 添加 File -> Open 菜单项，用于打开本地 HTML 文件
    QMenu *fileMenu = mainWindow.menuBar()->addMenu("&File");
    QAction *openAction = new QAction("&Open...", &mainWindow);
    openAction->setShortcut(QKeySequence::Open);
    fileMenu->addAction(openAction);
    QObject::connect(openAction, &QAction::triggered, [&mainWindow, webView]() {
        QString filePath = QFileDialog::getOpenFileName(&mainWindow, "Open HTML file", QDir::homePath(), "HTML Files (*.htm *.html);;All Files (*)");
        if (!filePath.isEmpty()) {
            webView->navigateLocalFile(filePath);
        }
    });

    mainWindow.show();

    webView->navigate("https://www.bing.com");

    int result = a.exec();

    // 6. 释放 COM
    CoUninitialize();

    return result;
}