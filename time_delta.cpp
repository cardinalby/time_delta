#include "time_delta.h"

namespace {

const qint64 kMillisecondsPerSecond = 1000;
const qint64 kMicrosecondsPerMillisecond = 1000;
const qint64 kMicrosecondsPerSecond = kMicrosecondsPerMillisecond *
                                            kMillisecondsPerSecond;
const qint64 kMicrosecondsPerMinute = kMicrosecondsPerSecond * 60;
const qint64 kMicrosecondsPerHour = kMicrosecondsPerMinute * 60;
const qint64 kMicrosecondsPerDay = kMicrosecondsPerHour * 24;
const qint64 kMicrosecondsPerWeek = kMicrosecondsPerDay * 7;
const qint64 kNanosecondsPerMicrosecond = 1000;
const qint64 kNanosecondsPerSecond = kNanosecondsPerMicrosecond *
                                           kMicrosecondsPerSecond;
}  // namespace

TimeDelta TimeDelta::FromDays(qint64 days)
{
  return TimeDelta(days * kMicrosecondsPerDay);
}

TimeDelta TimeDelta::FromHours(qint64 hours)
{
  return TimeDelta(hours * kMicrosecondsPerHour);
}

TimeDelta TimeDelta::FromMinutes(qint64 minutes)
{
  return TimeDelta(minutes * kMicrosecondsPerMinute);
}

TimeDelta TimeDelta::FromSeconds(qint64 secs)
{
  return TimeDelta(secs * kMicrosecondsPerSecond);
}

TimeDelta TimeDelta::FromMilliseconds(qint64 ms)
{
  return TimeDelta(ms * kMicrosecondsPerMillisecond);
}

TimeDelta TimeDelta::FromMicroseconds(qint64 us)
{
  return TimeDelta(us);
}

int TimeDelta::InDays() const {
  return static_cast<int>(delta_ / kMicrosecondsPerDay);
}

int TimeDelta::InHours() const {
  return static_cast<int>(delta_ / kMicrosecondsPerHour);
}

int TimeDelta::InMinutes() const {
  return static_cast<int>(delta_ / kMicrosecondsPerMinute);
}

double TimeDelta::InSecondsF() const {
  return static_cast<double>(delta_) / kMicrosecondsPerSecond;
}

qint64 TimeDelta::InSeconds() const {
  return delta_ / kMicrosecondsPerSecond;
}

double TimeDelta::InMillisecondsF() const {
  return static_cast<double>(delta_) / kMicrosecondsPerMillisecond;
}

qint64 TimeDelta::InMilliseconds() const {
  return delta_ / kMicrosecondsPerMillisecond;
}

qint64 TimeDelta::InMillisecondsRoundedUp() const {
  return (delta_ + kMicrosecondsPerMillisecond - 1) /
      kMicrosecondsPerMillisecond;
}

qint64 TimeDelta::InMicroseconds() const {
  return delta_;
}

TimeDelta TimeDelta::FromInternalValue(qint64 delta) {
  return TimeDelta(delta);
}

qint64 TimeDelta::ToInternalValue() const {
  return delta_;
}

TimeDelta& TimeDelta::operator =(const TimeDelta &other) {
  delta_ = other.delta_;
  return *this;
}

TimeDelta TimeDelta::operator +(const TimeDelta &other) const {
  return TimeDelta(delta_ + other.delta_);
}

bool TimeDelta::operator ==(const TimeDelta &other) const {
  return delta_ == other.delta_;
}

bool TimeDelta::operator !=(TimeDelta other) const {
  return delta_ != other.delta_;
}

bool TimeDelta::operator <(TimeDelta other) const {
  return delta_ < other.delta_;
}

bool TimeDelta::operator <=(TimeDelta other) const {
  return delta_ <= other.delta_;
}

bool TimeDelta::operator >(TimeDelta other) const {
  return delta_ > other.delta_;
}

bool TimeDelta::operator >=(TimeDelta other) const {
  return delta_ >= other.delta_;
}

TimeDelta& TimeDelta::operator +=(const TimeDelta &other) {
  delta_ += other.delta_;
  return *this;
}

TimeDelta &TimeDelta::operator -=(const TimeDelta &other) {
  delta_ -= other.delta_;
  return *this;
}

TimeDelta TimeDelta::operator -() const {
  return TimeDelta(-delta_);
}

TimeDelta TimeDelta::operator *(qint64 a) const {
  return TimeDelta(delta_ * a);
}

TimeDelta& TimeDelta::operator *=(qint64 a) {
  delta_ *= a;
  return *this;
}

TimeDelta& TimeDelta::operator /=(qint64 a) {
  delta_ /= a;
  return *this;
}

qint64 TimeDelta::operator /(const TimeDelta &a) const {
  return delta_ / a.delta_;
}

TimeDelta TimeDelta::operator /(qint64 a) const {
  return TimeDelta(delta_ / a);
}

TimeDelta TimeDelta::operator -(const TimeDelta &other) const {
  return TimeDelta(delta_ - other.delta_);
}

TimeDelta::TimeDelta(qint64 delta_us)
  : delta_(delta_us)
{}

TimeDelta operator * (qint64 a, TimeDelta delta)
{
  return delta * a;
}

QDateTime operator + (QDateTime dt, TimeDelta delta)
{
  return dt.addMSecs(delta.InMilliseconds());
}

QDateTime operator + (QDate d, TimeDelta delta)
{
  return QDateTime(d) + delta;
}

QDateTime operator + (TimeDelta delta, QDateTime dt)
{
  return dt.addMSecs(delta.InMilliseconds());
}

QDateTime operator + (TimeDelta delta, QDate d)
{
  return QDateTime(d) + delta;
}

QDateTime operator - (QDateTime dt, TimeDelta delta)
{
  return dt.addMSecs(-1 * delta.InMilliseconds());
}

QDateTime operator - (QDate d, TimeDelta delta)
{
  return QDateTime(d) - delta;
}

QDateTime& operator += (QDateTime& dt, TimeDelta delta)
{
  return (dt = dt + delta);
}

QDateTime& operator -= (QDateTime& dt, TimeDelta delta)
{
  return (dt = dt - delta);
}

TimeDelta operator -(QDateTime dt_left, QDateTime dt_right)
{
  return TimeDelta::FromMilliseconds(dt_left.msecsTo(dt_right));
}

TimeDelta operator -(QDateTime dt_left, QDate d_right)
{
  return dt_left - QDateTime(d_right);
}

TimeDelta operator -(QDate d_left, QDateTime dt_right)
{
  return QDateTime(d_left) - dt_right;
}

TimeDelta operator -(QDate d_left, QDate d_right)
{
  return TimeDelta::FromDays(d_left.daysTo(d_right));
}

TimeDelta operator -(QTime t_left, QTime t_right)
{
  return TimeDelta::FromMilliseconds(t_left.msecsTo(t_right));
}
