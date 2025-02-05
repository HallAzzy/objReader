#ifndef OBJREADER_OBJREADERTEST_H
#define OBJREADER_OBJREADERTEST_H

#include <QTest>

namespace ObjReader::Tests {
    class ObjReaderTest : public QObject
    {
        Q_OBJECT

    public:
        ObjReaderTest() = default;

    private slots:
        void testParseVertex();
        void testParseTexture();
        void testParseFaceVertexOnly();
        void testParseFaceVertexTexture();
        void testParseFaceVertexNormal();
        void testParseFaceFull();
        void testParseAmount();
        void testParseFaceFullAnother();
        void testReadObj();
        void testReadObjAnother();
        void testReadFile();
    };
}

#endif // OBJREADER_OBJREADERTEST_H
