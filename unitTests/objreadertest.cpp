#include "objreadertest.h"
#include "objreader.h"

namespace ObjReader::Tests {

void ObjReaderTest::testParseVertex()
{
    QVector3D vertex;
    QString errorMessage;

    parseVertex({"v", "1", "2", "3"}, vertex, errorMessage);
    QCOMPARE(vertex, QVector3D(1, 2, 3));

    parseVertex({"v", "-1", "-2", "-3"}, vertex, errorMessage);
    QCOMPARE(vertex, QVector3D(-1, -2, -3));

    parseVertex({"v", "0.01", "0.2", "3"}, vertex, errorMessage);
    QCOMPARE(vertex, QVector3D(0.01, 0.2, 3));

    parseVertex({"v", "1234", "-1023", "0"}, vertex, errorMessage);
    QCOMPARE(vertex, QVector3D(1234, -1023, 0));

    parseVertex({"v", "t", "2", "3"}, vertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid vertex coordinate t: ");

    parseVertex({"v", "1", "tt", "3"}, vertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid vertex coordinate tt: ");

    parseVertex({"v", "1", "2", "ttt"}, vertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid vertex coordinate ttt: ");

    parseVertex({}, vertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid amount of coordinates in line: ");

    parseVertex({"v"}, vertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid amount of coordinates in line: ");

    parseVertex({"v", "1"}, vertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid amount of coordinates in line: ");

    parseVertex({"v", "1", "3"}, vertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid amount of coordinates in line: ");
}

void ObjReaderTest::testParseTexture()
{
    QVector2D textureVertex;
    QString errorMessage;

    parseTextureVertex({"vt", "1", "2"}, textureVertex, errorMessage);
    QCOMPARE(textureVertex, QVector2D(1, 2));

    parseTextureVertex({"vt", "-1", "-2"}, textureVertex, errorMessage);
    QCOMPARE(textureVertex, QVector2D(-1, -2));

    parseTextureVertex({"vt", "0.01", "0.2"}, textureVertex, errorMessage);
    QCOMPARE(textureVertex, QVector2D(0.01, 0.2));

    parseTextureVertex({"vt", "-1023", "0"}, textureVertex, errorMessage);
    QCOMPARE(textureVertex, QVector2D(-1023, 0));

    parseTextureVertex({"vt", "t", "2"}, textureVertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid texture vertex coordinate t: ");

    parseTextureVertex({"vt", "1", "tt"}, textureVertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid texture vertex coordinate tt: ");

    parseTextureVertex({}, textureVertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid amount of coordinates in line: ");

    parseTextureVertex({"vt"}, textureVertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid amount of coordinates in line: ");

    parseTextureVertex({"vt", "1"}, textureVertex, errorMessage);
    QCOMPARE(errorMessage, "Invalid amount of coordinates in line: ");
}

void ObjReaderTest::testParseFaceVertexOnly()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"f", "1", "2", "3"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(verticesIndeces, QVector<int>({1, 2, 3}));
}

void ObjReaderTest::testParseFaceVertexTexture()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"f", "1/2", "2/4", "3/6"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(verticesIndeces, QVector<int>({1, 2, 3}));
    QCOMPARE(textureIndeces, QVector<int>({2, 4, 6}));
}

void ObjReaderTest::testParseFaceVertexNormal()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"f", "1//2", "2//4", "3//6"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(verticesIndeces, QVector<int>({1, 2, 3}));
    QCOMPARE(normalIndeces, QVector<int>({2, 4, 6}));
}

void ObjReaderTest::testParseFaceFull()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"f", "1/4/7", "2/5/8", "3/6/9"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(verticesIndeces, QVector<int>({1, 2, 3}));
    QCOMPARE(textureIndeces, QVector<int>({4, 5, 6}));
    QCOMPARE(normalIndeces, QVector<int>({7, 8, 9}));
}

void ObjReaderTest::testParseFaceFullAnother()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"f", "1/1/1", "2/2/2", "3/3/3", "4/4/4", "5/5/5", "6/6/6"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(verticesIndeces, QVector<int>({1, 2, 3, 4, 5, 6}));
    QCOMPARE(textureIndeces, QVector<int>({1, 2, 3, 4, 5, 6}));
    QCOMPARE(normalIndeces, QVector<int>({1, 2, 3, 4, 5, 6}));
}

void ObjReaderTest::testParseAmount()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"f", "1/4/7", "2/5/8"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(errorMessage, "Invalid amount of coordinates in polygone: ");
}

void ObjReaderTest::testReadObj()
{
    QString str = "v 1 2 3\n"
                  "v 2 3 4\n"
                  "v 2 6 5\n"
                  "vt 1 2\n"
                  "vt 3 4\n"
                  "vt 8 3\n"
                  "vn 0.1 0.5 0.2\n"
                  "vn 0.2 0.6 0.3\n"
                  "vn 0.6 0.3 0.9\n"
                  "f 1/1/1 2/2/2 3/3/3\n";
    QTextStream stream(&str);
    MyMesh::Mesh m;
    MyMesh::Mesh mComp({{1, 2, 3}, {2, 3, 4}, {2, 6, 5}}, {{1, 2}, {3, 4}, {8, 3}}, {{0.1, 0.5, 0.2}, {0.2, 0.6, 0.3}, {0.6, 0.3, 0.9}}, {{1, 2, 3}}, {{1, 2, 3}}, {{1, 2, 3}}, {-1}, {});
    readObj(stream, m);
    QCOMPARE(m, mComp);
}

void ObjReaderTest::testReadObjAnother()
{
    QString str = "v 1 2 3\n"
                  "v 2 3 4\n"
                  "v 2 6 5\n"
                  "vt 1 2\n"
                  "vt 3 4\n"
                  "vt 8 3\n"
                  "vn 0.1 0.5 0.2\n"
                  "vn 0.2 0.6 0.3\n"
                  "vn 0.6 0.3 0.9\n"
                  "g point\n"
                  "f 1/1/1 2/2/2 3/3/3\n";
    QTextStream stream(&str);
    MyMesh::Mesh m;
    MyMesh::Mesh mComp({{1, 2, 3}, {2, 3, 4}, {2, 6, 5}}, {{1, 2}, {3, 4}, {8, 3}}, {{0.1, 0.5, 0.2}, {0.2, 0.6, 0.3}, {0.6, 0.3, 0.9}}, {{1, 2, 3}}, {{1, 2, 3}}, {{1, 2, 3}}, {0}, {"point"});
    readObj(stream, m);
    QCOMPARE(m, mComp);
}

void ObjReaderTest::testReadFile()
{
    QString filePath = QFINDTESTDATA("modelexp.obj");
        MyMesh::Mesh m;
        MyMesh::Mesh mComp(
           {{1.000000, 1.000000, -1.000000},
            {1.000000, -1.000000, -1.000000},
            {-1.000000, -1.000000, -1.000000},
            {-1.000000, 1.000000, -1.000000},
            {1.000000, 1.000000, 1.000000},
            {1.000000, -1.000000, 1.000000},
            {-1.000000, -1.000000, 1.000000},
            {-1.000000, 1.000000, 1.000000}},

           {{0.000000, 0.000000},
            {1.000000, 0.000000},
            {1.000000, 1.000000},
            {0.000000, 1.000000}},

           {{0.000000, 0.000000, -1.000000},
            {0.000000, 0.000000, 1.000000},
            {1.000000, 0.000000, 0.000000},
            {-1.000000, 0.000000, 0.000000},
            {0.000000, 1.000000, 0.000000},
            {0.000000, -1.000000, 0.000000}},

           {{1, 2, 3, 4},
            {5, 6, 7, 8},
            {1, 5, 6, 2},
            {4, 8, 7, 3},
            {1, 4, 8, 5},
            {2, 3, 7, 6}},

           {{1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4}},

            {{1, 1, 1, 1},
            {2, 2, 2, 2},
            {3, 3, 3, 3},
            {4, 4, 4, 4},
            {5, 5, 5, 5},
            {6, 6, 6, 6}},

            {0, 0, 0, 0, 0, 0},

            {"cube"});

        readObj(filePath, m);
        QCOMPARE(m, mComp);
}
//fullline comment

} // namespace ObjReader
