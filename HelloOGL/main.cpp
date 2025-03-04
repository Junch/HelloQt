#include <QApplication>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    // 构造函数，初始化父类
    MyGLWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {}

protected:
    // 初始化OpenGL环境
    void initializeGL() override
    {
        // 初始化OpenGL函数指针
        initializeOpenGLFunctions();
        // 设置背景颜色为黑色
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    // 处理窗口大小调整
    void resizeGL(int w, int h) override
    {
        // 设置视口大小与窗口一致
        glViewport(0, 0, w, h);
        // 设置投影矩阵
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // 设置正交投影，坐标范围为 [-1, 1] x [-1, 1]
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        // 切换回模型视图矩阵
        glMatrixMode(GL_MODELVIEW);
    }

    // 渲染OpenGL场景（绘制三角形）
    void paintGL() override
    {
        // 清除颜色缓冲区
        glClear(GL_COLOR_BUFFER_BIT);
        // 重置模型视图矩阵
        glLoadIdentity();
        // 设置三角形颜色为红色
        glColor3f(1.0f, 0.0f, 0.0f);
        // 开始绘制三角形
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f); // 左下角
        glVertex2f(0.5f, -0.5f);  // 右下角
        glVertex2f(0.0f, 0.5f);   // 顶点
        glEnd();
    }
};

int main(int argc, char *argv[])
{
    // 创建Qt应用
    QApplication app(argc, argv);
    // 创建OpenGL窗口实例
    MyGLWidget widget;
    // 设置窗口初始大小
    widget.resize(800, 600);
    // 设置窗口标题
    widget.setWindowTitle("Triangle Example");
    // 显示窗口
    widget.show();
    // 进入事件循环
    return app.exec();
}
