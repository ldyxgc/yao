#ifndef __YAO__LAB__RE__STT__STATE_BASE__HPP__
#define __YAO__LAB__RE__STT__STATE_BASE__HPP__

#include "yao/def/attr.hpp"

namespace yao::lab::re::stt {

template <typename State> class YAO_ATTR__EMPTY_BASES StateBase {
protected:
  StateBase();

public:
  auto operator<=>(const StateBase &rhs) const = default;
};

} // namespace yao::lab::re::stt

#include "yao/lab/re/stt/StateBase.ipp"

#endif
