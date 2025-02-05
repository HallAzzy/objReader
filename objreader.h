#ifndef OBJREADER_H
#define OBJREADER_H

#include <QTextStream>
#include <QFile>
#include "mesh.h"


namespace ObjReader {
    QString readObj(QTextStream &stream, MyMesh::Mesh &mesh);
    QString readObj(const QString &pathToFile, MyMesh::Mesh &mesh);
    void parseVertex(const QStringList &chars, QVector3D &vertex, QString &errorMassage);
    void parseTextureVertex(const QStringList &chars, QVector2D &textureVertex, QString &errorMassage);
    void parseFace(const QStringList &chars, QVector<int> &verticesIndeces, QVector<int> &textureVerticesIndeces, QVector<int> &normalIndeces, QString &errorMessage);
};

#endif // OBJREADER_H
