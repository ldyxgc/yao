#ifndef __YAO__RE__STT__UNION_STATE__HPP__
#define __YAO__RE__STT__UNION_STATE__HPP__

#include <ostream>

#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_r_State_with_same_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

template <typename LhsState, typename RhsState>
  requires req::c_r_no_cvref<LhsState> && req::c_r_no_cvref<RhsState> &&
           c_r_State_with_same_Symbol<LhsState, RhsState>
class UnionState : private StateBase<UnionState<LhsState, RhsState>> {
public:
  using Symbol = typename LhsState::Symbol;

public:
  UnionState(const LhsState &lhs_state, const RhsState &rhs_state);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const UnionState &rhs) const = default;

  template <bool ns = false, bool tp = false>
  static void print_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  void print_value(std::ostream &os) const;

private:
  LhsState _lhs_state;
  RhsState _rhs_state;
};

template <typename LhsState, typename RhsState>
  requires c_r_State_with_same_Symbol<LhsState, RhsState>
UnionState(const LhsState &lhs_state, const RhsState &rhs_state)
    -> UnionState<LhsState, RhsState>;

} // namespace yao::re::stt

#include "yao/re/stt/UnionState.ipp"

#endif
