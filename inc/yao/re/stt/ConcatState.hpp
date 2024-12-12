#ifndef __YAO__RE__STT__CONCAT_STATE__HPP__
#define __YAO__RE__STT__CONCAT_STATE__HPP__

#include <concepts>
#include <ostream>
#include <set>

#include "yao/def/warn.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/StateType.hpp"
#include "yao/re/stt/c_o_State.hpp"

namespace yao::re::stt {

namespace impl {

// c: concept, r: require
template <typename LhsState, typename RhsState>
concept c_r_ConcatState =
    c_o_State<LhsState> && c_o_State<RhsState> &&
    std::same_as<typename LhsState::Symbol, typename RhsState::Symbol>;

} // namespace impl

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename LhsState, typename RhsState>
  requires impl::c_r_ConcatState<LhsState, RhsState>
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
  requires impl::c_r_ConcatState<LhsState, RhsState>
ConcatState(const LhsState &lhs_state,
            const RhsState &rhs_state) -> ConcatState<LhsState, RhsState>;

} // namespace yao::re::stt

#include "yao/re/stt/ConcatState.ipp"

#endif
