#ifndef OBJREADER_H
#define OBJREADER_H

#include <QTextStream>
#include <QFile>
#include "mesh.h"


namespace ObjReader
{
    QString readObj(const QString &pathToFile,  Mesh &mesh);
    QString parseVertex(const QStringList &chars, QVector3D &vertex, QString &errorMassage);
    QString parseTextureVertex(const QStringList &chars, QVector2D &textureVertex, QString &errorMassage);
    QString parseFace(const QStringList &chars, QVector<int> &verticesIndeces, QVector<int> &textureVerticesIndeces, QVector<int> &normalIndeces, QString &errorMessage);
};

#endif // OBJREADER_H
