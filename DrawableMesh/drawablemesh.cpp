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

    QVector<float> triangleNormalCoords = calcNormals(triangulatedVertices, vertices);
    m_normalBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    if (!m_normalBuffer->create())
        qFatal("Failed to create normal buffer");
    if (!m_normalBuffer->bind())
        qFatal("Failed to bind normal buffer");
    m_normalBuffer->allocate(triangleNormalCoords.constData(), dataSize);
    m_normalBuffer->release();

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
    QMatrix4x4 normalMatrix = viewMatrix.inverted().transposed();
    bool shaderBound = m_shader->bind();
    if (!shaderBound)
        qFatal("Can't bind the shader");
    m_shader->setUniformValue("modelViewMatrix", viewMatrix);
    m_shader->setUniformValue("normalMatrix", normalMatrix);
    m_shader->setUniformValue("projectionMatrix", projectionMatrix);

    bool vertexBound = m_vertexBuffer->bind();
    if (!vertexBound)
        qFatal("Can't bind the vertices buffer");
    m_shader->setAttributeBuffer("vertex", GL_FLOAT, 0, 3, 0);
    m_shader->enableAttributeArray("vertex");
    m_vertexBuffer->release();

    bool normalBound = m_normalBuffer->bind();
    if (!normalBound)
        qFatal("Can't bind the normals buffer");
    m_shader->setAttributeBuffer("normal", GL_FLOAT, 0, 3, 0);
    m_shader->enableAttributeArray("normal");
    m_normalBuffer->release();

    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, m_verticesAmount);

    m_shader->disableAttributeArray("vertex");
    m_shader->disableAttributeArray("normal");

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

QVector<float> DrawableMesh::calcNormals(
        const QVector<int> &triangulatedVertices,
        const QVector<QVector3D> &vertices)
{
    QVector<QVector3D> normals;
    normals.resize(vertices.size());
    for (QVector3D &normal : normals) {
        normal = QVector3D(0, 0, 0);
    }

    for (int i = 0; i < triangulatedVertices.size(); i += 3) {

        int i1 = triangulatedVertices[i];
        int i2 = triangulatedVertices[i + 1];
        int i3 = triangulatedVertices[i + 2];

        const QVector3D &v1 = vertices[i1 - 1];
        const QVector3D &v2 = vertices[i2 - 1];
        const QVector3D &v3 = vertices[i3 - 1];

        QVector3D edge1 = v2 - v1;
        QVector3D edge2 = v3 - v1;

        QVector3D triangleNormal = QVector3D::crossProduct(edge1, edge2);

        normals[i1 - 1] += triangleNormal;
        normals[i2 - 1] += triangleNormal;
        normals[i3 - 1] += triangleNormal;
    }

    for (QVector3D &normal : normals) {
        normal.normalize();
    }
    return triangleCoordinatesVector(triangulatedVertices, normals);
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
