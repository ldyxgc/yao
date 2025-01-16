#include <cstdint>
#include <map>
#include <memory>
#include <ostream>
#include <set>

#include "yao/com/integral.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/prt/c_f_print_value.hpp"

using namespace yao::com;
using yao::prt::PrintValueArgs;

struct Accept {
  void print_value(std::ostream &os, const PrintValueArgs &args,
                   uint indent_level) const;
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

static_assert(c_f_print_value<signed char> == true);
static_assert(c_f_print_value<unsigned char> == true);
static_assert(c_f_print_value<short> == true);
static_assert(c_f_print_value<unsigned short> == true);
static_assert(c_f_print_value<int> == true);
static_assert(c_f_print_value<unsigned> == true);
static_assert(c_f_print_value<long> == true);
static_assert(c_f_print_value<unsigned long> == true);
static_assert(c_f_print_value<long long> == true);
static_assert(c_f_print_value<unsigned long long> == true);

static_assert(c_f_print_value<Accept> == true);
static_assert(c_f_print_value<Reject> == false);

static_assert(c_f_print_value<std::set<std::int8_t>> == true);
static_assert(c_f_print_value<std::map<std::int8_t, std::uint8_t>> == true);

static_assert(c_f_print_value<std::unique_ptr<bool>> == true);
static_assert(c_f_print_value<std::shared_ptr<char>> == true);

int main() { return 0; }
