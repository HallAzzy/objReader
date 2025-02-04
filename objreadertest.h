#ifndef OBJREADER_OBJREADERTEST_H
#define OBJREADER_OBJREADERTEST_H

#include <QTest>

namespace ObjReader {

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
};

} // namespace ObjReader

#endif // OBJREADER_OBJREADERTEST_H
