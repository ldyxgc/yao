#ifndef __YAO__RE__STT__VIRTUAL_STATE__IPP__
#define __YAO__RE__STT__VIRTUAL_STATE__IPP__

#include "yao/re/stt/VirtualState.hpp"

#include "yao/prt/print_type.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
not_null<std::unique_ptr<VirtualState<_Symbol>>>
VirtualState<_Symbol>::copy_uptr() const {
  return std::unique_ptr<VirtualState>{copy_rptr()};
}

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
template <bool ns, bool tp>
void VirtualState<_Symbol>::print_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::";
  os << "VirtualState";
  if constexpr (tp) {
    os << '<';
    prt::print_type<Symbol, ns, tp>(os);
    os << '>';
  }
}

} // namespace yao::re::stt

#endif
