#ifndef __YAO__RE__STT__KLEENE_STATE__HPP__
#define __YAO__RE__STT__KLEENE_STATE__HPP__

#include <ostream>
#include <set>

#include "yao/def/warn.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/StateType.hpp"
#include "yao/re/stt/c_o_State.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename SubState>
  requires c_o_State<SubState>
class KleeneState : private StateBase<KleeneState<SubState>> {
public:
  using Symbol = typename SubState::Symbol;

public:
  KleeneState(const SubState &sub_state);

  YAO_WARN_PUSH
  YAO_WARN_OFF__ZERO_AS_NULL_POINTER_CONSTANT
  auto operator<=>(const KleeneState &rhs) const = default;
  YAO_WARN_POP

  StateType type() const;

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  template <bool ns = false, bool tp = false>
  static void osprint_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  void osprint_value(std::ostream &os) const;

private:
  SubState _raw_sub_state; // const
  std::set<SubState> _sub_state_set;
  bool _is_final;
};

YAO_WARN_POP

template <typename SubState>
  requires c_o_State<SubState>
KleeneState(const SubState &sub_state) -> KleeneState<SubState>;

} // namespace yao::re::stt

#include "yao/re/stt/KleeneState.ipp"

#endif
