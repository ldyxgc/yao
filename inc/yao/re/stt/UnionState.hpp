#ifndef __YAO__RE__STT__UNION_STATE__HPP__
#define __YAO__RE__STT__UNION_STATE__HPP__

#include <type_traits>

#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_r_State_with_same_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

namespace impl {

// c: concept, r: require
template <typename LhsState, typename RhsState>
concept c_r_UnionState =
    req::c_r_no_cvref<LhsState> && req::c_r_no_cvref<RhsState> &&
    c_r_State_with_same_Symbol<LhsState, RhsState>;

} // namespace impl

template <typename LhsState, typename RhsState>
  requires impl::c_r_UnionState<LhsState, RhsState>
class UnionState : private StateBase<UnionState<LhsState, RhsState>> {
public:
  using Symbol = typename LhsState::Symbol;

public:
  template <typename _LhsState, typename _RhsState>
    requires c_r_State_with_same_Symbol<std::remove_cvref_t<_LhsState>,
                                        std::remove_cvref_t<_RhsState>>
  UnionState(_LhsState &&lhs_state, _RhsState &&rhs_state);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const UnionState &rhs) const = default;

private:
  LhsState _lhs_state;
  RhsState _rhs_state;
};

template <typename LhsState, typename RhsState,
          typename _LhsState = std::remove_cvref_t<LhsState>,
          typename _RhsState = std::remove_cvref_t<RhsState>>
  requires c_r_State_with_same_Symbol<_LhsState, _RhsState>
UnionState(LhsState &&lhs_state, RhsState &&rhs_state)
    -> UnionState<_LhsState, _RhsState>;

} // namespace yao::re::stt

#include "yao/re/stt/UnionState.ipp"

#endif
