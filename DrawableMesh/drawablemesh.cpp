#include "drawablemesh.h"

namespace Drawable {

DrawableMesh::DrawableMesh()
{

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

}

QVector<float> DrawableMesh::triangleCoordinatesVector(const QVector<int> &triangulatedVertices,
                                                       const QVector<QVector3D> &vertices) const
{
    QVector<float> triangulatedFlatCoords;
    for (int index : triangulatedVertices) {
        triangulatedFlatCoords.append(vertices[index - 1].x());
        triangulatedFlatCoords.append(vertices[index - 1].y());
        triangulatedFlatCoords.append(vertices[index - 1].z());
    }
    return triangulatedFlatCoords;
}
} // namespace Drawable
