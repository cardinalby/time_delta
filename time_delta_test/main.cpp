#include <QCoreApplication>

#include "..\time_delta.h"
#include "tester.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  QTest::qExec(new Tester, argc, argv);

  return a.exec();
}
