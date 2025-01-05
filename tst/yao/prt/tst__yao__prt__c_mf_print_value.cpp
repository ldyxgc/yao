#include <ostream>

#include "yao/prt/c_mf_print_value.hpp"

struct Accept1 {
  template <bool ns, bool tp> void print_value(std::ostream &os) const;
};
struct Reject1 {
  template <bool ns> void print_value(std::ostream &os) const;
  void print_value(std::ostream &os) const;
};

struct Reject2 {
  template <bool ns, bool tp> void print_value(std::ostream &os);
  template <bool ns> void print_value(std::ostream &os);
  void print_value(std::ostream &os);
};

struct Reject3 {
  template <bool ns, bool tp> static void print_value(std::ostream &os);
  template <bool ns> static void print_value(std::ostream &os);
  static void print_value(std::ostream &os);
};

struct Accept2 {
  void print_value(std::ostream &os, bool ns, bool tp) const;
};
struct Reject4 {
  void print_value(std::ostream &os, bool ns) const;
  void print_value(std::ostream &os) const;
};

struct Reject5 {
  void print_value(std::ostream &os, bool ns, bool tp);
  void print_value(std::ostream &os, bool ns);
  void print_value(std::ostream &os);
};

struct Reject6 {
  static void print_value(std::ostream &os, bool ns, bool tp);
  static void print_value(std::ostream &os, bool ns);
  static void print_value(std::ostream &os);
};

using yao::prt::c_mf_print_value;

static_assert(c_mf_print_value<int> == false);

static_assert(c_mf_print_value<Accept1> == true);
static_assert(c_mf_print_value<Reject1> == false);
static_assert(c_mf_print_value<Reject2> == false);
static_assert(c_mf_print_value<Reject3> == false);

static_assert(c_mf_print_value<Accept2> == true);
static_assert(c_mf_print_value<Reject4> == false);
static_assert(c_mf_print_value<Reject5> == false);
static_assert(c_mf_print_value<Reject6> == false);

int main() { return 0; }
