#ifndef __YAO__RE__STT__CONCAT_STATE__HPP__
#define __YAO__RE__STT__CONCAT_STATE__HPP__

#include <set>
#include <type_traits>

#include "yao/def/warn.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_r_State_with_same_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

namespace impl {

// c: concept, r: require
template <typename LhsState, typename RhsState>
concept c_r_ConcatState =
    req::c_r_no_cvref<LhsState> && req::c_r_no_cvref<RhsState> &&
    c_r_State_with_same_Symbol<LhsState, RhsState>;

} // namespace impl

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename LhsState, typename RhsState,
          typename RhsStateCmp = std::less<RhsState>>
  requires impl::c_r_ConcatState<LhsState, RhsState>
class ConcatState : private StateBase<ConcatState<LhsState, RhsState>> {
public:
  using Symbol = typename LhsState::Symbol;

public:
  template <typename _LhsState, typename _RhsState>
    requires c_r_State_with_same_Symbol<std::remove_cvref_t<_LhsState>,
                                        std::remove_cvref_t<_RhsState>>
  ConcatState(_LhsState &&lhs_state, _RhsState &&rhs_state,
              const RhsStateCmp &rhs_state_cmp = RhsStateCmp{});

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const ConcatState &rhs) const = default;

private:
  LhsState _lhs_state;
  RhsState _raw_rhs_state; // const
  std::set<RhsState, RhsStateCmp> _rhs_state_set;
  bool _is_final;
};

YAO_WARN_POP

template <typename LhsState, typename RhsState,
          typename _LhsState = std::remove_cvref_t<LhsState>,
          typename _RhsState = std::remove_cvref_t<RhsState>>
  requires c_r_State_with_same_Symbol<_LhsState, _RhsState>
ConcatState(LhsState &&lhs_state, RhsState &&rhs_state)
    -> ConcatState<_LhsState, _RhsState>;

} // namespace yao::re::stt

#include "yao/re/stt/ConcatState.ipp"

#endif
