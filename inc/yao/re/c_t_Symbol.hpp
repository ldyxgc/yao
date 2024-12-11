#ifndef __YAO__RE__C_T_SYMBOL__HPP__
#define __YAO__RE__C_T_SYMBOL__HPP__

#include <concepts>

#include "yao/prt/c_f_osprint_type.hpp"
#include "yao/prt/c_f_osprint_value.hpp"

namespace yao::re {

// c: concept, t: type
template <typename Symbol>
concept c_t_Symbol =
    std::equality_comparable<Symbol> && //
    prt::c_f_osprint_type<Symbol> && prt::c_f_osprint_value<Symbol>;

} // namespace yao::re

#endif
