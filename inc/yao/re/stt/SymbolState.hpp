#ifndef __YAO__RE__STT__SYMBOL_STATE__HPP__
#define __YAO__RE__STT__SYMBOL_STATE__HPP__

#include "yao/re/c_ct_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
class SymbolState : private StateBase<SymbolState<_Symbol>> {
public:
  using Symbol = _Symbol;

public:
  SymbolState(const Symbol &symbol);
  SymbolState(Symbol &&symbol);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const SymbolState &rhs) const = default;

private:
  enum class Label { START, FINAL, DEAD };

private:
  Symbol _symbol; // const
  Label _label;
};

} // namespace yao::re::stt

#include "yao/re/stt/SymbolState.ipp"

#endif
