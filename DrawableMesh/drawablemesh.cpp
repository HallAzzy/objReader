#include "drawablemesh.h"

namespace Drawable {

DrawableMesh::DrawableMesh()
{
}

DrawableMesh::DrawableMesh(
        const QVector<int> &triangulatedVertices,
        const QVector<QVector3D> &vertices)
{
    QVector<float> triangulatedFlatCoords = triangleCoordinatesVector(triangulatedVertices, vertices);
    m_verticesAmount = triangulatedFlatCoords.size() / 3;
    const int dataSize = triangulatedFlatCoords.size() * static_cast<int>(sizeof(float));
    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    if (!m_vertexBuffer->create())
        qFatal("Failed to create vertex buffer");
    if (!m_vertexBuffer->bind())
        qFatal("Failed to bind vertex buffer");
    m_vertexBuffer->allocate(triangulatedFlatCoords.constData(), dataSize);
    m_vertexBuffer->release();

    QString vertexShaderFileName = "/home/anton/objReader/DrawableMesh/VertexShader.vert";
    QString fragmentShaderFileName = "/home/anton/objReader/DrawableMesh/FragmentShader.frag";
    m_shader = createShaderProgram(vertexShaderFileName, fragmentShaderFileName);
    if (m_shader == nullptr)
        qFatal("Failed to create shader");
}

DrawableMesh::~DrawableMesh()
{
    delete m_vertexBuffer;
    m_vertexBuffer = nullptr;
    delete m_normalBuffer;
    m_normalBuffer = nullptr;
    delete m_shader;
    m_shader = nullptr;
}

void DrawableMesh::draw(QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix)
{
    bool isBound = m_shader->bind();
    if (!isBound)
        qFatal("Can't bind the shader");
    m_shader->setUniformValue("modelViewMatrix", viewMatrix);
    m_shader->setUniformValue("projectionMatrix", projectionMatrix);

    isBound = m_vertexBuffer->bind();
    if (!isBound)
        qFatal("Can't bind the vertex buffer");
    m_shader->setAttributeBuffer("vertex", GL_FLOAT, 0, 3, 0);
    m_shader->enableAttributeArray("vertex");
    m_vertexBuffer->release();

    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, m_verticesAmount);

    m_shader->disableAttributeArray("vertex");

    m_shader->release();
}

QVector<float> DrawableMesh::triangleCoordinatesVector(
        const QVector<int> &triangulatedVertices,
        const QVector<QVector3D> &vertices)
{
    QVector<float> triangulatedFlatCoords;
    for (int index : triangulatedVertices) {
        --index;
        triangulatedFlatCoords.append(vertices[index].x());
        triangulatedFlatCoords.append(vertices[index].y());
        triangulatedFlatCoords.append(vertices[index].z());
    }
    return triangulatedFlatCoords;
}

QOpenGLShaderProgram *DrawableMesh::createShaderProgram(QString vertexShaderFileName, QString fragmentShaderFileName)
{
    QOpenGLShaderProgram *shader = new QOpenGLShaderProgram();
    if (!shader->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFileName)) {
        delete shader;
        return nullptr;
    }
    if (!shader->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFileName)) {
        delete shader;
        return nullptr;
    }
    if (!shader->link()) {
        delete shader;
        return nullptr;
    }
    return shader;
}
} // namespace Drawable
