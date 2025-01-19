#ifndef __YAO__RE__STT__CONCRETE_VIRTUAL_STATE__HPP__
#define __YAO__RE__STT__CONCRETE_VIRTUAL_STATE__HPP__

#include <compare>
#include <memory>
#include <ostream>

#include "yao/com.hpp"
#include "yao/def/warn.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/VirtualState.hpp"
#include "yao/re/stt/c_r_no_cvref_State.hpp"
#include "yao/re/stt/c_r_no_cvref_different_State_with_same_Symbol.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename ConcreteState>
  requires c_r_no_cvref_State<ConcreteState>
class ConcreteVirtualState
    : public VirtualState<typename ConcreteState::Symbol>,
      private StateBase<ConcreteVirtualState<ConcreteState>> {
public:
  using Symbol = typename ConcreteState::Symbol;
  using CmpOrderInState = typename VirtualState<Symbol>::CmpOrderInState;
  using CmpLessInState = typename VirtualState<Symbol>::CmpLessInState;

public:
  ConcreteVirtualState(auto &&...args);
  static not_null<owner<ConcreteVirtualState *>> make_rptr(auto &&...args);
  static not_null<std::unique_ptr<ConcreteVirtualState>>
  make_uptr(auto &&...args);
  not_null<owner<ConcreteVirtualState *>> copy_rptr() const override;
  not_null<std::unique_ptr<ConcreteVirtualState>> copy_uptr() const;

  void match(const Symbol &symbol) override;
  bool is_final() const override;
  bool is_dead() const override;

  bool operator==(const ConcreteVirtualState &rhs) const;
  auto operator<=>(const ConcreteVirtualState &rhs) const;
  template <typename OtherConcreteState>
    requires c_r_no_cvref_different_State_with_same_Symbol<OtherConcreteState,
                                                           ConcreteState>
  bool operator==(const ConcreteVirtualState<OtherConcreteState> &rhs) const;
  template <typename OtherConcreteState>
    requires c_r_no_cvref_different_State_with_same_Symbol<OtherConcreteState,
                                                           ConcreteState>
  auto operator<=>(const ConcreteVirtualState<OtherConcreteState> &rhs) const;
  bool operator==(const VirtualState<Symbol> &rhs) const override;
  std::strong_ordering
  operator<=>(const VirtualState<Symbol> &rhs) const override;

  static std::strong_ordering
  cmp_order_in_state(const VirtualState<Symbol> &lhs,
                     const VirtualState<Symbol> &rhs);
  CmpOrderInState get_cmp_order_in_state() const override;

  static bool cmp_less_in_state(const VirtualState<Symbol> &lhs,
                                const VirtualState<Symbol> &rhs);
  CmpLessInState get_cmp_less_in_state() const override;

  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  void print_value(std::ostream &os, const prt::PrintValueArgs &args = {},
                   uint indent_level = 0) const override;

private:
  ConcreteState _concrete_state;
};

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/ConcreteVirtualState.ipp"

#endif
