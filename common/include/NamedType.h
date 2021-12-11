#ifndef NAMEDTYPE
#define NAMEDTYPE

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

using Temperature = NamedType<float, struct TemperatureParameter>;
using Humidity    = NamedType<float, struct HumidityParameter   >;

using DHTData  = NamedType<uint8_t, struct DHTDataParameter >;
using DHTType  = NamedType<uint8_t, struct DHTTypeParameter >;
using DHTPower = NamedType<uint8_t, struct DHTPowerParameter>;

using RadioNum   = NamedType<int16_t, struct RadioNumParameter  >;
using RadioPower = NamedType<int8_t, struct RadioPowerParameter>;
using MessageId  = NamedType<uint16_t, struct MessageIdParameter>;

#endif