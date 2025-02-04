#ifndef OBJREADER_H
#define OBJREADER_H

#include <QTextStream>
#include <QFile>
#include <QTest>
#include "mesh.h"


namespace ObjReader
{
    QString ObjReader(const QString &pathToFile,  Mesh &mesh);
    bool parseToVertex(const QStringList &strl, QVector3D &vertex, QString &errorMassage);
    bool parseToTextureVertex(const QStringList &strl, QVector2D &textureVertex, QString &errorMassage);
    bool parseToFace(const QStringList &strl, QVector<int> &verticesIndex, QVector<int> &textureVerticesIndex, QString &errorMassage);

    class ObjReaderTest : public QObject
    {
        Q_OBJECT

    public:
        ObjReaderTest();

    private slots:
        void testParseVertex();
    };
};

#endif // OBJREADER_H
