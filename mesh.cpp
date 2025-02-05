#include "mesh.h"

MyMesh::Mesh::Mesh(const QVector<QVector3D> &vertices, const QVector<QVector2D> &textureVertices, const QVector<QVector3D> &normals,
                   const QVector<QVector<int>> &faceVerticesIndeces, const QVector<QVector<int>> &textureFaceVerticesIndeces,
                   const QVector<QVector<int>> &normalIndeces, const QVector<int> &groups, const QVector<QString> &groupNames) :
    m_vertices(vertices), m_textureVertices(textureVertices), m_normals(normals), m_faceVerticesIndeces(faceVerticesIndeces),
    m_textureFaceVerticesIndeces(textureFaceVerticesIndeces), m_normalIndeces(normalIndeces), m_groups(groups), m_groupNames(groupNames)
{
}

const QVector<QVector3D> &MyMesh::Mesh::Mesh::getVertices()
{
    return m_vertices;
}

const QVector<QVector2D> &MyMesh::Mesh::getTextureVertices()
{
    return m_textureVertices;
}

const QVector<QVector<int>> &MyMesh::Mesh::getFaceVerticesIndeces()
{
    return m_faceVerticesIndeces;
}

const QVector<QVector<int>> &MyMesh::Mesh::getTextureFaceVerticesIndeces()
{
    return m_textureFaceVerticesIndeces;
}

const QVector<QString> &MyMesh::Mesh::getGroups()
{
    return m_groupNames;
}

QVector<QVector3D> MyMesh::Mesh::calcBoundBox()
{
    QVector<QVector3D> boundingBox;

    float minX = m_vertices[0].x();
    float minY = m_vertices[0].y();
    float minZ = m_vertices[0].z();
    float maxX = m_vertices[0].x();
    float maxY = m_vertices[0].y();
    float maxZ = m_vertices[0].z();

    for (const QVector3D &vertex : m_vertices) {
        if (vertex.x() < minX)
            minX = vertex.x();
        if (vertex.y() < minY)
            minY = vertex.y();
        if (vertex.z() < minZ)
            minZ = vertex.z();

        if (vertex.x() > maxX)
            maxX = vertex.x();
        if (vertex.y() > maxY)
            maxY = vertex.y();
        if (vertex.z() > maxZ)
            maxZ = vertex.z();
    }

    boundingBox.clear();
    boundingBox.append(QVector3D(minX, minY, minZ));
    boundingBox.append(QVector3D(maxX, maxY, maxZ));

    return boundingBox;
}

bool MyMesh::Mesh::operator==(const Mesh& other) const {
     return (m_vertices == other.m_vertices &&
            m_textureVertices == other.m_textureVertices &&
            m_normals == other.m_normals &&
            m_faceVerticesIndeces == other.m_faceVerticesIndeces &&
            m_textureFaceVerticesIndeces == other.m_textureFaceVerticesIndeces &&
            m_normalIndeces == other.m_normalIndeces &&
            m_groups == other.m_groups &&
            m_groupNames == other.m_groupNames);
 }
