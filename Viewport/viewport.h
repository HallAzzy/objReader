#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QOpenGLWidget>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

namespace Viewport {

class Viewport : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit Viewport(QWidget *parent = nullptr);
    ~Viewport();
    bool addObject(QVector<float> triangleCoords);
    Viewport(const Viewport &other) = delete;
    Viewport &operator=(const Viewport &other) = delete;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    bool createShaderProgram(QString vertexShaderFilePath, QString fragmentShaderFilePath);
    QOpenGLBuffer *m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLShaderProgram *m_shader = new QOpenGLShaderProgram();
    int m_verticesAmount = 0;
};
}
#endif // VIEWPORT_H
