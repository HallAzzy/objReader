#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QString>

class Mesh
{
public:
    Mesh();
    void addVertex(QVector3D verticeCoord);
    void addTextureVertex(QVector2D verticeTextureCoord);
    void addFace(QVector<int>);
    void addTextureFace(QVector<int>);

private:
    QVector<QVector3D> vertices;
    QVector<QVector2D> textureVertices;
    QVector<QVector<int>> faceVerticesIndeces;
    QVector<QVector<int>>  textureFaceVerticesIndeces;
};

#endif // MESH_H
