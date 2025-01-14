#ifndef __YAO__RE__C_R_NO_CVREF_SYMBOL__HPP__
#define __YAO__RE__C_R_NO_CVREF_SYMBOL__HPP__

#include "yao/re/c_ct_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re {

// c: concept, r: require
template <typename Symbol>
concept c_r_no_cvref_Symbol = req::c_r_no_cvref<Symbol> && c_ct_Symbol<Symbol>;

} // namespace yao::re

#endif
