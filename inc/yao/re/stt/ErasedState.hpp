#ifndef __YAO__RE__STT__ERASED_STATE__HPP__
#define __YAO__RE__STT__ERASED_STATE__HPP__

#include <concepts>
#include <memory>
#include <ostream>
#include <type_traits>

#include "yao/re/c_t_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/StateType.hpp"
#include "yao/re/stt/VirtualStateBase.hpp"
#include "yao/re/stt/c_o_State.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
class ErasedState : private StateBase<ErasedState<_Symbol>> {
public:
  using Symbol = _Symbol;

public:
  ErasedState(const ErasedState &erased_state);
  template <typename ConcreteState,
            std::enable_if_t<
                c_o_State<ConcreteState> &&
                    std::same_as<typename ConcreteState::Symbol, _Symbol> &&
                    (!std::same_as<ConcreteState, ErasedState<_Symbol>>),
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

} // namespace yao::re::stt

#include "yao/re/stt/ErasedState.ipp"

#endif
