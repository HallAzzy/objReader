#include "mesh.h"

QString MyMesh::Mesh::init(
        const QVector<QVector3D> &vertices, const QVector<QVector2D> &textureVertices, const QVector<QVector3D> &normals,
        const QVector<QVector<int>> &faceVerticesIndices, const QVector<QVector<int>> &textureFaceVerticesIndices,
        const QVector<QVector<int>> &normalIndices, const QVector<int> &groups, const QVector<QString> &groupNames)
{
    if (vertices.isEmpty())
        return "Trying to initialize a mesh without vertices";
    if (faceVerticesIndices.isEmpty())
        return "Trying to initialize a mesh without polygons";

    for (const QVector<int> &face : faceVerticesIndices) {
        for (int vertexIndex : face) {
            if (!(vertexIndex > 0 && vertexIndex <= vertices.size()))
                return "No match for vertex in polygon";
        }
    }
    if (!textureVertices.isEmpty()) {
        for (const QVector<int> &textureFace : textureFaceVerticesIndices) {
            for (int textureIndex : textureFace) {
                if (!(textureIndex > 0 && textureIndex <= textureVertices.size()))
                    return "No match for texture vertex in polygon";
            }
        }
    }
    if (!normals.isEmpty()) {
        for (const QVector<int> &normalFace : normalIndices) {
            for (int normalIndex : normalFace) {
                if (!(normalIndex > 0 && normalIndex <= normals.size()))
                    return "No match for normal in polygon";
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
    m_meshBoundingBox = BoundingBox::fromVertices(vertices);

    return "";
}

const QVector<QVector3D> &MyMesh::Mesh::Mesh::vertices() const
{
    return m_vertices;
}

const QVector<QVector2D> &MyMesh::Mesh::textureVertices() const
{
    return m_textureVertices;
}

const QVector<QVector3D> &MyMesh::Mesh::normals() const
{
    return m_normals;
}

const QVector<QVector<int>> &MyMesh::Mesh::faceVerticesIndices() const
{
    return m_faceVerticesIndices;
}

const QVector<QVector<int>> &MyMesh::Mesh::textureFaceVerticesIndices() const
{
    return m_textureFaceVerticesIndices;
}

const QVector<QVector<int>> &MyMesh::Mesh::normalIndices() const
{
    return m_normalIndices;
}

const QVector<QString> &MyMesh::Mesh::groups() const
{
    return m_groupNames;
}

const MyMesh::BoundingBox &MyMesh::Mesh::meshBoundingBox() const
{
    return m_meshBoundingBox;
}

QVector<int> MyMesh::Mesh::buildPolygonVertexIndicesVector()
{
    QVector<int> indicesVector;
    for (QVector<int> polygon : m_faceVerticesIndices)
        for (int vertexId : polygon)
            indicesVector.append(vertexId);
    return indicesVector;
}

QVector<int> MyMesh::Mesh::buildPolygonStartsVector()
{
    QVector<int> startsVector;
    int i = 0;
    startsVector.append(0);
    for (QVector<int> polygon : m_faceVerticesIndices)
    {
        startsVector.append(polygon.size() + startsVector[i]);
        ++i;
    }
    return startsVector;
}

bool MyMesh::Mesh::operator==(const Mesh &other) const
{
    if (
            m_vertices.size() != other.m_vertices.size() ||
            m_textureVertices.size() != other.m_textureVertices.size() ||
            m_normals.size() != other.m_normals.size())
        return false;
    bool vEqual;
    for (int i = 0; i < m_vertices.size(); ++i)
    {
        vEqual = (
                    qFuzzyCompare(m_vertices[i].x(), other.m_vertices[i].x()) &&
                    qFuzzyCompare(m_vertices[i].y(), other.m_vertices[i].y()) &&
                    qFuzzyCompare(m_vertices[i].z(), other.m_vertices[i].z()));
        if (vEqual == false)
            return false;
    }
    if (m_textureVertices.size() != 0) {
        for (int i = 0; i < m_textureVertices.size(); ++i)
        {
            vEqual = (
                        qFuzzyCompare(m_textureVertices[i].x(), other.m_textureVertices[i].x()) &&
                        qFuzzyCompare(m_textureVertices[i].y(), other.m_textureVertices[i].y()));
            if (vEqual == false)
                return false;
        }
    }
    if (m_normals.size() != 0) {
        for (int i = 0; i < m_normals.size(); ++i)
        {
            vEqual = (
                        qFuzzyCompare(m_normals[i].x(), other.m_normals[i].x()) &&
                        qFuzzyCompare(m_normals[i].y(), other.m_normals[i].y()) &&
                        qFuzzyCompare(m_normals[i].z(), other.m_normals[i].z()));
            if (vEqual == false)
                return false;
        }
    }
    return (m_faceVerticesIndices == other.m_faceVerticesIndices &&
            m_textureFaceVerticesIndices == other.m_textureFaceVerticesIndices &&
            m_normalIndices == other.m_normalIndices &&
            m_groups == other.m_groups &&
            m_groupNames == other.m_groupNames &&
            m_meshBoundingBox == other.m_meshBoundingBox);
}
