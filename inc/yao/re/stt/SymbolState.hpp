#ifndef __YAO__RE__STT__SYMBOL_STATE__HPP__
#define __YAO__RE__STT__SYMBOL_STATE__HPP__

#include "yao/re/c_ct_Symbol.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

template <typename Symbol>
  requires req::c_r_no_cvref<Symbol> && c_ct_Symbol<Symbol>
class SymbolState {
public:
  SymbolState(const Symbol &symbol);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

private:
  enum class Label { START, FINAL, DEAD };

private:
  Symbol _symbol; // const
  Label _label;
};

template <typename Symbol>
SymbolState(const Symbol &symbol) -> SymbolState<Symbol>;

} // namespace yao::re::stt

#include "yao/re/stt/SymbolState.ipp"

#endif
