#include <QCoreApplication>
#include "MeshUnitTest/meshtest.h"

int main()
{
    MyMesh::Test::MeshTest test;
    return QTest::qExec(&test);
}
