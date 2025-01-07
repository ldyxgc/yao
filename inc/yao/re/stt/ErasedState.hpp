#ifndef __YAO__RE__STT__ERASED_STATE__HPP__
#define __YAO__RE__STT__ERASED_STATE__HPP__

#include <memory>
#include <ostream>

#include "yao/re/c_ct_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/VirtualState.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
class ErasedState : private StateBase<ErasedState<_Symbol>> {
public:
  using Symbol = _Symbol;

public:
  template <typename ConcreteState>
  ErasedState(const ConcreteState &concrete_state);

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
  std::unique_ptr<VirtualState<Symbol>> _virtual_state;
};

} // namespace yao::re::stt

#include "yao/re/stt/ErasedState.ipp"

#endif
