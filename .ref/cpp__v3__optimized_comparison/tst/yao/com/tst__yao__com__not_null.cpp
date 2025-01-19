#include <memory>

#include "yao/com/not_null.hpp"

struct Object;

template <typename T>
concept test = requires { yao::com::not_null<T>{}; };

static_assert(!test<int>);
static_assert(!test<Object>);

static_assert(test<int *>);
static_assert(test<const int *>);
static_assert(!test<int *const>);

static_assert(test<std::unique_ptr<int>>);
static_assert(test<std::unique_ptr<const int>>);
static_assert(!test<const std::unique_ptr<int>>);

static_assert(test<std::shared_ptr<int>>);
static_assert(test<std::shared_ptr<const int>>);
static_assert(!test<const std::shared_ptr<int>>);

static_assert(!test<int &>);
static_assert(!test<int *&>);
static_assert(!test<Object &>);
static_assert(!test<Object *&>);
static_assert(!test<std::unique_ptr<int> &>);
static_assert(!test<std::shared_ptr<int> &>);

int main() { return 0; }
