#pragma once

#include <QtGlobal>

class QDateTime;
class QDate;
class QTime;

class TimeDelta
{
  public:
    TimeDelta();
    TimeDelta(const TimeDelta& other);

    // Converts units of time to TimeDeltas.
    static TimeDelta FromDays(qint64 days);
    static TimeDelta FromHours(qint64 hours);
    static TimeDelta FromMinutes(qint64 minutes);
    static TimeDelta FromSeconds(qint64 secs);
    static TimeDelta FromMilliseconds(qint64 ms);
    static TimeDelta FromMicroseconds(qint64 us);

    // Converts an integer value representing TimeDelta to a class. This is used
    // when deserializing a |TimeDelta| structure, using a value known to be
    // compatible. It is not provided as a constructor because the integer type
    // may be unclear from the perspective of a caller.
    static TimeDelta FromInternalValue(qint64 delta);

    // Returns the internal numeric value of the TimeDelta object. Please don't
    // use this and do arithmetic on it, as it is more error prone than using the
    // provided operators.
    // For serializing, use FromInternalValue to reconstitute.
    qint64 ToInternalValue() const;

    // Returns the time delta in some unit. The F versions return a floating
    // point value, the "regular" versions return a rounded-down value.
    //
    // InMillisecondsRoundedUp() instead returns an integer that is rounded up
    // to the next full millisecond.
    int InDays() const;
    int InHours() const;
    int InMinutes() const;
    double InSecondsF() const;
    qint64 InSeconds() const;
    double InMillisecondsF() const;
    qint64 InMilliseconds() const;
    qint64 InMillisecondsRoundedUp() const;
    qint64 InMicroseconds() const;

    TimeDelta& operator = (const TimeDelta& other);

    // Computations with other deltas.
    TimeDelta operator + (const TimeDelta& other) const;
    TimeDelta operator - (const TimeDelta& other) const;
    TimeDelta& operator += (const TimeDelta& other);
    TimeDelta& operator -= (const TimeDelta& other);
    TimeDelta operator - () const;

    // Computations with ints, note that we only allow multiplicative operations
    // with ints, and additive operations with other deltas.
    TimeDelta operator * (qint64 a) const;
    TimeDelta operator / (qint64 a) const;
    TimeDelta& operator *= (qint64 a);
    TimeDelta& operator /= (qint64 a);
    qint64 operator / (const TimeDelta& a) const;

    // Comparison operators.
    bool operator == (const TimeDelta& other) const;

    bool operator != (const TimeDelta& other) const;
    bool operator < (const TimeDelta& other) const;
    bool operator <= (const TimeDelta& other) const;
    bool operator > (const TimeDelta& other) const;
    bool operator >= (const TimeDelta& other) const;

  private:
    // Constructs a delta given the duration in microseconds. This is private
    // to avoid confusion by callers with an integer constructor. Use
    // FromSeconds, FromMilliseconds, etc. instead.
    explicit TimeDelta(qint64 delta_us);

    qint64 delta_;
};

TimeDelta operator * (qint64 a, TimeDelta delta);

// QDate after adding TimeDelta extends to QDateTime
QDateTime operator + (const QDateTime& dt, const TimeDelta& delta);
QDateTime operator + (const QDate& d, const TimeDelta& delta);
QDateTime operator + (const TimeDelta& delta, const QDateTime& dt);
QDateTime operator + (const TimeDelta& delta, const QDate& d);
QDateTime operator - (const QDateTime& dt, const TimeDelta& delta);
QDateTime operator - (const QDate& d, const TimeDelta& delta);

// Can't change QDate
QDateTime& operator += (QDateTime& dt, const TimeDelta& delta);
QDateTime& operator -= (QDateTime& dt, const TimeDelta& delta);

TimeDelta operator - (const QDateTime& dt_left, const QDateTime& dt_right);
TimeDelta operator - (const QDateTime& dt_left, const QDate& d_right);
TimeDelta operator - (const QDate& d_left, const QDateTime& dt_right);
TimeDelta operator - (const QDate& d_left, const QDate& d_right);
TimeDelta operator - (const QTime& t_left, const QTime& t_right);
