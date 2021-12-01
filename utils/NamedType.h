template <typename T, typename Parameter>
class NamedType
{
public:
    explicit NamedType(T const& value) : value_(value) {}
    T& get() { return value_; }
    T const& get() const { return value_; }
private:
    T value_;
};

using Temperature = NamedType<double, struct TemperatureParameter>;
using Humidity    = NamedType<double, struct HumidityParameter   >;
