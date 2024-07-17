#include <sallos/checksum.h>
#include <sallos/protocol_data.h>
#include <string>

enum class Target {

};

struct [[gnu::packed]] TestData {
    static constexpr unsigned short CMD_ID = 1.0;
    double yaw;
    double pitch;
    double roll;
    Target t;
};

template <ProtocolData T>
void Fun(T) {
    TestData d{};
    Fun(d);
    CheckSum<1> checker{};
    checker.Encode({1});
}
