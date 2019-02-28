
template<typename T>
struct Complex
{
  constexpr Complex() :
    re_(),
    im_()
  {
    // Empty
  }

  constexpr Complex(const T re, const T im = T()) :
    re_(re), im_(im)
  {
    // Empty
  }

  T re_;
  T im_;
}; // end Complex

template<typename T>
Complex<T> operator+ (
    const Complex<T>& a, const Complex<T>& b)
{
  return Complex<T>(a.re_ + b.re_, a.im_ + b.im_);
}

template<typename T>
Complex<T> operator- (
    const Complex<T>& a, const Complex<T>& b)
{
  return Complex<T>(a.re_ - b.re_, a.im_ - b.im_);
}

template<typename T>
Complex<T> operator* (
    const Complex<T>& a, const Complex<T>& b)
{
  Complex<T> ret;
  ret.re_ = a.re_ * b.re_ - a.im_ * b.im_;
  ret.im_ = a.im_ * b.re_ + a.re_ * b.im_;
  return ret;
}

template<typename T>
Complex<T> operator/ (
    const Complex<T>& a, const Complex<T>& b)
{
  Complex<T> ret;
  T denominator = b.re_ * b.re_ + b.im_ * b.im_;
  ret.re_ = (a.re_ * b.re_ + a.im_ * b.im_) / denominator;
  ret.im_ = (a.im_ * b.re_ - a.re_ * b.im_) / denominator;
  return ret;
}

#ifndef AVR
template<typename T>
std::ostream& operator<< (std::ostream& os, const Complex<T>& obj)
{
  os << "(" << obj.re_ << "," << obj.im_ << ")";
  return os;
}
#endif

