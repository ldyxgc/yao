#ifndef __YAO__RE__STT__UNION_STATE__HPP__
#define __YAO__RE__STT__UNION_STATE__HPP__

#include <concepts>
#include <ostream>

#include "yao/def/warn.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_o_State.hpp"

namespace yao::re::stt {

namespace impl {

// c: concept, r: require
template <typename LhsState, typename RhsState>
concept c_r_UnionState =
    c_o_State<LhsState> && c_o_State<RhsState> &&
    std::same_as<typename LhsState::Symbol, typename RhsState::Symbol>;

} // namespace impl

template <typename LhsState, typename RhsState>
  requires impl::c_r_UnionState<LhsState, RhsState>
class UnionState : private StateBase<UnionState<LhsState, RhsState>> {
public:
  using Symbol = typename LhsState::Symbol;

public:
  UnionState(const LhsState &lhs_state, const RhsState &rhs_state);

  YAO_WARN_PUSH
  YAO_WARN_OFF__ZERO_AS_NULL_POINTER_CONSTANT
  auto operator<=>(const UnionState &rhs) const = default;
  YAO_WARN_POP

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
  requires impl::c_r_UnionState<LhsState, RhsState>
UnionState(const LhsState &lhs_state,
           const RhsState &rhs_state) -> UnionState<LhsState, RhsState>;

} // namespace yao::re::stt

#include "yao/re/stt/UnionState.ipp"

#endif
