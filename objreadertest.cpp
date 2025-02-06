#include "objreadertest.h"
#include "objreader.h"

namespace ObjReader::Tests {
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
    QTest::newRow("firstCoordInvalid") << vertex << errorMessage << QVector3D() << "Invalid vertex coordinate t: ";

    vertex = {};
    errorMessage = "";
    parseVertex({"1", "tt", "3"}, vertex, errorMessage);
    QTest::newRow("secondCoordInvalid") << vertex << errorMessage << QVector3D(1, 0, 0) << "Invalid vertex coordinate tt: ";

    vertex = {};
    errorMessage = "";
    parseVertex({"1", "2", "ttt"}, vertex, errorMessage);
    QTest::newRow("thirdCoordInvalid") << vertex << errorMessage << QVector3D(1, 2, 0) << "Invalid vertex coordinate ttt: ";

    vertex = {};
    errorMessage = "";
    parseVertex({}, vertex, errorMessage);
    QTest::newRow("zeroCoord") << vertex << errorMessage << QVector3D() << "Invalid amount of coordinates in line: ";

    vertex = {};
    errorMessage = "";
    parseVertex({"1"}, vertex, errorMessage);
    QTest::newRow("oneCoord") << vertex << errorMessage << QVector3D() << "Invalid amount of coordinates in line: ";

    vertex = {};
    errorMessage = "";
    parseVertex({"1", "3"}, vertex, errorMessage);
    QTest::newRow("twoCoords") << vertex << errorMessage << QVector3D() << "Invalid amount of coordinates in line: ";
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
    QTest::newRow("firstTextureCoordInvalid") << textureVertex << errorMessage << QVector2D() << "Invalid texture vertex coordinate t: ";

    textureVertex = {};
    errorMessage = "";
    parseTextureVertex({"1", "tt"}, textureVertex, errorMessage);
    QTest::newRow("secondTextureCoordInvalid") << textureVertex << errorMessage << QVector2D(1, 0) << "Invalid texture vertex coordinate tt: ";

    textureVertex = {};
    errorMessage = "";
    parseTextureVertex({}, textureVertex, errorMessage);
    QTest::newRow("zeroTextureCoord") << textureVertex << errorMessage << QVector2D() << "Invalid amount of coordinates in line: ";

    textureVertex = {};
    errorMessage = "";
    parseTextureVertex({"1"}, textureVertex, errorMessage);
    QTest::newRow("oneTextureCoord") << textureVertex << errorMessage << QVector2D() << "Invalid amount of coordinates in line: ";
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

void ObjReaderTest::testParseFaceFullAnother()
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
    QCOMPARE(errorMessage, "Invalid amount of coordinates in polygon: ");
}

void ObjReaderTest::testParseFaceStructure()
{
    QVector<int> verticesIndeces;
    QVector<int> textureIndeces;
    QVector<int> normalIndeces;
    QString errorMessage;

    parseFace({"1/2/5", "2//4", "3/2/3"}, verticesIndeces, textureIndeces, normalIndeces, errorMessage);
    QCOMPARE(errorMessage, "Number of texture vertices does not match the number of vertices");
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

void ObjReaderTest::testReadFileWithComms()
{
    QString filePath = QFINDTESTDATA("modelexp3.obj");
    MyMesh::Mesh m;
    MyMesh::Mesh mComp(
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

    readObj(filePath, m);
    QCOMPARE(m, mComp);
}

void ObjReaderTest::testReadFileEmptyGroup()
{
    QString filePath = QFINDTESTDATA("modelexp2.obj");
        MyMesh::Mesh m;

        QString error = readObj(filePath, m);
        QCOMPARE(error, "Invalid group");
}

} // namespace ObjReader

