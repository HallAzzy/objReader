#include "mesh.h"

Mesh::Mesh(QVector<QVector3D> vertices, QVector<QVector2D> textureVertices, QVector<QVector<int>> faceVerticesIndeces, QVector<QVector<int>> textureFaceVerticesIndeces) :
    m_vertices(vertices), m_textureVertices(textureVertices), m_faceVerticesIndeces(faceVerticesIndeces), m_textureFaceVerticesIndeces(textureFaceVerticesIndeces) {
}
