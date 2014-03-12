#include "tester.h"

#include <QDateTime>
#include "../time_delta.h"

Tester::Tester()
{}

void Tester::construct()
{
  const qint64 days = 12,
               hours = days * 24,
               minutes = hours * 60,
               seconds = minutes * 60,
               milisec = seconds * 1000,
               microsec = milisec * 1000;

  QCOMPARE(TimeDelta().InMicroseconds(), 0);
  QCOMPARE(TimeDelta::FromDays(days), TimeDelta::FromHours(hours));
  QCOMPARE(TimeDelta::FromHours(hours), TimeDelta::FromMinutes(minutes));
  QCOMPARE(TimeDelta::FromMinutes(minutes), TimeDelta::FromSeconds(seconds));
  QCOMPARE(TimeDelta::FromSeconds(seconds), TimeDelta::FromMilliseconds(milisec));
  QCOMPARE(TimeDelta::FromMilliseconds(milisec), TimeDelta::FromMicroseconds(microsec));

  QCOMPARE(TimeDelta::FromDays(days).InDays(), days);
  QCOMPARE(TimeDelta::FromHours(hours).InHours(), hours);
  QCOMPARE(TimeDelta::FromMinutes(minutes).InMinutes(), minutes);
  QCOMPARE(TimeDelta::FromSeconds(seconds).InSeconds(), seconds);
  QCOMPARE(TimeDelta::FromMilliseconds(milisec).InMilliseconds(), milisec);
  QCOMPARE(TimeDelta::FromMicroseconds(microsec).InMicroseconds(), microsec);

  TimeDelta original_delta = TimeDelta::FromMilliseconds(Q_INT64_C(324805423423));
  TimeDelta serialized_delta = TimeDelta::FromInternalValue(original_delta.ToInternalValue());
  QCOMPARE(original_delta, serialized_delta);
}

void Tester::operators_with_another_delta()
{
  TimeDelta init_by_static_method = TimeDelta::FromSeconds(333480);
  TimeDelta init_by_copy_ctor(init_by_static_method);
  TimeDelta assigned;
  assigned = init_by_static_method;
  QVERIFY(init_by_static_method == init_by_copy_ctor);
  QVERIFY(init_by_static_method == assigned);

  const qint64 usec1 = Q_INT64_C(32425893495);
  const qint64 usec2 = Q_INT64_C(72332423427);

  TimeDelta td1 = TimeDelta::FromMicroseconds(usec1);
  TimeDelta td2 = TimeDelta::FromMicroseconds(usec2);
  TimeDelta sub_res = td2 - td1;
  QCOMPARE(sub_res.InMicroseconds(), usec2 - usec1);

  TimeDelta negative_sub_res = td1 - td2;
  QCOMPARE((-sub_res).InMicroseconds(), usec1 - usec2);
  QCOMPARE(negative_sub_res, -sub_res);

  QCOMPARE(negative_sub_res + sub_res, TimeDelta());
  QCOMPARE((td1 + td2).InMicroseconds(), usec1 + usec2);

  TimeDelta simple_sum,
            increment = td1;
  simple_sum = td1 + td2;
  increment += td2;
  QCOMPARE(simple_sum, increment);

  TimeDelta decrement = td2;
  decrement -= td1;
  QCOMPARE(sub_res, decrement);
}

void Tester::comparision_operators()
{
  TimeDelta td1 = TimeDelta::FromMilliseconds(Q_INT64_C(9226737));
  TimeDelta td2 = TimeDelta::FromMilliseconds(Q_INT64_C(236234));
  QVERIFY(td1 > td2);
  QVERIFY(td2 < td1);
  QVERIFY(td1 >= td1);
  QVERIFY(td1 >= td2);
  QVERIFY(td2 <= td1);
  QVERIFY(td2 <= td2);
  QVERIFY(td1 == td1);
  QVERIFY(td1 != td2);
}

void Tester::operators_with_int()
{
  const qint64 usec = Q_INT64_C(32345346);
  const qint64 k = Q_INT64_C(7);

  TimeDelta td = TimeDelta::FromMicroseconds(usec);
  QCOMPARE(td * k, TimeDelta::FromMicroseconds(usec * k));
  QCOMPARE(k * td, TimeDelta::FromMicroseconds(usec * k));
  QCOMPARE(td / k, TimeDelta::FromMicroseconds(usec / k));

  td *= k;
  QCOMPARE(td, TimeDelta::FromMicroseconds(usec * k));

  td /= k;
  QCOMPARE(td, TimeDelta::FromMicroseconds(usec));

  TimeDelta td_with_k = td * k;
  QCOMPARE(td_with_k / td, k);
}

void Tester::operators_with_qdatetime()
{
  const int two = 2;
  QDateTime now = QDateTime::currentDateTime();
  QDateTime two_sec_later = now.addSecs(two);
  TimeDelta two_seconds = TimeDelta::FromSeconds(two);

  QCOMPARE(two_sec_later - now, two_seconds);
  QCOMPARE(now - two_sec_later, -two_seconds);
  QCOMPARE(now + two_seconds, two_sec_later);

  QDateTime test_dt = now;
  test_dt += two_seconds;
  QCOMPARE(test_dt, two_sec_later);
  test_dt -= two_seconds;
  QCOMPARE(test_dt, now);

  const int week_days = 7;
  QDate today = QDate::currentDate();
  QDate next_week = today.addDays(week_days);
  QCOMPARE(next_week - today, TimeDelta::FromDays(week_days));

  TimeDelta from_midnight = now - today;
  qint64 msecs_from_midnight = now.time().hour() * 60 * 60 * 1000 +
                               now.time().minute() * 60 * 1000 +
                               now.time().second() * 1000 +
                               now.time().msec();
  QCOMPARE(from_midnight.InMilliseconds(), msecs_from_midnight);
  QCOMPARE(today + from_midnight, now);
  QCOMPARE(from_midnight + today, now);

  QTime time_now = now.time();
  QTime time_two_sec_later = two_sec_later.time();

  QCOMPARE(time_two_sec_later - time_now, two_seconds);
  QCOMPARE(time_now - time_two_sec_later, -two_seconds);
}

