#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H

#include <cmath>

#ifndef __AVR__
#include <iostream>
#include <cstdint>
#endif

// Fixed point number with storage type T and fractional bits Q
template<typename T, int Q>
struct FixedPoint
{
  using value_type = T;

  constexpr FixedPoint() :
    value_(0)
  {
    // Empty
  }

  template<typename T1, int Q1>
  constexpr FixedPoint(const FixedPoint<T1, Q1>& other) :
    value_(Q1 > Q ?
      // Fractional bits are being dropped. Round up if necessary.
      // Note: First dropped bit is in position (1 << (Q - Q1 - 1))
      ((other.value_ + (1 << (Q1 - Q - 1))) >> (Q1 - Q)) :

      // Frational bits are not being dropped.
      (other.value_ << (Q - Q1)))
  {
    // Empty
  }

  constexpr FixedPoint(const double value) :
    value_(static_cast<T>(std::round(value * (1<<Q))))
  {
    // Empty
  }

  constexpr double toDouble() const
  {
    return static_cast<double>(value_) / (1<<Q);
  }

  T value_;
};

template<typename T>
struct wider;

template<>
struct wider<uint8_t> { using type = uint16_t; };

template<>
struct wider<int8_t> { using type = int16_t; };

template<>
struct wider<uint16_t> { using type = uint32_t; };

template<>
struct wider<int16_t> { using type = int32_t; };

template<>
struct wider<uint32_t> { using type = uint64_t; };

template<>
struct wider<int32_t> { using type = int64_t; };

template<typename T, int Q1, int Q2>
struct result_types
{
  using add = void;
  using sub = void;
  using mul = FixedPoint<typename wider<T>::type, Q1 + Q2>;
  using div = void;
};

template<typename T, int Q>
FixedPoint<T,Q> operator+ (
  const FixedPoint<T,Q>& a, const FixedPoint<T,Q>& b)
{
  FixedPoint<T,Q> ret;
  ret.value_ = a.value_ + b.value_;
  return ret;
}

template<typename T, int Q>
FixedPoint<T,Q> operator- (
  const FixedPoint<T,Q>& a, const FixedPoint<T,Q>& b)
{
  FixedPoint<T,Q> ret;
  ret.value_ = a.value_ - b.value_;
  return ret;
}

// Trailing return type! Heck yeah!
template<typename T, int Q1, int Q2>
auto operator*( const FixedPoint<T,Q1>& a, const FixedPoint<T,Q2>& b)
  -> typename result_types<T,Q1,Q2>::mul 
{
    using ret_type = typename result_types<T,Q1,Q2>::mul;
    using operand_type = typename result_types<T,Q1,Q2>::mul::value_type;
    ret_type ret;
    ret.value_ = static_cast<operand_type>(a.value_) * static_cast<operand_type>(b.value_);
    return ret;
}

template<typename T, int Q>
FixedPoint<T,Q> operator/ (
  const FixedPoint<T,Q>& a, const FixedPoint<T,Q>& b)
{
  FixedPoint<T,Q> ret;
  ret.value_ = (a.value_ / b.value_) << Q;
  return ret;
}

template<typename T, int Q>
bool operator== (
  const FixedPoint<T,Q>& a, const FixedPoint<T,Q>& b)
{
  return a.value_ == b.value_;
}


#ifndef __AVR__
template<typename T, int Q>
std::ostream& operator<< (std::ostream& os, const FixedPoint<T,Q>& obj)
{
  os << obj.toDouble();
  return os;
}
#endif

#endif  // FIXEDPOINT_H
