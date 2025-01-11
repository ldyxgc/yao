#ifndef __YAO__RE__STT__CONCRETE_VIRTUAL_STATE__HPP__
#define __YAO__RE__STT__CONCRETE_VIRTUAL_STATE__HPP__

#include <compare>
#include <memory>

#include "yao/com.hpp"
#include "yao/def/warn.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/VirtualState.hpp"
#include "yao/re/stt/c_ct_State.hpp"
#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

namespace impl {

// c: concept, r: require
template <typename ConcreteState>
concept c_r_ConcreteVirtualState =
    req::c_r_no_cvref<ConcreteState> && c_ct_State<ConcreteState>;

} // namespace impl

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename ConcreteState>
  requires impl::c_r_ConcreteVirtualState<ConcreteState>
class ConcreteVirtualState
    : public VirtualState<typename ConcreteState::Symbol>,
      private StateBase<ConcreteVirtualState<ConcreteState>> {
public:
  using Symbol = typename ConcreteState::Symbol;

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

private:
  ConcreteState _concrete_state;
};

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/ConcreteVirtualState.ipp"

#endif
