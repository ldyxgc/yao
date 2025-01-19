#include <cstdint>
#include <map>
#include <memory>
#include <ostream>
#include <set>

#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/c_f_print_type.hpp"

using yao::prt::PrintTypeArgs;

struct Accept {
  static void print_type(std::ostream &os, const PrintTypeArgs &args);
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

static_assert(c_f_print_type<signed char> == true);
static_assert(c_f_print_type<unsigned char> == true);
static_assert(c_f_print_type<short> == true);
static_assert(c_f_print_type<unsigned short> == true);
static_assert(c_f_print_type<int> == true);
static_assert(c_f_print_type<unsigned> == true);
static_assert(c_f_print_type<long> == true);
static_assert(c_f_print_type<unsigned long> == true);
static_assert(c_f_print_type<long long> == true);
static_assert(c_f_print_type<unsigned long long> == true);

static_assert(c_f_print_type<Accept> == true);
static_assert(c_f_print_type<Reject> == false);

static_assert(c_f_print_type<std::set<char>> == true);
static_assert(c_f_print_type<std::map<char, bool>> == true);

static_assert(c_f_print_type<std::unique_ptr<char>> == true);
static_assert(c_f_print_type<std::shared_ptr<char>> == true);

int main() { return 0; }
