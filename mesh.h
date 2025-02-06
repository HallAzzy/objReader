#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>

//! REVIEW: namespace

namespace MyMesh {
    class Mesh
    {
    public:
        Mesh() = default;
        Mesh(const QVector<QVector3D> &vertices, const QVector<QVector2D> &textureVertices, const QVector<QVector3D> &normals,
             const QVector<QVector<int>> &faceVerticesIndices, const QVector<QVector<int>> &textureFaceVerticesIndices,
             const QVector<QVector<int>> &m_normalIndices, const QVector<int> &groups, const QVector<QString> &groupNames);

        const QVector<QVector3D> &Vertices();
        const QVector<QVector2D> &TextureVertices();
        const QVector<QVector<int>> &FaceVerticesIndices();
        const QVector<QVector<int>> &TextureFaceVerticesIndices();
        const QVector<QVector<int>> &GroupIndices();
        const QVector<QString> &Groups();
        QVector<QVector3D> calcBoundBox() const;
        bool operator==(const Mesh& other) const;

    private:
        QVector<QVector3D> m_vertices;
        QVector<QVector2D> m_textureVertices;
        QVector<QVector3D> m_normals;
        QVector<QVector<int>> m_faceVerticesIndices;
        QVector<QVector<int>> m_textureFaceVerticesIndices;
        QVector<QVector<int>> m_normalIndices;
        QVector<int> m_groups;
        QVector<QString> m_groupNames;
    };
}


#endif // MESH_H
