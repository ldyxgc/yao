#include <cstdint>
#include <ostream>

#include "yao/prt/c_f_print_value.hpp"

struct Accept {
  template <bool ns, bool tp> void print_value(std::ostream &os) const;
};
struct Reject {};

using yao::prt::c_f_print_value;

static_assert(c_f_print_value<bool> == true);
static_assert(c_f_print_value<char> == true);

static_assert(c_f_print_value<std::int8_t> == true);
static_assert(c_f_print_value<std::uint8_t> == true);

static_assert(c_f_print_value<std::int16_t> == true);
static_assert(c_f_print_value<std::uint16_t> == true);

static_assert(c_f_print_value<std::int32_t> == true);
static_assert(c_f_print_value<std::uint32_t> == true);

static_assert(c_f_print_value<std::int64_t> == true);
static_assert(c_f_print_value<std::uint64_t> == true);

static_assert(c_f_print_value<Accept> == true);
static_assert(c_f_print_value<Reject> == false);

int main() { return 0; }
