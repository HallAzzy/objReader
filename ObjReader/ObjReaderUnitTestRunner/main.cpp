#include <QCoreApplication>
#include "ObjReaderUnitTest/objreadertest.h"

int main()
{
    ObjReader::Test::ObjReaderTest test;
    return QTest::qExec(&test);

}
