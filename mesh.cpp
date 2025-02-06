#include "mesh.h"

MyMesh::Mesh::Mesh(const QVector<QVector3D> &vertices, const QVector<QVector2D> &textureVertices, const QVector<QVector3D> &normals,
                   const QVector<QVector<int>> &faceVerticesIndices, const QVector<QVector<int>> &textureFaceVerticesIndices,
                   const QVector<QVector<int>> &normalIndices, const QVector<int> &groups, const QVector<QString> &groupNames)

{
    assert(!vertices.isEmpty());
    assert(!faceVerticesIndices.isEmpty());

    for (const QVector<int> &face : faceVerticesIndices) {
        for (int vertexIndex : face) {
            assert(vertexIndex > 0 && vertexIndex <= vertices.size());
        }
    }
    if (!textureVertices.isEmpty()) {
        for (const QVector<int> &textureFace : textureFaceVerticesIndices) {
            for (int textureIndex : textureFace) {
                assert(textureIndex > 0 && textureIndex <= textureVertices.size());
            }
        }
    }
    if (!normals.isEmpty()) {
        for (const QVector<int> &normalFace : normalIndices) {
            for (int normalIndex : normalFace) {
                assert(normalIndex > 0 && normalIndex <= normals.size());
            }
        }
    }

    m_vertices = vertices;
    m_textureVertices = textureVertices;
    m_normals = normals;
    m_faceVerticesIndices = faceVerticesIndices;
    m_textureFaceVerticesIndices = textureFaceVerticesIndices;
    m_normalIndices = normalIndices;
    m_groups = groups;
    m_groupNames = groupNames;
}

const QVector<QVector3D> &MyMesh::Mesh::Mesh::Vertices()
{
    return m_vertices;
}

const QVector<QVector2D> &MyMesh::Mesh::TextureVertices()
{
    return m_textureVertices;
}

const QVector<QVector<int>> &MyMesh::Mesh::FaceVerticesIndices()
{
    return m_faceVerticesIndices;
}

const QVector<QVector<int>> &MyMesh::Mesh::TextureFaceVerticesIndices()
{
    return m_textureFaceVerticesIndices;
}

const QVector<QString> &MyMesh::Mesh::Groups()
{
    return m_groupNames;
}

QVector<QVector3D> MyMesh::Mesh::calcBoundBox() const
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
            m_faceVerticesIndices == other.m_faceVerticesIndices &&
            m_textureFaceVerticesIndices == other.m_textureFaceVerticesIndices &&
            m_normalIndices == other.m_normalIndices &&
            m_groups == other.m_groups &&
            m_groupNames == other.m_groupNames);
 }
