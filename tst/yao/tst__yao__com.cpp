#include <type_traits>

#include "yao/com.hpp"

namespace yao {

static_assert(std::is_integral_v<bool>);
static_assert(std::is_integral_v<char>);

static_assert(std::is_integral_v<schar>);
static_assert(std::is_integral_v<uchar>);

static_assert(std::is_integral_v<short>);
static_assert(std::is_integral_v<ushort>);

static_assert(std::is_integral_v<int>);
static_assert(std::is_integral_v<uint>);

static_assert(std::is_integral_v<long>);
static_assert(std::is_integral_v<ulong>);

static_assert(std::is_integral_v<llong>);
static_assert(std::is_integral_v<ullong>);

} // namespace yao

int main() { return 0; }
