#ifndef __YAO__RE__STT__CONCAT_STATE__HPP__
#define __YAO__RE__STT__CONCAT_STATE__HPP__

#include <compare>
#include <ostream>
#include <set>
#include <type_traits>

#include "yao/com.hpp"
#include "yao/def/warn.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_r_no_cvref_State_with_same_Symbol.hpp"
#include "yao/re/stt/c_r_rm_cvref_State_with_same_Symbol.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
class ConcatState : private StateBase<ConcatState<LhsState, RhsState>> {
public:
  using Symbol = typename LhsState::Symbol;
  using CmpOrderInState = std::strong_ordering (*)(const ConcatState &,
                                                   const ConcatState &);
  using CmpLessInState = bool (*)(const ConcatState &, const ConcatState &);

public:
  template <typename _LhsState, typename _RhsState>
  ConcatState(_LhsState &&lhs_state, _RhsState &&rhs_state);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const ConcatState &rhs) const = default;

  static std::strong_ordering cmp_order_in_state(const ConcatState &lhs,
                                                 const ConcatState &rhs);
  CmpOrderInState get_cmp_order_in_state() const;

  static bool cmp_less_in_state(const ConcatState &lhs, const ConcatState &rhs);
  CmpLessInState get_cmp_less_in_state() const;

  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  void print_value(std::ostream &os, const prt::PrintValueArgs &args = {},
                   uint indent_level = 0) const;

private:
  LhsState _lhs_state;
  RhsState _raw_rhs_state; // const
  std::set<RhsState, typename RhsState::CmpLessInState> _rhs_state_set;
  bool _is_final;
};

YAO_WARN_POP

template <typename LhsState, typename RhsState>
  requires c_r_rm_cvref_State_with_same_Symbol<LhsState, RhsState>
ConcatState(LhsState &&lhs_state, RhsState &&rhs_state)
    -> ConcatState<std::remove_cvref_t<LhsState>,
                   std::remove_cvref_t<RhsState>>;

} // namespace yao::re::stt

#include "yao/re/stt/ConcatState.ipp"

#endif
