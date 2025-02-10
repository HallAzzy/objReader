#ifndef OBJREADER_OBJREADERTEST_H
#define OBJREADER_OBJREADERTEST_H

#include <QTest>

namespace ObjReader::Test {
    class ObjReaderTest : public QObject
    {
        Q_OBJECT

    public:
        ObjReaderTest() = default;

    private slots:
        void testParseVertex_data();
        void testParseVertex();
        void testParseTexture_data();
        void testParseTexture();
        void testParseFaceVertexOnly();
        void testParseFaceVertexTexture();
        void testParseFaceVertexNormal();
        void testParseFaceFull();
        void testParseAmount();
        void testParseFaceFull2();
        void testParseFaceStructure();
        void testParseFaceBrokenStructure();
        void testReadObj();
        void testReadObj2();
        void testReadFile();
        void testReadFileWithComms();
        void testReadFileEmptyGroup();
        void testWrapSameMesh();
        void testWrapDiffMesh();
    };
}

#endif // OBJREADER_OBJREADERTEST_H
