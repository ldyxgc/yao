#include <sstream>

#include "yao/prt/print_format.hpp"

int main() {

  std::ostringstream oss;
  yao::prt::print_format(oss, nullptr);

  return 0;
}
