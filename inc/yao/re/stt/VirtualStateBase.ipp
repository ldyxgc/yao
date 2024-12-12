#ifndef __YAO__RE__STT__VIRTUAL_STATE_BASE__IPP__
#define __YAO__RE__STT__VIRTUAL_STATE_BASE__IPP__

#include "yao/re/stt/VirtualStateBase.hpp"

#include "yao/prt/osprint_type.hpp"

namespace yao::re::stt {

template <typename Symbol>
  requires c_t_Symbol<Symbol>
not_null<std::unique_ptr<VirtualStateBase<Symbol>>>
VirtualStateBase<Symbol>::copy_uptr() const {
  return std::unique_ptr<VirtualStateBase>{copy_rptr()};
}

template <typename Symbol>
  requires c_t_Symbol<Symbol>
template <bool ns, bool tp>
void VirtualStateBase<Symbol>::osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::re::stt::";
  os << "VirtualStateBase";
  if constexpr (tp) {
    os << '<';
    prt::osprint_type<Symbol, ns, tp>(os);
    os << '>';
  }
}

} // namespace yao::re::stt

#endif
