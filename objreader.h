#ifndef OBJREADER_H
#define OBJREADER_H

#include <QTextStream>
#include <QFile>
#include <QTest>
#include "mesh.h"


namespace ObjReader
{
    QString readObj(const QString &pathToFile,  Mesh &mesh);
    QString parseToVertex(const QStringList &strl, QVector3D &vertex, QString &errorMassage);
    QString parseToTextureVertex(const QStringList &strl, QVector2D &textureVertex, QString &errorMassage);
    QString parseToFace(const QStringList &strl, QVector<int> &verticesIndex, QVector<int> &textureVerticesIndex, QString &errorMassage);

    class ObjReaderTest : public QObject
    {
        Q_OBJECT

    public:
        ObjReaderTest() = default;

    private slots:
        void testParseVertex();
    };
};

#endif // OBJREADER_H
