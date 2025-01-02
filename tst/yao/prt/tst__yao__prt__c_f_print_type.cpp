#include <cstdint>
#include <ostream>

#include "yao/prt/c_f_print_type.hpp"

struct Accept {
  template <bool ns, bool tp> static void print_type(std::ostream &os);
};
struct Reject {};

using yao::prt::c_f_print_type;

static_assert(c_f_print_type<bool> == true);
static_assert(c_f_print_type<char> == true);

static_assert(c_f_print_type<std::int8_t> == true);
static_assert(c_f_print_type<std::uint8_t> == true);

static_assert(c_f_print_type<std::int16_t> == true);
static_assert(c_f_print_type<std::uint16_t> == true);

static_assert(c_f_print_type<std::int32_t> == true);
static_assert(c_f_print_type<std::uint32_t> == true);

static_assert(c_f_print_type<std::int64_t> == true);
static_assert(c_f_print_type<std::uint64_t> == true);

static_assert(c_f_print_type<Accept> == true);
static_assert(c_f_print_type<Reject> == false);

int main() { return 0; }
