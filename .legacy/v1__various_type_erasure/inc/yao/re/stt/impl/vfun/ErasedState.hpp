#ifndef __YAO__RE__STT__IMPL__VFUN__ERASED_STATE__HPP__
#define __YAO__RE__STT__IMPL__VFUN__ERASED_STATE__HPP__

#include <memory>
#include <ostream>
#include <type_traits>

#include "yao/com.hpp"
#include "yao/re/c_ct_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/VirtualState.hpp"
#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt::impl::vfun {

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
class ErasedState : private StateBase<ErasedState<_Symbol>> {
public:
  using Symbol = _Symbol;

public:
  template <typename ConcreteState,
            std::enable_if_t<
                c_r_different_State_with_same_Symbol<
                    std::remove_cvref_t<ConcreteState>, ErasedState<_Symbol>>,
                int> = 0>
  ErasedState(ConcreteState &&concrete_state);

  ErasedState(const ErasedState &erased_state);
  ErasedState(ErasedState &&erased_state) = default;
  ErasedState &operator=(const ErasedState &erased_state);
  ErasedState &operator=(ErasedState &&erased_state) = default;

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  bool operator==(const ErasedState &rhs) const;
  auto operator<=>(const ErasedState &rhs) const;

  template <bool ns = false, bool tp = false>
  static void print_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  void print_value(std::ostream &os) const;

private:
  not_null<std::unique_ptr<VirtualState<Symbol>>> _virtual_state;
};

} // namespace yao::re::stt::impl::vfun

#include "yao/re/stt/impl/vfun/ErasedState.ipp"

#endif
