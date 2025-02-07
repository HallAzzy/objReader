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
        void testParseFaceFullAnother();
        void testParseFaceStructure();
        void testReadObj();
        void testReadObjAnother();
        void testReadFile();
        void testReadFileWithComms();
        void testReadFileEmptyGroup();
    };
}

#endif // OBJREADER_OBJREADERTEST_H
