#ifndef __YAO__RE__STT__VIRTUAL_STATE__HPP__
#define __YAO__RE__STT__VIRTUAL_STATE__HPP__

#include <compare>
#include <memory>
#include <ostream>

#include "yao/def/warn.hpp"
#include "yao/help.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/StateType.hpp"
#include "yao/re/stt/VirtualStateBase.hpp"
#include "yao/re/stt/c_o_State.hpp"
#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename ConcreteState>
  requires c_o_State<ConcreteState>
class VirtualState : public VirtualStateBase<typename ConcreteState::Symbol>,
                     private StateBase<VirtualState<ConcreteState>> {
public:
  using Symbol = typename ConcreteState::Symbol;

public:
  VirtualState(const auto &...args);
  static not_null<owner<VirtualState *>> make_rptr(const auto &...args);
  static not_null<std::unique_ptr<VirtualState>> make_uptr(const auto &...args);
  not_null<owner<VirtualState *>> copy_rptr() const override;
  not_null<std::unique_ptr<VirtualState>> copy_uptr() const;

  bool operator==(const VirtualState &rhs) const;
  auto operator<=>(const VirtualState &rhs) const;
  template <typename OtherConcreteState>
    requires c_r_different_State_with_same_Symbol<OtherConcreteState,
                                                  ConcreteState>
  bool operator==(const VirtualState<OtherConcreteState> &rhs) const;
  template <typename OtherConcreteState>
    requires c_r_different_State_with_same_Symbol<OtherConcreteState,
                                                  ConcreteState>
  auto operator<=>(const VirtualState<OtherConcreteState> &rhs) const;
  bool operator==(const VirtualStateBase<Symbol> &rhs) const override;
  std::strong_ordering
  operator<=>(const VirtualStateBase<Symbol> &rhs) const override;

  StateType type() const override;

  void match(const Symbol &symbol) override;
  bool is_final() const override;
  bool is_dead() const override;

  template <bool ns = false, bool tp = false>
  static void osprint_type(std::ostream &os);
  void osprint_value(std::ostream &os, bool ns = false,
                     bool tp = false) const override;

private:
  ConcreteState _concrete_state;
};

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/VirtualState.ipp"

#endif
