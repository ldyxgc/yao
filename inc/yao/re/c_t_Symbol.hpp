#ifndef __YAO__RE__C_T_SYMBOL__HPP__
#define __YAO__RE__C_T_SYMBOL__HPP__

#include "yao/prt/c_f_osprint_type.hpp"

namespace yao::re {

// c: concept, t: type
template <typename Symbol>
concept c_t_Symbol = prt::c_f_osprint_type<Symbol>;

} // namespace yao::re

#endif
