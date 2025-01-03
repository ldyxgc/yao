#include <map>

#include "yao/req/c_t_std_map.hpp"

struct Object;

using yao::req::c_t_std_map;

static_assert(!c_t_std_map<int>);
static_assert(!c_t_std_map<Object>);

static_assert(c_t_std_map<std::map<int, int>>);
static_assert(!c_t_std_map<std::map<int, int> &>);
static_assert(!c_t_std_map<const std::map<int, int>>);

int main() { return 0; }
