#ifndef __YAO__LAB__RE__STT__VIRTUAL_STATE_BASE__IPP__
#define __YAO__LAB__RE__STT__VIRTUAL_STATE_BASE__IPP__

#include "yao/lab/re/stt/VirtualStateBase.hpp"

#include "yao/lab/prt/osprint_type.hpp"

namespace yao::lab::re::stt {

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
    os << "yao::lab::re::stt::";
  os << "VirtualStateBase";
  if constexpr (tp) {
    os << '<';
    prt::osprint_type<Symbol, ns, tp>(os);
    os << '>';
  }
}

} // namespace yao::lab::re::stt

#endif
