#include <memory>

#include "yao/def/check.hpp"
#include "yao/help.hpp"

template <typename T>
concept test = requires { yao::owner<T>{}; };

int main() {

  YAO_CHECK(test<int> == false);

  YAO_CHECK(test<int *> == true);

  YAO_CHECK(test<std::unique_ptr<int>> == false);
  YAO_CHECK(test<std::shared_ptr<int>> == false);

  return 0;
}
