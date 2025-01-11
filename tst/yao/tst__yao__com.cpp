#include "yao/com.hpp"

template <typename T>
concept test__not_null = requires { yao::not_null<T>{}; };

template <typename T>
concept test__owner = requires { yao::owner<T>{}; };

static_assert(test__not_null<yao::zstring>);
static_assert(test__not_null<yao::czstring>);
static_assert(test__not_null<std::unique_ptr<int>>);
static_assert(test__not_null<std::unique_ptr<const int>>);
static_assert(test__not_null<std::shared_ptr<int>>);
static_assert(test__not_null<std::shared_ptr<const int>>);

static_assert(test__owner<yao::zstring>);
static_assert(test__owner<yao::czstring>);

int main() { return 0; }
