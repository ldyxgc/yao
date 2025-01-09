#ifndef __YAO__RE__STT__IMPL__FPTR__ERASED_STATE__HPP__
#define __YAO__RE__STT__IMPL__FPTR__ERASED_STATE__HPP__

#include <compare>
#include <ostream>
#include <type_traits>
#include <typeindex>

#include "yao/com.hpp"
#include "yao/re/c_ct_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt::impl::fptr {

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
class ErasedState : private StateBase<ErasedState<_Symbol>> {
public:
  using Symbol = _Symbol;

public:
  template <typename ConcreteState,
            typename _ConcreteState = std::remove_cvref_t<ConcreteState>,
            std::enable_if_t<c_r_different_State_with_same_Symbol<
                                 _ConcreteState, ErasedState<_Symbol>>,
                             int> = 0>
  ErasedState(ConcreteState &&concrete_state);

  ErasedState(const ErasedState &erased_state);
  ErasedState(ErasedState &&erased_state);
  ErasedState &operator=(const ErasedState &erased_state);
  ErasedState &operator=(ErasedState &&erased_state);

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

  template <typename ConcreteState>
  static not_null<owner<void *>>
  _sfun__copy_rptr(not_null<void *> abstract_state);
  not_null<owner<void *>> (*_fptr__copy_rptr)(not_null<void *>);

  template <typename ConcreteState>
  static void _sfun__match(not_null<void *> abstract_state,
                           const Symbol &symbol);
  void (*_fptr__match)(not_null<void *>, const Symbol &);

  template <typename ConcreteState>
  static bool _sfun__is_final(not_null<void *> abstract_state);
  bool (*_fptr__is_final)(not_null<void *>);

  template <typename ConcreteState>
  static bool _sfun__is_dead(not_null<void *> abstract_state);
  bool (*_fptr__is_dead)(not_null<void *>);

  template <typename ConcreteState>
  static bool _sfun__equal(not_null<void *> abstract_state,
                           not_null<void *> rhs_abstract_state);
  bool (*_fptr__equal)(not_null<void *>, not_null<void *>);

  template <typename ConcreteState>
  static std::strong_ordering _sfun__order(not_null<void *> abstract_state,
                                           not_null<void *> rhs_abstract_state);
  std::strong_ordering (*_fptr__order)(not_null<void *>, not_null<void *>);

  template <typename ConcreteState, bool ns, bool tp>
  static void _sfun__print_value(not_null<void *> abstract_state,
                                 std::ostream &os);
  void (*_fptr__print_value__false_false)(not_null<void *>, std::ostream &);
  void (*_fptr__print_value__true_false)(not_null<void *>, std::ostream &);
  void (*_fptr__print_value__false_true)(not_null<void *>, std::ostream &);
  void (*_fptr__print_value__true_true)(not_null<void *>, std::ostream &);

  template <typename ConcreteState>
  static void _sfun__delete(not_null<void *> abstract_state);
  void (*_fptr__delete)(not_null<void *>);
};

} // namespace yao::re::stt::impl::fptr

#include "yao/re/stt/impl/fptr/ErasedState.ipp"

#endif
