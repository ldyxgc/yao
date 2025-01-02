#include <ostream>

#include "yao/prt/c_smf_print_type.hpp"

struct Accept {
  template <bool ns, bool tp> static void print_type(std::ostream &os);
};
struct Reject1 {
  template <bool ns> static void print_type(std::ostream &os);
  static void print_type(std::ostream &os);
};

struct Reject2 {
  template <bool ns, bool tp> void print_type(std::ostream &os);
  template <bool ns> void print_type(std::ostream &os);
  void print_type(std::ostream &os);
};

using yao::prt::c_smf_print_type;

static_assert(c_smf_print_type<int> == false);

static_assert(c_smf_print_type<Accept> == true);
static_assert(c_smf_print_type<Reject1> == false);
static_assert(c_smf_print_type<Reject2> == false);

int main() { return 0; }
