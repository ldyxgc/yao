#ifndef __YAO__RE__C_CT_SYMBOL__HPP__
#define __YAO__RE__C_CT_SYMBOL__HPP__

#include <compare>
#include <concepts>

namespace yao::re {

// c: concept, ct: conceptual type
template <typename Symbol>
concept c_ct_Symbol =
    std::totally_ordered<Symbol> && std::three_way_comparable<Symbol>;

} // namespace yao::re

#endif
