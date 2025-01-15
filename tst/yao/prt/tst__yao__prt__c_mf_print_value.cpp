#include <ostream>

#include "yao/prt/PrintValueArgs.hpp"
#include "yao/prt/c_mf_print_value.hpp"

using yao::prt::c_mf_print_value;
using yao::prt::PrintValueArgs;

struct Accept {
  void print_value(std::ostream &os, const PrintValueArgs &args) const;
};
struct Reject1 {
  void print_value(std::ostream &os) const;
};

struct Reject2 {
  void print_value(std::ostream &os, const PrintValueArgs &args);
  void print_value(std::ostream &os);
};

struct Reject3 {
  static void print_value(std::ostream &os, const PrintValueArgs &args);
  static void print_value(std::ostream &os);
};

static_assert(c_mf_print_value<int> == false);

static_assert(c_mf_print_value<Accept> == true);
static_assert(c_mf_print_value<Reject1> == false);
static_assert(c_mf_print_value<Reject2> == false);
static_assert(c_mf_print_value<Reject3> == false);

int main() { return 0; }
