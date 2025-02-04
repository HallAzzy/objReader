#include "mesh.h"

Mesh::Mesh()
{

}

void Mesh::addVertex(QVector3D verticeCoord)
{
    vertices.append(verticeCoord);
}

void Mesh::addTextureVertex(QVector2D verticeTextureCoord)
{
    textureVertices.append(verticeTextureCoord);
}

void Mesh::addFace(QVector<int> face)
{
    faceVerticesIndeces.append(face);
}

void Mesh::addTextureFace(QVector<int> textureFace)
{
    textureFaceVerticesIndeces.append(textureFace);
}
