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

    QVector<QVector3D> getVertices();
    QVector<QVector2D> getTextureVertices();
    QVector<QVector<int>> getFaceVerticesIndeces();
    QVector<QVector<int>> getTextureFaceVerticesIndeces();
    QVector<QVector3D> calcBoundBox();

private:
    QVector<QVector3D> m_vertices;
    QVector<QVector2D> m_textureVertices;
    QVector<QVector3D> m_normals;
    QVector<QVector<int>> m_faceVerticesIndeces;
    QVector<QVector<int>> m_textureFaceVerticesIndeces;
    QVector<QVector<int>> m_normalIndeces;
    QVector<QVector3D> boundingBox;
};

#endif // MESH_H
