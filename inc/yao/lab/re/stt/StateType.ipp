#ifndef __YAO__LAB__RE__STT__STATE_TYPE__IPP__
#define __YAO__LAB__RE__STT__STATE_TYPE__IPP__

#include "yao/lab/re/stt/StateType.hpp"

#include "yao/def/claim.hpp"

namespace yao::lab::prt {

template <typename T, bool ns, bool tp>
  requires std::same_as<T, re::stt::StateType>
void osprint_type(std::ostream &os) {
  if constexpr (ns)
    os << "yao::lab::re::stt::";
  os << "StateType";
}

template <bool ns, bool tp, typename T>
  requires std::same_as<T, re::stt::StateType>
void osprint_value(std::ostream &os, T state_type) {
  osprint_type<T, ns, tp>(os);
  os << ": ";
  switch (state_type) {
    using re::stt::StateType;
  case StateType::EpsilonState:
    os << "EpsilonState";
    break;
  case StateType::SymbolState:
    os << "SymbolState";
    break;
  case StateType::KleeneState:
    os << "KleeneState";
    break;
  case StateType::ConcatState:
    os << "ConcatState";
    break;
  case StateType::UnionState:
    os << "UnionState";
    break;
  default:
    YAO_CLAIM(false);
    break;
  }
}

} // namespace yao::lab::prt

#endif
