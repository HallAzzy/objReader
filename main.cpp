#include <QCoreApplication>
#include "QDebug"
#include "objreadertest.h"

int main()
{
    ObjReader::Test::ObjReaderTest test;
    return QTest::qExec(&test);
}
