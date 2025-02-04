#include "mesh.h"

Mesh::Mesh(QVector<QVector3D> vertices, QVector<QVector2D> textureVertices, QVector<QVector<int>> faceVerticesIndeces, QVector<QVector<int>> textureFaceVerticesIndeces) :
    m_vertices(vertices), m_textureVertices(textureVertices), m_faceVerticesIndeces(faceVerticesIndeces), m_textureFaceVerticesIndeces(textureFaceVerticesIndeces) {
}

QVector<QVector3D> Mesh::getVertices()
{
    return m_vertices;
}

QVector<QVector2D> Mesh::getTextureVertices()
{
    return m_textureVertices;
}

QVector<QVector<int>> Mesh::getFaceVerticesIndeces()
{
    return m_faceVerticesIndeces;
}

QVector<QVector<int>> Mesh::getTextureFaceVerticesIndeces()
{
    return m_textureFaceVerticesIndeces;
}

/*QVector<QVector3D> calcBoundBox()
{

}*/
