#ifndef MESH_H
#define MESH_H

#include <QPair>
#include <QVector2D>
#include "boundingbox.h"

namespace MyMesh {
class Mesh
{
public:
    Mesh() = default;
    QString init(
            const QVector<QVector3D> &vertices, const QVector<QVector2D> &textureVertices, const QVector<QVector3D> &normals,
            const QVector<QVector<int>> &faceVerticesIndices, const QVector<QVector<int>> &textureFaceVerticesIndices,
            const QVector<QVector<int>> &normalIndices, const QVector<int> &groups, const QVector<QString> &groupNames);

    const QVector<QVector3D> &vertices() const;
    const QVector<QVector2D> &textureVertices() const;
    const QVector<QVector3D> &normals() const;
    const QVector<QVector<int>> &faceVerticesIndices() const;
    const QVector<QVector<int>> &textureFaceVerticesIndices() const;
    const QVector<QVector<int>> &normalIndices() const;
    const QVector<QVector<int>> &groupIndices() const;
    const QVector<QString> &groups() const;
    const BoundingBox &meshBoundingBox() const;
    QVector<int> buildPolygonVertexIndicesVector() const;
    QVector<int> buildPolygonStartsVector() const;
    QVector<int> triangulatedVertices() const;
    QVector<float> toFlat() const;
    bool operator==(const Mesh &other) const;

private:
    QVector<QVector3D> m_vertices;
    QVector<QVector2D> m_textureVertices;
    QVector<QVector3D> m_normals;
    QVector<QVector<int>> m_faceVerticesIndices;
    QVector<QVector<int>> m_textureFaceVerticesIndices;
    QVector<QVector<int>> m_normalIndices;
    QVector<int> m_groups;
    QVector<QString> m_groupNames;
    BoundingBox m_meshBoundingBox;
};
}


#endif // MESH_H
