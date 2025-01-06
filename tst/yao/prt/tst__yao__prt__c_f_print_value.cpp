#include <cstdint>
#include <map>
#include <memory>
#include <ostream>
#include <set>

#include "yao/prt/c_f_print_value.hpp"

struct Accept1 {
  template <bool ns, bool tp> void print_value(std::ostream &os) const;
};
struct Accept2 {
  void print_value(std::ostream &os, bool ns, bool tp) const;
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

static_assert(c_f_print_value<Accept1> == true);
static_assert(c_f_print_value<Accept2> == true);
static_assert(c_f_print_value<Reject> == false);

static_assert(c_f_print_value<std::set<std::int8_t>> == true);
static_assert(c_f_print_value<std::map<std::int8_t, std::uint8_t>> == true);

static_assert(c_f_print_value<std::unique_ptr<bool>> == true);
static_assert(c_f_print_value<std::shared_ptr<char>> == true);

int main() { return 0; }
