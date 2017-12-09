
template<typename T, int N>
class FixedPoint
{
public:

    FixedPoint() :
        value_(0)
    {
        // Empty
    }

    FixedPoint(const T value) :
        value_(value)
    {
        // Empty
    }

    explicit FixedPoint(const double value) :
        value_(static_cast<T>(value * (1<<N)))
    {
        // Empty
    }

    double toDouble() const
    {
        return static_cast<double>(value_) / (1<<N);
    }

    friend FixedPoint operator+ (
        const FixedPoint<T,N>& a, const FixedPoint<T,N>& b)
    {
        FixedPoint<T,N> ret;
        ret.value_ = a.value_ + b.value_;
        return ret;
    }

    friend FixedPoint operator- (
        const FixedPoint<T,N>& a, const FixedPoint<T,N>& b)
    {
        FixedPoint<T,N> ret;
        ret.value_ = a.value_ - b.value_;
        return ret;
    }

    friend FixedPoint operator* (
        const FixedPoint<T,N>& a, const FixedPoint<T,N>& b)
    {
        FixedPoint<T,N> ret;
        ret.value_ = (a.value_ * b.value_) >> N;
        return ret;
    }

    friend FixedPoint operator/ (
        const FixedPoint<T,N>& a, const FixedPoint<T,N>& b)
    {
        FixedPoint<T,N> ret;
        ret.value_ = (a.value_ / b.value_) << N;
        return ret;
    }

    friend std::ostream& operator<< (std::ostream& os, const FixedPoint& obj)
    {
        os << obj.toDouble();
        return os;
    }


private:
    T value_;
};

