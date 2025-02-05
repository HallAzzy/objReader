#include <QCoreApplication>
#include "QDebug"
#include "objreader.h"
#include "objreadertest.h"

int main()
{
    QVector3D vertex;
    QStringList lst = {"v", "5", "2", "2"};
    QString error = "Line ";
    ObjReader::parseVertex(lst, vertex, error);

    ObjReader::Tests::ObjReaderTest test;
    QTest::qExec(&test);
}
