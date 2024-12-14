#ifndef __YAO__LAB__RE__STT__UNION_STATE__HPP__
#define __YAO__LAB__RE__STT__UNION_STATE__HPP__

#include <ostream>

#include "yao/def/warn.hpp"
#include "yao/lab/re/stt/StateBase.hpp"
#include "yao/lab/re/stt/StateType.hpp"
#include "yao/lab/re/stt/c_r_State_with_same_Symbol.hpp"

namespace yao::lab::re::stt {

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
class UnionState : private StateBase<UnionState<LhsState, RhsState>> {
public:
  using Symbol = typename LhsState::Symbol;

public:
  UnionState(const LhsState &lhs_state, const RhsState &rhs_state);

  YAO_WARN_PUSH
  YAO_WARN_OFF__ZERO_AS_NULL_POINTER_CONSTANT
  auto operator<=>(const UnionState &rhs) const = default;
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
  LhsState _lhs_state;
  RhsState _rhs_state;
};

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
UnionState(const LhsState &lhs_state,
           const RhsState &rhs_state) -> UnionState<LhsState, RhsState>;

} // namespace yao::lab::re::stt

#include "yao/lab/re/stt/UnionState.ipp"

#endif
