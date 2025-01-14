#ifndef __YAO__RE__STT__STATE_BASE__IPP__
#define __YAO__RE__STT__STATE_BASE__IPP__

#include "yao/re/stt/StateBase.hpp"

#include "yao/re/stt/c_ct_State.hpp"

namespace yao::re::stt {

template <typename State> StateBase<State>::StateBase() {
  static_assert(c_ct_State<State>);
}

} // namespace yao::re::stt

#endif
