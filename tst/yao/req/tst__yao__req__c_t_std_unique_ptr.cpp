#include <memory>

#include "yao/req/c_t_std_unique_ptr.hpp"

struct Object;

using yao::req::c_t_std_unique_ptr;

static_assert(!c_t_std_unique_ptr<int>);
static_assert(!c_t_std_unique_ptr<Object>);

static_assert(!c_t_std_unique_ptr<int *>);
static_assert(!c_t_std_unique_ptr<Object *>);
static_assert(!c_t_std_unique_ptr<std::shared_ptr<int>>);
static_assert(c_t_std_unique_ptr<std::unique_ptr<int>>);

static_assert(c_t_std_unique_ptr<std::unique_ptr<const int>>);
static_assert(c_t_std_unique_ptr<std::unique_ptr<volatile int>>);
static_assert(c_t_std_unique_ptr<std::unique_ptr<const volatile int>>);

static_assert(!c_t_std_unique_ptr<const std::unique_ptr<int>>);
static_assert(!c_t_std_unique_ptr<volatile std::unique_ptr<int>>);
static_assert(!c_t_std_unique_ptr<const volatile std::unique_ptr<int>>);

static_assert(!c_t_std_unique_ptr<int &>);
static_assert(!c_t_std_unique_ptr<int *&>);
static_assert(!c_t_std_unique_ptr<Object &>);
static_assert(!c_t_std_unique_ptr<Object *&>);
static_assert(!c_t_std_unique_ptr<std::unique_ptr<int> &>);
static_assert(!c_t_std_unique_ptr<std::shared_ptr<int> &>);

int main() { return 0; }
