#ifndef __YAO__RE__STT__ERASED_STATE__HPP__
#define __YAO__RE__STT__ERASED_STATE__HPP__

#include <memory>
#include <type_traits>

#include "yao/com.hpp"
#include "yao/re/c_r_no_cvref_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/VirtualState.hpp"
#include "yao/re/stt/c_ct_State.hpp"
#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
class ErasedState : private StateBase<ErasedState<_Symbol>> {
public:
  using Symbol = _Symbol;

  struct CmpLess1 {
    typename VirtualState<Symbol>::CmpLess1 sub_cmp_less;
    bool operator()(const ErasedState &lhs, const ErasedState &rhs) const {
      return sub_cmp_less(*lhs._virtual_state, *rhs._virtual_state);
    }
  };

  using CmpLess2 = bool (*)(const ErasedState &, const ErasedState &);

public:
  template <typename ConcreteState,
            std::enable_if_t<
                c_r_different_State_with_same_Symbol<
                    std::remove_cvref_t<ConcreteState>, ErasedState<_Symbol>>,
                int> = 0>
  ErasedState(ConcreteState &&concrete_state);
  template <typename ConcreteState>
    requires c_ct_State<std::remove_cvref_t<ConcreteState>>
  ErasedState(ConcreteState &&concrete_state, int sub_state);

  ErasedState(const ErasedState &erased_state);
  ErasedState(ErasedState &&erased_state) = default;
  ErasedState &operator=(const ErasedState &erased_state);
  ErasedState &operator=(ErasedState &&erased_state) = default;

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  bool operator==(const ErasedState &rhs) const;
  auto operator<=>(const ErasedState &rhs) const;

  CmpLess1 get_cmp_less1_assume_same_known_type() const;

  VirtualState<Symbol> *get() const;
  CmpLess2 get_cmp_less2_assume_same_known_type() const;

private:
  not_null<std::unique_ptr<VirtualState<Symbol>>> _virtual_state;
};

} // namespace yao::re::stt

#include "yao/re/stt/ErasedState.ipp"

#endif
