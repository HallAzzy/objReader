#include "objreader.h"
#include <QDebug>

using namespace MyMesh;

QString ObjReader::readObj(const QTextStream &text, Mesh &mesh) {

}

QString ObjReader::readObj(const QString &pathToFile, Mesh &mesh)
{        
    QFile file(pathToFile);
    if (!file.open(QFile::ReadOnly)) {
        return "Cannot open the file!";
    }
    QTextStream stream(&file);
    QVector<QVector3D> vertices;
    QVector<QVector2D> textureVertices;
    QVector<QVector3D> normals;
    QVector<QVector<int>> faceVerticesIndeces;
    QVector<QVector<int>> textureFaceVerticesIndeces;
    QVector<QVector<int>> normalIndeces;
    QVector<int> groups;
    QVector<QString> groupNames;
    QString currentGroup;
    QString errorMessage;

    bool hasActiveGroup = false;
    int faceIndex = 0;

    while(!stream.atEnd()) {
        const QString line = stream.readLine();
        const QStringList parts = line.split(" ");
        const QString token = parts[0];
        if (token == "#")
            continue;
        if (token == "v") {
            QVector3D vertex;
            parseVertex(parts, vertex, errorMessage);
            if (!errorMessage.isEmpty())
                return errorMessage + line;
            vertices.append(vertex);
        }
        if (token == "vt") {
            QVector2D textureVertex;
            parseTextureVertex(parts, textureVertex, errorMessage);
            if (!errorMessage.isEmpty())
                return errorMessage + line;
            textureVertices.append(textureVertex);
        }
        if (token == "vn") {
            QVector3D norm;
            parseVertex(parts, norm, errorMessage);
            if (!errorMessage.isEmpty())
                return errorMessage + line;
            normals.append(norm);
        }
        if (token == "f") {
            QVector<int> vertexIndex;
            QVector<int> textureVertexIndex;
            QVector<int> normalIndex;
            parseFace(parts, vertexIndex, textureVertexIndex, normalIndex, errorMessage);
            if (!errorMessage.isEmpty())
                return errorMessage + line;
            faceVerticesIndeces.append(vertexIndex);
            textureFaceVerticesIndeces.append(textureVertexIndex);
            normalIndeces.append(normalIndex);
            if (hasActiveGroup) {
                groups[faceIndex] = groupNames.indexOf(currentGroup);
            }
            faceIndex++;
        }
        if (token == "g") {
            currentGroup = parts[1];
            groupNames.append(currentGroup);
            hasActiveGroup = true;
        }
    }
    file.close();
    mesh = Mesh(vertices, textureVertices, faceVerticesIndeces, textureFaceVerticesIndeces);
    return errorMessage;
}

void ObjReader::parseVertex(const QStringList &chars, QVector3D &outVertex, QString &errorMessage)
{
    if (chars.size() != 4) {
        errorMessage = QString("Invalid amount of coordinates in line: ");
        return;
    }
    bool isOk =  true;
    for (int i = 1; i < 4; i++) {
        outVertex[i - 1] = chars[i].toFloat(&isOk);
        if (!isOk) {
            errorMessage = QString("Invalid vertex coordinate %1: ").arg(chars[i]);
        }
    }
}

void ObjReader::parseTextureVertex(const QStringList &chars, QVector2D &outTextureVertex, QString &errorMessage)
{
    if (chars.size() != 3) {
        errorMessage = QString("Invalid amount of coordinates in line: ");
        return;
    }
    bool isOk = true;
    for (int i = 1; i < 3; i++) {
        outTextureVertex[i - 1] = chars[i].toFloat(&isOk);
        if (!isOk) {
            errorMessage = QString("Invalid texture vertex coordinate %1: ").arg(chars[i]);
        }
    }
}

void ObjReader::parseFace(const QStringList &chars, QVector<int> &verticesIndeces, QVector<int> &textureVerticesIndeces, QVector<int> &normalIndeces, QString &errorMessage)
{
    if (chars.size() < 4) {
        errorMessage = QString("Invalid amount of coordinates in polygone: ");
        return;
    }
    bool isOk = true;
    for (const QString &character : chars) {
        if (character.contains('f'))
            continue;
        if (character.contains('/')) {
            const QStringList blocks = character.split('/');
            verticesIndeces.append(blocks[0].toInt(&isOk));
            if (!isOk) {
                errorMessage = QString("Invalid vertex index %1").arg(blocks[0]);
            }
            if (blocks.size() > 1 && !blocks[1].isEmpty()) {
                textureVerticesIndeces.append(blocks[1].toInt(&isOk));
                if (!isOk) {
                    errorMessage = QString("Invalid texture vertex index %1").arg(blocks[1]);
                }
            }
            if (blocks.size() > 2 && !blocks[2].isEmpty()) {
                normalIndeces.append(blocks[2].toInt(&isOk));
                if (!isOk) {
                    errorMessage = QString("Invalid normal index %1").arg(blocks[2]);
                }
            }
        } else {
            verticesIndeces.append(character.toInt(&isOk));
            if (!isOk) {
                errorMessage = QString("Invalid vertex index %1").arg(character);
            }
        }
    }
}
