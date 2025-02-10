#include <QCoreApplication>
#include "ObjReaderUnitTest/objreadertest.h"
#include "MeshUnitTest/meshtest.h"

int main()
{
    ObjReader::Test::ObjReaderTest oTest;
    MyMesh::Test::MeshTest mTest;
    return QTest::qExec(&mTest) + QTest::qExec(&oTest);
}
