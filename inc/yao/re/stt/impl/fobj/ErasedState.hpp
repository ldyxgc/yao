#ifndef __YAO__RE__STT__IMPL__FOBJ__ERASED_STATE__HPP__
#define __YAO__RE__STT__IMPL__FOBJ__ERASED_STATE__HPP__

#include <compare>
#include <functional>
#include <ostream>
#include <type_traits>
#include <typeindex>

#include "yao/com.hpp"
#include "yao/re/c_ct_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt::impl::fobj {

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
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

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  bool operator==(const ErasedState &rhs) const;
  auto operator<=>(const ErasedState &rhs) const;

  template <bool ns = false, bool tp = false>
  static void print_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  void print_value(std::ostream &os) const;

  ~ErasedState();

private:
  not_null<owner<void *>> _abstract_state;
  std::type_index _type_index;

  std::function<not_null<owner<void *>>(not_null<void *> abstract_state)>
      _fobj__copy_rptr;

  std::function<void(not_null<void *> abstract_state, const Symbol &)>
      _fobj__match;
  std::function<bool(not_null<void *> abstract_state)> _fobj__is_final;
  std::function<bool(not_null<void *> abstract_state)> _fobj__is_dead;

  std::function<bool(not_null<void *> abstract_state,
                     not_null<void *> rhs_abstract_state)>
      _fobj__equal;
  std::function<std::strong_ordering(not_null<void *> abstract_state,
                                     not_null<void *> rhs_abstract_state)>
      _fobj__order;

  std::function<void(not_null<void *> abstract_state, std::ostream &os)>
      _fobj__print_value__false_false;
  std::function<void(not_null<void *> abstract_state, std::ostream &os)>
      _fobj__print_value__true_false;
  std::function<void(not_null<void *> abstract_state, std::ostream &os)>
      _fobj__print_value__false_true;
  std::function<void(not_null<void *> abstract_state, std::ostream &os)>
      _fobj__print_value__true_true;

  std::function<void(not_null<void *> abstract_state)> _fobj__delete;
};

} // namespace yao::re::stt::impl::fobj

#include "yao/re/stt/impl/fobj/ErasedState.ipp"

#endif
