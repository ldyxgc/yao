#include "yao/req/c_r_no_cvref.hpp"

using yao::req::c_r_no_cvref;

static_assert(c_r_no_cvref<int>);
static_assert(!c_r_no_cvref<int &>);
static_assert(!c_r_no_cvref<int &&>);
static_assert(!c_r_no_cvref<const int>);
static_assert(!c_r_no_cvref<volatile int>);

static_assert(c_r_no_cvref<int *>);
static_assert(!c_r_no_cvref<int *&>);
static_assert(!c_r_no_cvref<int *&&>);
static_assert(!c_r_no_cvref<int *const>);
static_assert(!c_r_no_cvref<int *volatile>);

static_assert(c_r_no_cvref<const int *>);
static_assert(!c_r_no_cvref<const int *&>);
static_assert(!c_r_no_cvref<const int *&&>);
static_assert(!c_r_no_cvref<const int *const>);
static_assert(!c_r_no_cvref<const int *volatile>);

static_assert(c_r_no_cvref<volatile int *>);
static_assert(!c_r_no_cvref<volatile int *&>);
static_assert(!c_r_no_cvref<volatile int *&&>);
static_assert(!c_r_no_cvref<volatile int *const>);
static_assert(!c_r_no_cvref<volatile int *volatile>);

int main() { return 0; }
