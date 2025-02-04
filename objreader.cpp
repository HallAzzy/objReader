#include "objreader.h"

#include <QDebug>

QString ObjReader::readObj(const QString &pathToFile, Mesh &mesh)
{        
    QFile file(pathToFile);
    file.open(QFile::ReadOnly);
    QTextStream stream(&file);

    QVector3D vertex;
    QVector2D textureVertex;
    QVector<int> vertexIndex;
    QVector<int> textureVertexIndex;
    QVector<QVector3D> vertices;
    QVector<QVector2D> textureVertices;
    QVector<QVector<int>> faceVerticesIndeces;
    QVector<QVector<int>> textureFaceVerticesIndeces;
    QString errorMessage;

    while(!stream.atEnd()) {
        const QString line = stream.readLine();
        const QStringList parts = line.split(" ");
        const QString token = parts[0];
        if (token == "v") {
            parseToVertex(parts, vertex, errorMessage);
            if (errorMessage.size() != 0)
                return errorMessage;
            vertices.append(vertex);
        }
        if (token == "vt") {
            parseToTextureVertex(parts, textureVertex, errorMessage);
            if (errorMessage.size() != 0)
                return errorMessage;
            vertices.append(vertex);
        }
        if (token == "f") {
            parseToFace(parts, vertexIndex, textureVertexIndex, errorMessage);
            if (errorMessage.size() != 0)
                return errorMessage;
            vertices.append(vertex);
        }
    }
    file.close();
    mesh = Mesh(vertices, textureVertices, faceVerticesIndeces, textureFaceVerticesIndeces);
    return errorMessage;
}

QString ObjReader::parseToVertex(const QStringList &chars, QVector3D &outVertex, QString &errorMessage)
{
    if (chars.size() != 4) {
        errorMessage = QString("Invalid amount of coordinates in line %1!").arg(chars[1]);
        return errorMessage;
    }
    bool isOk =  true;           
    outVertex.setX(chars[1].toFloat(&isOk));
    if (!isOk) {        
        errorMessage = QString("Invalid vertex coordinate %1!").arg(chars[1]);
        return errorMessage;
    }
    outVertex.setY(chars[2].toFloat(&isOk));
    if (!isOk) {
        errorMessage = QString("Invalid vertex coordinate %1!").arg(chars[2]);
        return errorMessage;
    }
    outVertex.setZ(chars[3].toFloat(&isOk));
    if (!isOk) {
        errorMessage = QString("Invalid vertex coordinate %1!").arg(chars[3]);
        return errorMessage;
    }
    return errorMessage;
}

QString ObjReader::parseToTextureVertex(const QStringList &chars, QVector2D &outTextureVertex, QString &errorMessage)
{
    bool isOk = true;
    outTextureVertex.setX(chars[1].toFloat(&isOk));
    if (!isOk) {
        errorMessage = QString("Invalid texture vertex coordinate %1!").arg(chars[1]);
        return errorMessage;
    }
    outTextureVertex.setY(chars[2].toFloat(&isOk));
    if (!isOk) {
        errorMessage = QString("Invalid texture vertex coordinate %1!").arg(chars[2]);
        return errorMessage;
    }
    return errorMessage;
}

QString ObjReader::parseToFace(const QStringList &chars, QVector<int> &verticesIndeces, QVector<int> &textureVerticesIndeces, QString &errorMessage)
{
    bool isOk = true;
    for (const QString &character : chars) {
        if (character.contains('/')) {
           const QStringList blocks = character.split('/');
           verticesIndeces.append(blocks[0].toInt(&isOk));
           if (!isOk) {
               errorMessage = QString("Invalid index in polygon: %1!").arg(blocks[0]);
               return errorMessage;
           }
           textureVerticesIndeces.append(blocks[1].toInt(&isOk));
           if (!isOk) {
               errorMessage.append("Invalid index in texture polygon!");
               return errorMessage;
           }
       } else {
           verticesIndeces.append(character.toInt(&isOk));
           if (!isOk) {
               errorMessage = QString("Invalid index in polygon: %1!").arg(character);
               return errorMessage;
           }
       }
    }
    return errorMessage;
}

/*void ObjReader::ObjReaderTest::testParseVertex()
{
    QVector3D vertex;
    QString errorMessage;

    QCOMPARE(vertex, QVector3D(1, 2, 3));

    QCOMPARE(vertex, QVector3D(-1, -2, -3));

    QCOMPARE(vertex, QVector3D(1, 2, 3));

    QCOMPARE(vertex, QVector3D(1, 2, 3));

    QCOMPARE(vertex, QVector3D(1, 2, 3));

    QCOMPARE(vertex, QVector3D(1, 2, 3));

}*/
