#include "objreadertest.h"
#include "objreader.h"

namespace ObjReader::Test {
void ObjReaderTest::testParseVertex_data()
{
    QTest::addColumn<QVector3D>("coords");
    QTest::addColumn<QString>("errorMessage");
    QTest::addColumn<QVector3D>("resultCoords");
    QTest::addColumn<QString>("resultMessage");

    QVector3D vertex = {};
    QString errorMessage = "";
    parseVertex({"1", "2", "3"}, vertex, errorMessage);
    QTest::newRow("positiveNumbersVertex") << vertex << errorMessage << QVector3D(1, 2, 3) << "";

    vertex = {};
    errorMessage = "";
    parseVertex({"-1", "-2", "-3"}, vertex, errorMessage);
    QTest::newRow("negativeNumbersVertex") << vertex << errorMessage << QVector3D(-1, -2, -3) << "";

    vertex = {};
    errorMessage = "";
    parseVertex({"0.01", "0.2", "3"}, vertex, errorMessage);
    QTest::newRow("decimalNumbersVertex") << vertex << errorMessage << QVector3D(0.01, 0.2, 3) << "";

    vertex = {};
    errorMessage = "";
    parseVertex({"1234", "-1023", "0"}, vertex, errorMessage);
    QTest::newRow("complexNumbersVertex") << vertex << errorMessage << QVector3D(1234, -1023, 0) << "";

    vertex = {};
    errorMessage = "";
    parseVertex({"t", "2", "3"}, vertex, errorMessage);
    QTest::newRow("firstCoordInvalid") << vertex << errorMessage << QVector3D() << "Invalid character t, line ";

    vertex = {};
    errorMessage = "";
    parseVertex({"1", "tt", "3"}, vertex, errorMessage);
    QTest::newRow("secondCoordInvalid") << vertex << errorMessage << QVector3D(1, 0, 0) << "Invalid character tt, line ";

    vertex = {};
    errorMessage = "";
    parseVertex({"1", "2", "ttt"}, vertex, errorMessage);
    QTest::newRow("thirdCoordInvalid") << vertex << errorMessage << QVector3D(1, 2, 0) << "Invalid character ttt, line ";

    vertex = {};
    errorMessage = "";
    parseVertex({}, vertex, errorMessage);
    QTest::newRow("zeroCoord") << vertex << errorMessage << QVector3D() << "Invalid amount of coordinates, line ";

    vertex = {};
    errorMessage = "";
    parseVertex({"1"}, vertex, errorMessage);
    QTest::newRow("oneCoord") << vertex << errorMessage << QVector3D() << "Invalid amount of coordinates, line ";

    vertex = {};
    errorMessage = "";
    parseVertex({"1", "3"}, vertex, errorMessage);
    QTest::newRow("twoCoords") << vertex << errorMessage << QVector3D() << "Invalid amount of coordinates, line ";
}

void ObjReaderTest::testParseVertex()
{
    QFETCH(QVector3D, coords);
    QFETCH(QString, errorMessage);
    QFETCH(QVector3D, resultCoords);
    QFETCH(QString, resultMessage);

    QCOMPARE(coords, resultCoords);
    QCOMPARE(errorMessage, resultMessage);
}

void ObjReaderTest::testParseTexture_data()
{
    QTest::addColumn<QVector2D>("tCoords");
    QTest::addColumn<QString>("errorMessage");
    QTest::addColumn<QVector2D>("resultTCoords");
    QTest::addColumn<QString>("resultMessage");

    QVector2D textureVertex = {};
    QString errorMessage = "";
    parseTextureVertex({"1", "2"}, textureVertex, errorMessage);
    QTest::newRow("positiveNumbersTextures") << textureVertex << errorMessage << QVector2D(1, 2) << "";

    textureVertex = {};
    errorMessage = "";
    parseTextureVertex({"-1", "-2"}, textureVertex, errorMessage);
    QTest::newRow("negativeNumbersTextures") << textureVertex << errorMessage << QVector2D(-1, -2) << "";

    textureVertex = {};
    errorMessage = "";
    parseTextureVertex({"0.01", "0.2"}, textureVertex, errorMessage);
    QTest::newRow("decimalNumbersTextures") << textureVertex << errorMessage << QVector2D(0.01, 0.2) << "";

    textureVertex = {};
    errorMessage = "";
    parseTextureVertex({"t", "2"}, textureVertex, errorMessage);
    QTest::newRow("firstTextureCoordInvalid") << textureVertex << errorMessage << QVector2D() << "Invalid character t, line ";

    textureVertex = {};
    errorMessage = "";
    parseTextureVertex({"1", "tt"}, textureVertex, errorMessage);
    QTest::newRow("secondTextureCoordInvalid") << textureVertex << errorMessage << QVector2D(1, 0) << "Invalid character tt, line ";

    textureVertex = {};
    errorMessage = "";
    parseTextureVertex({}, textureVertex, errorMessage);
    QTest::newRow("zeroTextureCoord") << textureVertex << errorMessage << QVector2D() << "Invalid amount of coordinates, line ";

    textureVertex = {};
    errorMessage = "";
    parseTextureVertex({"1"}, textureVertex, errorMessage);
    QTest::newRow("oneTextureCoord") << textureVertex << errorMessage << QVector2D() << "Invalid amount of coordinates, line ";
}

void ObjReaderTest::testParseTexture()
{
    QFETCH(QVector2D, tCoords);
    QFETCH(QString, errorMessage);
    QFETCH(QVector2D, resultTCoords);
    QFETCH(QString, resultMessage);

    QCOMPARE(tCoords, resultTCoords);
    QCOMPARE(errorMessage, resultMessage);
}

void ObjReaderTest::testParseFaceVertexOnly()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"1", "2", "3"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(verticesIndeces, QVector<int>({1, 2, 3}));
}

void ObjReaderTest::testParseFaceVertexTexture()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"1/2", "2/4", "3/6"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(verticesIndeces, QVector<int>({1, 2, 3}));
    QCOMPARE(textureIndeces, QVector<int>({2, 4, 6}));
}

void ObjReaderTest::testParseFaceVertexNormal()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"1//2", "2//4", "3//6"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(verticesIndeces, QVector<int>({1, 2, 3}));
    QCOMPARE(normalIndeces, QVector<int>({2, 4, 6}));
}

void ObjReaderTest::testParseFaceFull()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"1/4/7", "2/5/8", "3/6/9"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(verticesIndeces, QVector<int>({1, 2, 3}));
    QCOMPARE(textureIndeces, QVector<int>({4, 5, 6}));
    QCOMPARE(normalIndeces, QVector<int>({7, 8, 9}));
}

void ObjReaderTest::testParseFaceFull2()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"1/1/1", "2/2/2", "3/3/3", "4/4/4", "5/5/5", "6/6/6"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
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

    parseFace({"1/4/7", "2/5/8"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(errorMessage, "Invalid amount of coordinates in polygon, line: ");
}

void ObjReaderTest::testParseFaceStructure()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"1/2/5", "2//4", "3/2/3"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(errorMessage, "Number of texture vertices does not match the number of vertices, line ");
}

void ObjReaderTest::testParseFaceBrokenStructure()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"1/2/5", "2/2/4/6/3/2", "3/2/3"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(errorMessage, "Invalid amount of vertices indices, line ");
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
    MyMesh::Mesh actual;
    MyMesh::Mesh expected;
    expected.init({{1, 2, 3}, {2, 3, 4}, {2, 6, 5}}, {{1, 2}, {3, 4}, {8, 3}}, {{0.1, 0.5, 0.2}, {0.2, 0.6, 0.3}, {0.6, 0.3, 0.9}}, {{1, 2, 3}}, {{1, 2, 3}}, {{1, 2, 3}}, {-1}, {});
    readObj(stream, actual);
    QCOMPARE(actual, expected);
}

void ObjReaderTest::testReadObj2()
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
    MyMesh::Mesh actual;
    MyMesh::Mesh expected;
    expected.init({{1, 2, 3}, {2, 3, 4}, {2, 6, 5}}, {{1, 2}, {3, 4}, {8, 3}}, {{0.1, 0.5, 0.2}, {0.2, 0.6, 0.3}, {0.6, 0.3, 0.9}}, {{1, 2, 3}}, {{1, 2, 3}}, {{1, 2, 3}}, {0}, {"point"});
    readObj(stream, actual);
    QCOMPARE(actual, expected);
}

void ObjReaderTest::testReadFile()
{
    QString filePath = QFINDTESTDATA("modelexp.obj");
    MyMesh::Mesh actual;
    MyMesh::Mesh expected;
    expected.init(
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

                {0, 0, 0, 1, 1, 0},

                {"cube", "side"});

    readObj(filePath, actual);
    QCOMPARE(actual, expected);
}

void ObjReaderTest::testReadFileWithComms()
{
    QString filePath = QFINDTESTDATA("modelexp3.obj");
    MyMesh::Mesh actual;
    MyMesh::Mesh expected;
    expected.init(
                {{0.000000, 1.000000, 0.000000},
                 {-1.000000, -1.000000, 1.000000},
                 {1.000000, -1.000000, 1.000000},
                 {1.000000, -1.000000, -1.000000},
                 {-1.000000, -1.000000, -1.000000}},

                {{0.500000, 1.000000},
                 {0.000000, 0.000000},
                 {1.000000, 0.000000},
                 {1.000000, 0.000000},
                 {0.000000, 0.000000}},

                {{0.000000, 0.707107, 0.707107},
                 {-0.707107, -0.707107, 0.000000},
                 {0.707107, -0.707107, 0.000000},
                 {0.000000, -0.707107, -0.707107},
                 {-0.707107, -0.707107, 0.000000}},

                {{1, 2, 3},
                 {1, 3, 4},
                 {1, 4, 5},
                 {1, 5, 2}},

                {{1, 2, 3},
                 {1, 3, 4},
                 {1, 4, 5},
                 {1, 5, 2}},

                {{1, 2, 3},
                 {1, 3, 4},
                 {1, 4, 5},
                 {1, 5, 2}},

                {0, 0, 0, 0},

                {"pyramid"});

    readObj(filePath, actual);
    QCOMPARE(actual, expected);
}

void ObjReaderTest::testReadFileEmptyGroup()
{
    QString filePath = QFINDTESTDATA("modelexp2.obj");
    MyMesh::Mesh m;

    QString error = readObj(filePath, m);
    QCOMPARE(error, "Empty group was declared, line 27");
}

void ObjReaderTest::testWrapSameMesh()
{
    QString filePath = QFINDTESTDATA("Puff.obj");
    MyMesh::Mesh m;
    readObj(filePath, m);
    filePath = QFINDTESTDATA("Puff.obj");
    MyMesh::Mesh mCMP;
    readObj(filePath, mCMP);
    bool same = (m == mCMP);
    QCOMPARE(same, true);
}

void ObjReaderTest::testWrapDiffMesh()
{
    QString filePath = QFINDTESTDATA("Puff.obj");
    MyMesh::Mesh m;
    readObj(filePath, m);
    filePath = QFINDTESTDATA("Scream.obj");
    MyMesh::Mesh mCMP;
    readObj(filePath, mCMP);
    bool same = (m == mCMP);
    QCOMPARE(same, false);
}

} // namespace ObjReader

