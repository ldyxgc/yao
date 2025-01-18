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

// -----------------------------------------------------------------------------

template <typename T>
concept test__not_null = requires { not_null<T>{}; };

static_assert(test__not_null<int *>);
static_assert(test__not_null<const int *>);
static_assert(test__not_null<std::unique_ptr<int>>);
static_assert(test__not_null<std::unique_ptr<const int>>);
static_assert(test__not_null<std::shared_ptr<int>>);
static_assert(test__not_null<std::shared_ptr<const int>>);

// -----------------------------------------------------------------------------

template <typename T>
concept test__owner = requires { owner<T>{}; };

static_assert(test__owner<int *>);
static_assert(test__owner<const int *>);

} // namespace yao

int main() { return 0; }
