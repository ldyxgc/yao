#include <concepts>
#include <cstdint>

static_assert(std::same_as<std::int8_t, signed char>);
static_assert(std::same_as<std::uint8_t, unsigned char>);

static_assert(std::same_as<std::int16_t, short>);
static_assert(std::same_as<std::uint16_t, unsigned short>);

static_assert(std::same_as<std::int32_t, int>);
static_assert(std::same_as<std::uint32_t, unsigned>);

template <typename T>
concept is_long = std::same_as<T, long>;
template <typename T>
concept is_llong = std::same_as<T, long long>;
template <typename T>
concept is_ulong = std::same_as<T, unsigned long>;
template <typename T>
concept is_ullong = std::same_as<T, unsigned long long>;

static_assert((is_long<std::int64_t> && !is_llong<std::int64_t>) ||
              (!is_long<std::int64_t> && is_llong<std::int64_t>));
static_assert((is_ulong<std::uint64_t> && !is_ullong<std::uint64_t>) ||
              (!is_ulong<std::uint64_t> && is_ullong<std::uint64_t>));

int main() { return 0; }
