#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>

class Mesh
{
public:
    Mesh() = default;
    Mesh(QVector<QVector3D> vertices, QVector<QVector2D> textureVertices, QVector<QVector<int>> faceVerticesIndeces, QVector<QVector<int>> textureFaceVerticesIndeces);

private:
    QVector<QVector3D> m_vertices;
    QVector<QVector2D> m_textureVertices;
    QVector<QVector<int>> m_faceVerticesIndeces;
    QVector<QVector<int>> m_textureFaceVerticesIndeces;
};

#endif // MESH_H
