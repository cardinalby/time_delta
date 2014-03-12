#pragma once

#include <QObject>
#include <QTest>

class Tester: public QObject
{
  Q_OBJECT

  public:
    Tester();

  private slots:
    void construct();
    void operators_with_another_delta();
    void comparision_operators();
    void operators_with_int();
    void operators_with_qdatetime();
};
