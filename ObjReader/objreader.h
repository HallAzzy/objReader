#ifndef OBJREADER_H
#define OBJREADER_H

#include <QTextStream>
#include <QFile>
#include "Mesh/mesh.h"


namespace ObjReader {
QString readObj(QTextStream &stream, MyMesh::Mesh &mesh);
QString readObj(const QString &pathToFile, MyMesh::Mesh &mesh);
void parseVertex(const QStringList &chars, QVector3D &vertex, QString &errorMessage);
void parseTextureVertex(const QStringList &chars, QVector2D &textureVertex, QString &errorMessage);
void parseFace(const QStringList &chars, QVector<int> &verticesIndeces, QVector<int> &textureVerticesIndeces, QVector<int> &normalIndeces, QString &errorMessage);
void parseIndex(const QString& str, QVector<int>& container, QString& errorMessage);
void convertIndices(int elementCount, QVector<QVector<int>>& indices);
};

#endif // OBJREADER_H
