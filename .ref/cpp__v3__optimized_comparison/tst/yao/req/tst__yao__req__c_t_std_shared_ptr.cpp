#include <memory>

#include "yao/req/c_t_std_shared_ptr.hpp"

struct Object;

using yao::req::c_t_std_shared_ptr;

static_assert(!c_t_std_shared_ptr<int>);
static_assert(!c_t_std_shared_ptr<Object>);

static_assert(!c_t_std_shared_ptr<int *>);
static_assert(!c_t_std_shared_ptr<Object *>);
static_assert(c_t_std_shared_ptr<std::shared_ptr<int>>);
static_assert(!c_t_std_shared_ptr<std::unique_ptr<int>>);

static_assert(c_t_std_shared_ptr<std::shared_ptr<const int>>);
static_assert(c_t_std_shared_ptr<std::shared_ptr<volatile int>>);
static_assert(c_t_std_shared_ptr<std::shared_ptr<const volatile int>>);

static_assert(!c_t_std_shared_ptr<const std::shared_ptr<int>>);
static_assert(!c_t_std_shared_ptr<volatile std::shared_ptr<int>>);
static_assert(!c_t_std_shared_ptr<const volatile std::shared_ptr<int>>);

static_assert(!c_t_std_shared_ptr<int &>);
static_assert(!c_t_std_shared_ptr<int *&>);
static_assert(!c_t_std_shared_ptr<Object &>);
static_assert(!c_t_std_shared_ptr<Object *&>);
static_assert(!c_t_std_shared_ptr<std::unique_ptr<int> &>);
static_assert(!c_t_std_shared_ptr<std::shared_ptr<int> &>);

int main() { return 0; }
