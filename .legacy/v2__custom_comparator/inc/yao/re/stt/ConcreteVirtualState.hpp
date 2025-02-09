#ifndef __YAO__RE__STT__CONCRETE_VIRTUAL_STATE__HPP__
#define __YAO__RE__STT__CONCRETE_VIRTUAL_STATE__HPP__

#include <compare>
#include <memory>

#include "yao/com.hpp"
#include "yao/def/warn.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/VirtualState.hpp"
#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"
#include "yao/re/stt/c_r_no_cvref_State.hpp"
#include "yao/req/c_r_no_cvref.hpp"

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
  using CmpLess1 =
      typename VirtualState<typename ConcreteState::Symbol>::CmpLess1;
  using CmpLess2 =
      typename VirtualState<typename ConcreteState::Symbol>::CmpLess2;

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
    requires req::c_r_no_cvref<OtherConcreteState> &&
             c_r_different_State_with_same_Symbol<OtherConcreteState,
                                                  ConcreteState>
  bool operator==(const ConcreteVirtualState<OtherConcreteState> &rhs) const;
  template <typename OtherConcreteState>
    requires req::c_r_no_cvref<OtherConcreteState> &&
             c_r_different_State_with_same_Symbol<OtherConcreteState,
                                                  ConcreteState>
  auto operator<=>(const ConcreteVirtualState<OtherConcreteState> &rhs) const;
  bool operator==(const VirtualState<Symbol> &rhs) const override;
  std::strong_ordering
  operator<=>(const VirtualState<Symbol> &rhs) const override;

  static bool cmp_less1_assume_same_known_type(const VirtualState<Symbol> &lhs,
                                               const VirtualState<Symbol> &rhs);
  CmpLess1 get_cmp_less1_assume_same_known_type() const override;

  static bool cmp_less2_assume_same_known_type(const ErasedState<Symbol> &lhs,
                                               const ErasedState<Symbol> &rhs);
  CmpLess2 get_cmp_less2_assume_same_known_type() const override;

private:
  ConcreteState _concrete_state;
};

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/ConcreteVirtualState.ipp"

#endif
