#ifndef __YAO__RE__C_CT_SYMBOL__HPP__
#define __YAO__RE__C_CT_SYMBOL__HPP__

#include <compare>
#include <concepts>

#include "yao/prt/c_f_print_type.hpp"
#include "yao/prt/c_f_print_value.hpp"

namespace yao::re {

// c: concept, ct: conceptual type
template <typename Symbol>
concept c_ct_Symbol =
    std::totally_ordered<Symbol> && std::three_way_comparable<Symbol> &&
    prt::c_f_print_type<Symbol> && prt::c_f_print_value<Symbol>;

} // namespace yao::re

#endif
