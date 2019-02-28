
// Fixed point number with storage type T and fractional bits F
template<typename T, int F>
struct FixedPoint
{
  using value_type = T;

  constexpr FixedPoint() :
    value_(0)
  {
    // Empty
  }

  template<typename T1, int F1>
    constexpr FixedPoint(const FixedPoint<T1, F1>& other) :
      value_(F1 > F ? (other.value_ >> (F1 - F)) :
          (other.value_ << (F - F1)))
      {
        // Empty
      }

  constexpr FixedPoint(const double value) :
    value_(static_cast<T>(value * (1<<F)))
  {
    // Empty
  }

  double toDouble() const
  {
    return static_cast<double>(value_) / (1<<F);
  }

  T value_;
};

template<typename T, int F1, int F2>
struct result_types
{
  using add = void;
  using sub = void;
  using mul = void;
  using div = void;
};

template<int F1, int F2>
struct result_types<int16_t, F1, F2>
{
  using add = void;
  using sub = void;
  using mul = FixedPoint<int32_t, F1 + F2>;
  using div = void;
};

  template<typename T, int F>
FixedPoint<T,F> operator+ (
    const FixedPoint<T,F>& a, const FixedPoint<T,F>& b)
{
  FixedPoint<T,F> ret;
  ret.value_ = a.value_ + b.value_;
  return ret;
}

  template<typename T, int F>
FixedPoint<T,F> operator- (
    const FixedPoint<T,F>& a, const FixedPoint<T,F>& b)
{
  FixedPoint<T,F> ret;
  ret.value_ = a.value_ - b.value_;
  return ret;
}

// Trailing return type! Heck yeah!
  template<typename T, int F1, int F2>
auto operator*( const FixedPoint<T,F1>& a, const FixedPoint<T,F2>& b)
  -> typename result_types<T,F1,F2>::mul 
{
  typename result_types<T,F1,F2>::mul ret;
  ret.value_ = a.value_ * b.value_;
  return ret;
}

  template<typename T, int F>
FixedPoint<T,F> operator/ (
    const FixedPoint<T,F>& a, const FixedPoint<T,F>& b)
{
  FixedPoint<T,F> ret;
  ret.value_ = (a.value_ / b.value_) << F;
  return ret;
}

#ifndef AVR
  template<typename T, int F>
std::ostream& operator<< (std::ostream& os, const FixedPoint<T,F>& obj)
{
  os << obj.toDouble();
  return os;
}
#endif

