#include "objreader.h"

#include <QDebug>

QString ObjReader::ObjReader(const QString &pathToFile, Mesh &mesh)
{        
    QFile file(pathToFile);
    file.open(QFile::ReadOnly);
    QTextStream stream(&file);

    QVector3D vertex;
    QVector2D textureVertex;
    QVector<int> verticesIndeces;
    QVector<int> textureVerticesIndeces;
    QString errorMessage;

    while(!stream.atEnd()) {
        QString line = stream.readLine();
        const QStringList parts = line.split(" ");
        const QString token = parts[0];
        if (token == "v")
            parseToVertex(parts, vertex, errorMessage);
        if (token == "vt")
            parseToTextureVertex(parts, textureVertex, errorMessage);
        if (token == "f")
            parseToFace(parts, verticesIndeces, textureVerticesIndeces, errorMessage);
    }

    if (errorMessage.size() == 0) {
        mesh.addVertex(vertex);
        mesh.addTextureVertex(textureVertex);
        mesh.addFace(verticesIndeces);
        mesh.addTextureFace(textureVerticesIndeces);
    }

    file.close();
    return errorMessage;
}

bool ObjReader::parseToVertex(const QStringList &strl, QVector3D &vertex, QString &errorMessage)
{
    /*if (strl.size() != 4) {
        errorMessage.append("Invalid amount of coordinates!");
        return false;
    }*/
    bool isOk =  true;
    vertex.setX(strl[1].toFloat(&isOk));
    if (!isOk) {
        errorMessage.append("Invalid vertex coordinate!");
        return false;
    }
    vertex.setY(strl[2].toFloat(&isOk));
    if (!isOk) {
        errorMessage.append("Invalid vertex coordinate!");
        return false;
    }
    vertex.setZ(strl[3].toFloat(&isOk));
    if (!isOk) {
        errorMessage.append("Invalid vertex coordinate!");
        return false;
    }
    return true;
}


bool ObjReader::parseToTextureVertex(const QStringList &strl, QVector2D &textureVertex, QString &errorMessage)
{
    bool isOk = true;
    textureVertex.setX(strl[1].toFloat(&isOk));
    if (!isOk) {
        errorMessage.append("Invalid texture vertex coordinate!");
        return false;
    }
    textureVertex.setY(strl[2].toFloat(&isOk));
    if (!isOk) {
        errorMessage.append("Invalid texture vertex coordinate!");
        return false;
    }
    return true;
}

bool ObjReader::parseToFace(const QStringList &strl, QVector<int> &verticesIndeces, QVector<int> &textureVerticesIndeces, QString &errorMessage)
{
    bool isOk = true;
    for (QString str : strl) {
        if (str.contains('/')) {
           const QStringList blocks = str.split('/');
           verticesIndeces.append(blocks[0].toInt(&isOk));
           if (!isOk) {
               errorMessage.append("Invalid index in polygon!");
               return false;
           }
           textureVerticesIndeces.append(blocks[1].toInt(&isOk));
           if (!isOk) {
               errorMessage.append("Invalid index in texture polygon!");
               return false;
           }
       } else {
           verticesIndeces.append(str.toInt(&isOk));
           if (!isOk) {
               errorMessage.append("Invalid index in polygon!");
               return false;
           }
       }
    }
    return true;
}

ObjReader::ObjReaderTest::ObjReaderTest()
{
}

void ObjReader::ObjReaderTest::testParseVertex()
{
    QVector3D vertex;
    QString errorMessage;

    QVERIFY(parseToVertex({"v", "1", "2", "3"}, vertex, errorMessage));
    QCOMPARE(vertex, QVector3D(1, 2, 3));

    QVERIFY(parseToVertex({"v", "-1", "-2", "-3"}, vertex, errorMessage));
    QCOMPARE(vertex, QVector3D(1, 2, 3));

    QVERIFY(parseToVertex({"v", "t", "2", "3"}, vertex, errorMessage));
    QCOMPARE(vertex, QVector3D(1, 2, 3));

    QVERIFY(parseToVertex({"v", "1", "a", "3"}, vertex, errorMessage));
    QCOMPARE(vertex, QVector3D(1, 2, 3));

    QVERIFY(parseToVertex({"v", "t", "2", "b"}, vertex, errorMessage));
    QCOMPARE(vertex, QVector3D(1, 2, 3));

    QVERIFY(parseToVertex({"v", "112", "12t", "3"}, vertex, errorMessage));
    QCOMPARE(vertex, QVector3D(1, 2, 3));

    QVERIFY(!parseToVertex({}, vertex, errorMessage));
}
