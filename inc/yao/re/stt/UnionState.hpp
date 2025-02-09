#ifndef __YAO__RE__STT__UNION_STATE__HPP__
#define __YAO__RE__STT__UNION_STATE__HPP__

#include <ostream>
#include <type_traits>

#include "yao/com.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_r_no_cvref_State_with_same_Symbol.hpp"
#include "yao/re/stt/c_r_rm_cvref_State_with_same_Symbol.hpp"

namespace yao::re::stt {

template <typename LhsState, typename RhsState>
  requires c_r_no_cvref_State_with_same_Symbol<LhsState, RhsState>
class UnionState : private StateBase<UnionState<LhsState, RhsState>> {
public:
  using Symbol = typename LhsState::Symbol;

public:
  template <typename _LhsState, typename _RhsState>
    requires c_r_rm_cvref_State_with_same_Symbol<_LhsState, _RhsState>
  UnionState(_LhsState &&lhs_state, _RhsState &&rhs_state);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const UnionState &rhs) const = default;

  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  void print_value(std::ostream &os, const prt::PrintValueArgs &args = {},
                   uint indent_level = 0) const;

private:
  LhsState _lhs_state;
  RhsState _rhs_state;
};

template <typename LhsState, typename RhsState>
  requires c_r_rm_cvref_State_with_same_Symbol<LhsState, RhsState>
UnionState(LhsState &&lhs_state, RhsState &&rhs_state)
    -> UnionState<std::remove_cvref_t<LhsState>, std::remove_cvref_t<RhsState>>;

} // namespace yao::re::stt

#include "yao/re/stt/UnionState.ipp"

#endif
