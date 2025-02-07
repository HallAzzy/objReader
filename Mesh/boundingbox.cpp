#include "boundingbox.h"

namespace MyMesh {
MyMesh::BoundingBox::BoundingBox(const QVector3D &nearestLeftBottom, const QVector3D &farthestRightTop)
{
    m_nearestLeftBottom = nearestLeftBottom;
    m_farthestRightTop = farthestRightTop;
}

BoundingBox MyMesh::BoundingBox::fromVertices(const QVector<QVector3D> &vertices)
{
    if (vertices.isEmpty())
        return BoundingBox();
     QVector3D nearestLeftBottom(vertices[0].x(), vertices[0].y(), vertices[0].z());
     QVector3D farthestRightTop(vertices[0].x(), vertices[0].y(), vertices[0].z());

    for (const QVector3D &vertex : vertices) {
        if (vertex.x() < nearestLeftBottom.x())
            nearestLeftBottom.setX(vertex.x());
        if (vertex.y() < nearestLeftBottom.y())
            nearestLeftBottom.setY(vertex.y());
        if (vertex.z() < nearestLeftBottom.z())
            nearestLeftBottom.setZ(vertex.z());

        if (vertex.x() > farthestRightTop.x())
            farthestRightTop.setX(vertex.x());
        if (vertex.y() > farthestRightTop.y())
            farthestRightTop.setY(vertex.y());
        if (vertex.z() > farthestRightTop.z())
            farthestRightTop.setZ(vertex.z());
    }
    return BoundingBox(nearestLeftBottom, farthestRightTop);
}

const QVector3D MyMesh::BoundingBox::nearestLeftBottom() const
{
    return m_nearestLeftBottom;
}

const QVector3D MyMesh::BoundingBox::farthestRightTop() const
{
    return m_farthestRightTop;
}

bool MyMesh::BoundingBox::operator==(const BoundingBox &other) const
{
    return (
            qFuzzyCompare(m_nearestLeftBottom[0], other.m_nearestLeftBottom[0]) &&
            qFuzzyCompare(m_nearestLeftBottom[1], other.m_nearestLeftBottom[1]) &&
            qFuzzyCompare(m_nearestLeftBottom[2], other.m_nearestLeftBottom[2]) &&
            qFuzzyCompare(m_farthestRightTop[0], other.m_farthestRightTop[0]) &&
            qFuzzyCompare(m_farthestRightTop[1], other.m_farthestRightTop[1]) &&
            qFuzzyCompare(m_farthestRightTop[2], other.m_farthestRightTop[2]));
}

} // namespace MyMesh
