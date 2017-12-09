
template<typename T>
struct Complex
{
    Complex() :
        re_(),
        im_()
    {
        // Empty
    }

    explicit Complex(const T re, const T im = T()) :
        re_(re), im_(im)
    {
        // Empty
    }

    friend Complex operator+ (
        const Complex<T>& a, const Complex<T>& b)
    {
        Complex<T> ret;
        ret.re_ = a.re_ + b.re_;
        ret.im_ = a.im_ + b.im_;
        return ret;
    }

    friend Complex operator- (
        const Complex<T>& a, const Complex<T>& b)
    {
        Complex<T> ret;
        ret.re_ = a.re_ - b.re_;
        ret.im_ = a.im_ - b.im_;
        return ret;
    }

    friend Complex operator* (
        const Complex<T>& a, const Complex<T>& b)
    {
        Complex<T> ret;
        ret.re_ = (a.re_*b.re_ - a.im_*b.im_);
        ret.im_ = (a.im_*b.re_ + a.re_*b.im_);
        return ret;
    }

    friend Complex operator/ (
        const Complex<T>& a, const Complex<T>& b)
    {
        Complex<T> ret;
        T denominator = b.re_*b.re_ + b.im_*b.im_;
        ret.re_ = (a.re_*b.re_ + a.im_*b.im_) / denominator;
        ret.im_ = (a.im_*b.re_ - a.re_*b.im_) / denominator;
        return ret;
    }

    friend std::ostream& operator<< (std::ostream& os, const Complex& obj)
    {
        os << "(" << obj.re_ << "," << obj.im_ << ")";
        return os;
    }
    
    T re_;
    T im_;

}; // end Complex
