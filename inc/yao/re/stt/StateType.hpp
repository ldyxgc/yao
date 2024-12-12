#ifndef __YAO__RE__STT__STATE_TYPE__HPP__
#define __YAO__RE__STT__STATE_TYPE__HPP__

#include <concepts>
#include <ostream>

namespace yao {

namespace re::stt {

enum class StateType {
  EpsilonState,
  SymbolState,

  KleeneState,

  ConcatState,
  UnionState,
};

} // namespace re::stt

namespace prt {

template <typename T, bool ns = false, bool tp = false>
  requires std::same_as<T, re::stt::StateType>
void osprint_type(std::ostream &os);

template <bool ns = false, bool tp = false, typename T>
  requires std::same_as<T, re::stt::StateType>
void osprint_value(std::ostream &os, T state_type);

} // namespace prt

} // namespace yao

#include "yao/re/stt/StateType.ipp"

#endif
