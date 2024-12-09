#include <memory>

#include "yao/def/check.hpp"
#include "yao/help.hpp"

template <typename T>
concept test = requires { yao::not_null<T>{}; };

int main() {

  YAO_CHECK(test<int> == false);

  YAO_CHECK(test<int *> == true);

  YAO_CHECK(test<std::unique_ptr<int>> == true);
  YAO_CHECK(test<std::shared_ptr<int>> == true);

  return 0;
}
