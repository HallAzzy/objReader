#include "objreader.h"
#include <QDebug>

using namespace MyMesh;

QString ObjReader::readObj(QTextStream &stream, Mesh &mesh)
{
    QVector<QVector3D> vertices;
    QVector<QVector2D> textureVertices;
    QVector<QVector3D> normals;
    QVector<QVector<int>> faceVerticesIndices;
    QVector<QVector<int>> textureFaceVerticesIndices;
    QVector<QVector<int>> normalIndices;
    QVector<int> groups;
    QVector<QString> groupNames;
    QString currentGroup;
    QString errorMessage;

    bool hasActiveGroup = false;
    int faceIndex = 0;
    unsigned int lineNum = 0;

    while(!stream.atEnd()) {
        const QString line = stream.readLine();
        ++lineNum;
        if (line.isEmpty())
            continue;
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);
        const QString token = parts[0];
        parts.pop_front();
        if (token == "#")
            continue;
        for (int i = 0; i < parts.size(); ++i) {
            if (parts[i].startsWith("#")) {
                parts = parts.mid(0, i);
                break;
            }
        }
        if (token == "v") {
            QVector3D vertex;
            parseVertex(parts, vertex, errorMessage);
            if (!errorMessage.isEmpty())
                return errorMessage + QString::number(lineNum) + ": " + line.left(20);
            vertices.append(vertex);
        }
        if (token == "vt") {
            QVector2D textureVertex;
            parseTextureVertex(parts, textureVertex, errorMessage);
            if (!errorMessage.isEmpty())
                return errorMessage + QString::number(lineNum) + ": " + line.left(20);
            textureVertices.append(textureVertex);
        }
        if (token == "vn") {
            QVector3D norm;
            parseVertex(parts, norm, errorMessage);
            if (!errorMessage.isEmpty())
                return errorMessage + QString::number(lineNum) + ": " + line.left(20);
            normals.append(norm);
        }
        if (token == "f") {
            QVector<int> vertexIndex;
            QVector<int> textureVertexIndex;
            QVector<int> normalIndex;
            parseFace(parts, vertexIndex, textureVertexIndex, normalIndex, errorMessage);
            if (!errorMessage.isEmpty())
                return errorMessage + QString::number(lineNum) + ": " + line.left(20);
            faceVerticesIndices.append(vertexIndex);
            textureFaceVerticesIndices.append(textureVertexIndex);
            normalIndices.append(normalIndex);
            groups.append(-1);
            if (hasActiveGroup)
                groups[faceIndex] = groupNames.indexOf(currentGroup);
            ++faceIndex;
        }
        if (token == "g") {
            if (parts.isEmpty())
                return "Empty group was declared, line " + QString::number(lineNum);
            currentGroup = parts[0];
            if (groupNames.indexOf(currentGroup) == -1) {
                groupNames.append(currentGroup);
            }
            hasActiveGroup = true;
        }
    }
    mesh.init(vertices, textureVertices, normals, faceVerticesIndices, textureFaceVerticesIndices, normalIndices, groups, groupNames);
    return errorMessage;
}

QString ObjReader::readObj(const QString &pathToFile, Mesh &mesh)
{
    QFile file(pathToFile);
    if (!file.open(QFile::ReadOnly)) {
        return "Cannot open the file!";
    }
    QTextStream stream(&file);
    return readObj(stream, mesh);
}

void ObjReader::parseVertex(const QStringList &chars, QVector3D &outVertex, QString &errorMessage)
{
    if (chars.size() != 3) {
        errorMessage = QString("Invalid amount of coordinates, line ");
        return;
    }
    bool isOk =  true;
    for (int i = 0; i < 3; i++) {
        outVertex[i] = chars[i].toFloat(&isOk);
        if (!isOk) {
            errorMessage = QString("Invalid character %1, line ").arg(chars[i]);
            return;
        }
    }
}

void ObjReader::parseTextureVertex(const QStringList &chars, QVector2D &outTextureVertex, QString &errorMessage)
{
    if (chars.size() != 2) {
        errorMessage = QString("Invalid amount of coordinates, line ");
        return;
    }
    bool isOk = true;
    for (int i = 0; i < 2; i++) {
        outTextureVertex[i] = chars[i].toFloat(&isOk);
        if (!isOk) {
            errorMessage = QString("Invalid character %1, line ").arg(chars[i]);
            return;
        }
    }
}

void ObjReader::convertIndices(int elementCount, QVector<QVector<int>>& indices)
{
    for (QVector<int>& faceIndices : indices) {
        for (int& index : faceIndices) {
            if (index < 0) {
                index = elementCount + index;
            } else {
                index--;
            }

            if (index < 0 || index >= elementCount) {
                index = 0;
            }
        }
    }
}

void ObjReader::parseFace(const QStringList &chars,
                          QVector<int> &verticesIndices,
                          QVector<int> &textureVerticesIndices,
                          QVector<int> &normalIndices,
                          QString &errorMessage)
{
    if (chars.size() < 3) {
        errorMessage = "Invalid amount of coordinates in polygon, line: ";
        return;
    }

    verticesIndices.reserve(chars.size());
    textureVerticesIndices.reserve(chars.size());
    normalIndices.reserve(chars.size());

    for (const QString &part : chars) {
        QStringList blocks = part.split('/', Qt::KeepEmptyParts);
        if (blocks.size() == 1) {
            parseIndex(blocks[0], verticesIndices, errorMessage);
        }
        else if (blocks.size() == 2) {
            parseIndex(blocks[0], verticesIndices, errorMessage);

            if (!blocks[1].isEmpty()) {
                parseIndex(blocks[1], textureVerticesIndices, errorMessage);
            }
            else {
            }
        }
        else if (blocks.size() == 3) {
            parseIndex(blocks[0], verticesIndices, errorMessage);

            if (!blocks[1].isEmpty()) {
                parseIndex(blocks[1], textureVerticesIndices, errorMessage);
            }

            parseIndex(blocks[2], normalIndices, errorMessage);
        }
        else {
            errorMessage = "Invalid face format, line: ";
            return;
        }

        if (!errorMessage.isEmpty()) return;
    }
}

void ObjReader::parseIndex(const QString& str, QVector<int>& container, QString& errorMessage)
{
    bool ok;
    int value = str.toInt(&ok);

    if (!ok) {
        errorMessage = "Invalid index format '" + str + "', line: ";
        return;
    }

    container.append(value);
}
