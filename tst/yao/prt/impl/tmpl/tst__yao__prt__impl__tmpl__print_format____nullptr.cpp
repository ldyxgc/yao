#include <sstream>

#include "yao/prt/impl/tmpl/print_format.hpp"

int main() {

  std::ostringstream oss;
  yao::prt::impl::tmpl::print_format(oss, nullptr);

  return 0;
}
