#include "viewport.h"

Viewport::Viewport::Viewport(QWidget *parent) : QOpenGLWidget(parent)
{
}

Viewport::Viewport::~Viewport()
{
    if (m_shader != nullptr) {
        delete m_shader;
        m_shader = nullptr;
    }
    if (m_vertexBuffer) {
        m_vertexBuffer->destroy();
        delete m_vertexBuffer;
        m_vertexBuffer = nullptr;
    }
}

void Viewport::Viewport::initializeGL()
{
    initializeOpenGLFunctions();
    QString vertexShaderFilePath = "/home/anton/objReader/VertexShader.vert";
    QString fragmentShaderFilePath = "/home/anton/objReader/FragmentShader.frag";
    bool state = createShaderProgram(vertexShaderFilePath, fragmentShaderFilePath);

    if (!state) {
        qCritical() << "Failed to create shader program";
        return;
    }

    if (!m_vertexBuffer->create()) {
        qCritical() << "Failed to create vertex buffer";
        return;
    }
}

void Viewport::Viewport::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Viewport::Viewport::paintGL()
{
    glClearColor(0.6, 0.6, 0.6, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader->bind();
    m_vertexBuffer->bind();

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.translate(0, 0, -1);
    modelViewMatrix.rotate(40, {1, 0, 1});

    QMatrix4x4 projectionMatrix;
    float screenRatio = width() / float(height());
    projectionMatrix.ortho(-10, 10, -10 / screenRatio, 10/ screenRatio, 0.5, 5);

    m_shader->setUniformValue("modelViewMatrix", modelViewMatrix);
    m_shader->setUniformValue("projectionMatrix", projectionMatrix);
    m_shader->setAttributeBuffer("vertex", GL_FLOAT, 0, 3, 0);
    m_shader->enableAttributeArray("vertex");

    glDrawArrays(GL_TRIANGLES, 0, m_verticesAmount);
    m_shader->disableAttributeArray("vertex");
    m_shader->release();
    m_vertexBuffer->release();
}

bool Viewport::Viewport::addObject(QVector<float> triangleCoords)
{
    if (triangleCoords.isEmpty()) {
        qWarning() << "Triangle coordinates are empty";
        return false;
    }
    if (!m_vertexBuffer->bind()) {
        qCritical() << "Failed to bind vertex buffer";
        return false;
    }
    m_verticesAmount = triangleCoords.size() / 3;
    int dataSize = triangleCoords.size() * (sizeof(float));
    m_vertexBuffer->allocate(triangleCoords.constData(), dataSize);
    m_vertexBuffer->release();
    return true;
}

bool Viewport::Viewport::createShaderProgram(QString vertexShaderFilePath, QString fragmentShaderFilePath)
{
    if (!m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFilePath)) {
        return false;
    }
    if (!m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFilePath)) {
        return false;
    }
    if (!m_shader->link()) {
        return false;
    }
    return true;
}
