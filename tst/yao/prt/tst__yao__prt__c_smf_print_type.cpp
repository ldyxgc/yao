#include <ostream>

#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/c_smf_print_type.hpp"

using yao::prt::c_smf_print_type;
using yao::prt::PrintTypeArgs;

struct Accept {
  static void print_type(std::ostream &os, const PrintTypeArgs &args);
};
struct Reject1 {
  static void print_type(std::ostream &os);
};

struct Reject2 {
  void print_type(std::ostream &os, const PrintTypeArgs &args);
  void print_type(std::ostream &os);
};

static_assert(c_smf_print_type<int> == false);

static_assert(c_smf_print_type<Accept> == true);
static_assert(c_smf_print_type<Reject1> == false);
static_assert(c_smf_print_type<Reject2> == false);

int main() { return 0; }
