#ifndef __YAO__RE__STT__IMPL__VTAB__ERASED_STATE__HPP__
#define __YAO__RE__STT__IMPL__VTAB__ERASED_STATE__HPP__

#include <compare>
#include <functional>
#include <ostream>
#include <type_traits>

#include "yao/help.hpp"
#include "yao/re/c_t_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/StateType.hpp"
#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"

namespace yao::re::stt::impl::vtab {

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
class ErasedState : private StateBase<ErasedState<_Symbol>> {
public:
  using Symbol = _Symbol;

public:
  ErasedState(const ErasedState &erased_state);
  template <typename ConcreteState,
            std::enable_if_t<c_r_different_State_with_same_Symbol<
                                 ConcreteState, ErasedState<_Symbol>>,
                             int> = 0>
  ErasedState(const ConcreteState &concrete_state);

  ErasedState &operator=(const ErasedState &rhs);

  bool operator==(const ErasedState &rhs) const;
  auto operator<=>(const ErasedState &rhs) const;

  StateType type() const;

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  template <bool ns = false, bool tp = false>
  static void osprint_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  void osprint_value(std::ostream &os) const;

  ~ErasedState();

private:
  not_null<owner<void *>> _abstract_state;
  std::function<not_null<owner<void *>>(not_null<void *> abstract_state)>
      _func__copy_rptr;
  std::function<bool(not_null<void *> abstract_state,
                     not_null<void *> rhs_abstract_state)>
      _func__equal;
  std::function<std::strong_ordering(not_null<void *> abstract_state,
                                     not_null<void *> rhs_abstract_state)>
      _func__order;
  std::function<StateType(not_null<void *> abstract_state)> _func__type;
  std::function<void(not_null<void *> abstract_state, const Symbol &)>
      _func__match;
  std::function<bool(not_null<void *> abstract_state)> _func__is_final;
  std::function<bool(not_null<void *> abstract_state)> _func__is_dead;
  std::function<void(not_null<void *> abstract_state, std::ostream &os)>
      _func__osprint_value__false_false;
  std::function<void(not_null<void *> abstract_state, std::ostream &os)>
      _func__osprint_value__true_false;
  std::function<void(not_null<void *> abstract_state, std::ostream &os)>
      _func__osprint_value__false_true;
  std::function<void(not_null<void *> abstract_state, std::ostream &os)>
      _func__osprint_value__true_true;
  std::function<void(not_null<void *> abstract_state)> _func__delete;
};

} // namespace yao::re::stt::impl::vtab

#include "yao/re/stt/impl/vtab/ErasedState.ipp"

#endif
