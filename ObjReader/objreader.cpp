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

void ObjReader::parseFace(const QStringList &chars, QVector<int> &verticesIndices, QVector<int> &textureVerticesIndices, QVector<int> &normalIndices, QString &errorMessage)
{
    if (chars.size() < 3) {
        errorMessage = QString("Invalid amount of coordinates in polygon, line: ");
        return;
    }
    bool isOk = true;
    for (const QString &character : chars) {
        if (character.contains('/')) {
            const QStringList blocks = character.split('/');
            if (blocks.size() > 3) {
                errorMessage = QString("Invalid amount of vertices indices, line ");
                return;
            }
            verticesIndices.append(blocks[0].toInt(&isOk));
            if (!isOk) {
                errorMessage = QString("Invalid character %1, line ").arg(blocks[0]);
                return;
            }
            if (blocks.size() > 1 && !blocks[1].isEmpty()) {
                textureVerticesIndices.append(blocks[1].toInt(&isOk));
                if (!isOk) {
                    errorMessage = QString("Invalid character %1, line ").arg(blocks[1]);
                    return;
                }
            }
            if (blocks.size() > 2 && !blocks[2].isEmpty()) {
                normalIndices.append(blocks[2].toInt(&isOk));
                if (!isOk) {
                    errorMessage = QString("Invalid character %1, line ").arg(blocks[2]);
                    return;
                }
            }
        } else {
            verticesIndices.append(character.toInt(&isOk));
            if (!isOk) {
                errorMessage = QString("Invalid character %1, line ").arg(character);
                return;
            }
        }
    }
    if (textureVerticesIndices.size() > 0 && textureVerticesIndices.size() != verticesIndices.size()) {
        errorMessage = QString("Number of texture vertices does not match the number of vertices, line ");
        return;
    }
    if (normalIndices.size() > 0 && normalIndices.size() != verticesIndices.size()) {
        errorMessage = QString("Number of normals does not match the number of vertices, line ");
        return;
    }
}
