#include "QWebView2.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QWindow>
#include <QUrl>
#include <string>

QWebView2::QWebView2(QWidget *parent) : QWidget(parent) {
    // 确保 QWidget 有原生窗口句柄
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_DontCreateNativeAncestors);
    
    initWebView();
}

QWebView2::~QWebView2() {
    if (m_controller) {
        m_controller->Close();
    }
}

void QWebView2::initWebView() {
    // 异步创建环境
    HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [this](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
                if (FAILED(result)) return result;

                // 创建控制器
                env->CreateCoreWebView2Controller((HWND)this->winId(),
                    Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [this](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                            if (FAILED(result)) return result;

                            m_controller = controller;
                            m_controller->get_CoreWebView2(&m_webView);

                            // 设置配置
                            ComPtr<ICoreWebView2Settings> settings;
                            m_webView->get_Settings(&settings);
                            settings->put_IsScriptEnabled(TRUE);
                            settings->put_AreDefaultContextMenusEnabled(TRUE);

                            m_isInitialized = true;
                            updateBounds();
                            emit webViewReady();
                            return S_OK;
                        }).Get());
                return S_OK;
            }).Get());
}

void QWebView2::navigate(const QString &url) {
    if (m_webView) {
        m_webView->Navigate(url.toStdWString().c_str());
    } else {
        m_pendingUrl = url;
        // 现在可以使用 UniqueConnection 了，因为它指向明确的成员函数
        connect(this, &QWebView2::webViewReady, this, &QWebView2::onWebViewReady, Qt::UniqueConnection);
    }
}

void QWebView2::navigateLocalFile(const QString &localPath) {
    QUrl url = QUrl::fromLocalFile(localPath);
    QString finalUrl = url.toString(QUrl::FullyEncoded);
    navigate(finalUrl);
}

void QWebView2::onWebViewReady() {
    if (!m_pendingUrl.isEmpty()) {
        m_webView->Navigate(m_pendingUrl.toStdWString().c_str());
        m_pendingUrl.clear();
    }
}

void QWebView2::updateBounds() {
    if (m_controller) {
        RECT bounds;
        GetClientRect((HWND)winId(), &bounds);
        m_controller->put_Bounds(bounds);
    }
}

void QWebView2::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    updateBounds();
}

bool QWebView2::event(QEvent *event) {
    // 处理 DPI 变化或窗口移动
    if (event->type() == QEvent::WindowChangeInternal || event->type() == QEvent::ScreenChangeInternal) {
        updateBounds();
    }
    return QWidget::event(event);
}