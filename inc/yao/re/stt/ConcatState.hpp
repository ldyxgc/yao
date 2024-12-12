#ifndef __YAO__RE__STT__CONCAT_STATE__HPP__
#define __YAO__RE__STT__CONCAT_STATE__HPP__

#include <ostream>
#include <set>

#include "yao/def/warn.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/StateType.hpp"
#include "yao/re/stt/c_r_State_with_same_Symbol.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
class ConcatState : private StateBase<ConcatState<LhsState, RhsState>> {
public:
  using Symbol = typename LhsState::Symbol;

public:
  ConcatState(const LhsState &lhs_state, const RhsState &rhs_state);

  YAO_WARN_PUSH
  YAO_WARN_OFF__ZERO_AS_NULL_POINTER_CONSTANT
  auto operator<=>(const ConcatState &rhs) const = default;
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
  RhsState _raw_rhs_state; // const
  std::set<RhsState> _rhs_state_set;
  bool _is_final;
};

YAO_WARN_POP

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
ConcatState(const LhsState &lhs_state,
            const RhsState &rhs_state) -> ConcatState<LhsState, RhsState>;

} // namespace yao::re::stt

#include "yao/re/stt/ConcatState.ipp"

#endif
