#pragma once

#include <QWidget>
#include <memory>
#include <wrl.h>
#include <WebView2.h>

using namespace Microsoft::WRL;

class QWebView2 : public QWidget {
    Q_OBJECT

public:
    explicit QWebView2(QWidget *parent = nullptr);
    ~QWebView2();

    void navigate(const QString &url);
    void navigateLocalFile(const QString &localPath);

signals:
    void navigationCompleted(bool success);
    void webViewReady();

protected:
    void resizeEvent(QResizeEvent *event) override;
    bool event(QEvent *event) override;

private:
    void initWebView();
    void updateBounds();
    QString m_pendingUrl;
    void onWebViewReady(); // 定义槽函数

    ComPtr<ICoreWebView2Controller> m_controller;
    ComPtr<ICoreWebView2> m_webView;
    bool m_isInitialized = false;
};