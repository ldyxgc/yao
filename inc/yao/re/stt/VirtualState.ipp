#ifndef __YAO__RE__STT__VIRTUAL_STATE__IPP__
#define __YAO__RE__STT__VIRTUAL_STATE__IPP__

#include "yao/re/stt/VirtualState.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
not_null<std::unique_ptr<VirtualState<_Symbol>>>
VirtualState<_Symbol>::copy_uptr() const {
  return std::unique_ptr<VirtualState>{copy_rptr()};
}

} // namespace yao::re::stt

#endif
