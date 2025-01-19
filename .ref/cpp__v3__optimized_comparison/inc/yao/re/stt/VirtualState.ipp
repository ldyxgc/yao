#ifndef __YAO__RE__STT__VIRTUAL_STATE__IPP__
#define __YAO__RE__STT__VIRTUAL_STATE__IPP__

#include "yao/re/stt/VirtualState.hpp"

#include "yao/prt/print_type.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
not_null<std::unique_ptr<VirtualState<_Symbol>>>
VirtualState<_Symbol>::copy_uptr() const {
  return std::unique_ptr<VirtualState>{copy_rptr()};
}

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
void VirtualState<_Symbol>::print_type(std::ostream &os,
                                       const prt::PrintTypeArgs &args) {
  if (args.scope)
    os << "yao::re::stt::";
  os << "VirtualState";
  if (args.tmpl_args) {
    os << '<';
    prt::print_type<Symbol>(os, args);
    os << '>';
  }
}

} // namespace yao::re::stt

#endif
