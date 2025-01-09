#ifndef __YAO__RE__STT__STATE_BASE__HPP__
#define __YAO__RE__STT__STATE_BASE__HPP__

#include "yao/def/attr.hpp"

namespace yao::re::stt {

template <typename State> class YAO_ATTR__EMPTY_BASES StateBase {
protected:
  StateBase();

  friend auto operator<=>(StateBase lhs, StateBase rhs) = default;
};

} // namespace yao::re::stt

#include "yao/re/stt/StateBase.ipp"

#endif
