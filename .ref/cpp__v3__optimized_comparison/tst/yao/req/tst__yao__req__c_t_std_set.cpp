#include <set>

#include "yao/req/c_t_std_set.hpp"

struct Object;

using yao::req::c_t_std_set;

static_assert(!c_t_std_set<int>);
static_assert(!c_t_std_set<Object>);

static_assert(c_t_std_set<std::set<int>>);
static_assert(!c_t_std_set<std::set<int> &>);
static_assert(!c_t_std_set<const std::set<int>>);

int main() { return 0; }
