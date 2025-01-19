#include <memory>

#include "yao/req/c_t_pointer.hpp"

struct Object;

using yao::req::c_t_pointer;

static_assert(!c_t_pointer<int>);
static_assert(!c_t_pointer<Object>);

static_assert(c_t_pointer<int *>);
static_assert(c_t_pointer<Object *>);
static_assert(!c_t_pointer<std::shared_ptr<int>>);
static_assert(!c_t_pointer<std::unique_ptr<int>>);

static_assert(c_t_pointer<const int *>);
static_assert(c_t_pointer<volatile int *>);
static_assert(c_t_pointer<const volatile int *>);

static_assert(!c_t_pointer<int *const>);
static_assert(!c_t_pointer<int *volatile>);
static_assert(!c_t_pointer<int *const volatile>);

static_assert(!c_t_pointer<int &>);
static_assert(!c_t_pointer<int *&>);
static_assert(!c_t_pointer<Object &>);
static_assert(!c_t_pointer<Object *&>);
static_assert(!c_t_pointer<std::unique_ptr<int> &>);
static_assert(!c_t_pointer<std::shared_ptr<int> &>);

int main() { return 0; }
