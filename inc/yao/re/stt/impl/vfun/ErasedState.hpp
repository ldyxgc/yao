#ifndef __YAO__RE__STT__IMPL__VFUN__ERASED_STATE__HPP__
#define __YAO__RE__STT__IMPL__VFUN__ERASED_STATE__HPP__

#include <memory>
#include <ostream>
#include <type_traits>

#include "yao/re/c_t_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/StateType.hpp"
#include "yao/re/stt/VirtualStateBase.hpp"
#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"

namespace yao::re::stt::impl::vfun {

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

private:
  std::unique_ptr<VirtualStateBase<Symbol>> _virtual_state;
};

} // namespace yao::re::stt::impl::vfun

#include "yao/re/stt/impl/vfun/ErasedState.ipp"

#endif
