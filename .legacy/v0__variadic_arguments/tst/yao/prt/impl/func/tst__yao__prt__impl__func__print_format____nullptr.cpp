#include <sstream>

#include "yao/prt/impl/func/print_format.hpp"

int main() {

  std::ostringstream oss;
  yao::prt::impl::func::print_format(oss, nullptr);

  return 0;
}
