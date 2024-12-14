#ifndef __YAO__LAB__RE__C_T_SYMBOL__HPP__
#define __YAO__LAB__RE__C_T_SYMBOL__HPP__

#include <concepts>

#include "yao/lab/prt/c_f_osprint_type.hpp"
#include "yao/lab/prt/c_f_osprint_value.hpp"

namespace yao::lab::re {

// c: concept, t: type
template <typename Symbol>
concept c_t_Symbol =
    std::totally_ordered<Symbol> && std::three_way_comparable<Symbol> &&
    prt::c_f_osprint_type<Symbol> && prt::c_f_osprint_value<Symbol>;

} // namespace yao::lab::re

#endif
