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
        Mesh(const QVector<QVector3D> &vertices, const QVector<QVector2D> &textureVertices, const QVector<QVector<int>> &faceVerticesIndeces, const QVector<QVector<int>> &textureFaceVerticesIndeces);

        const QVector<QVector3D> &getVertices();
        const QVector<QVector2D> &getTextureVertices();
        const QVector<QVector<int>> &getFaceVerticesIndeces();
        const QVector<QVector<int>> &getTextureFaceVerticesIndeces();
        const QVector<QVector<int>> &getGroupIndeces();
        const QVector<QString> &getGroups();
        QVector<QVector3D> calcBoundBox();

    private:
        QVector<QVector3D> m_vertices;
        QVector<QVector2D> m_textureVertices;
        QVector<QVector3D> m_normals;
        QVector<QVector<int>> m_faceVerticesIndeces;
        QVector<QVector<int>> m_textureFaceVerticesIndeces;
        QVector<QVector<int>> m_normalIndeces;
        QVector<int> m_groups;
        QVector<QString> m_groupNames;
    };
}


#endif // MESH_H
