#ifndef __YAO__RE__STT__SYMBOL_STATE__IPP__
#define __YAO__RE__STT__SYMBOL_STATE__IPP__

#include "yao/re/stt/SymbolState.hpp"

#include "yao/def/claim.hpp"

namespace yao::re::stt {

template <typename Symbol>
SymbolState<Symbol>::SymbolState(const Symbol &symbol)
    : _symbol{symbol}, _label{Label::START} {}

template <typename Symbol>
void SymbolState<Symbol>::match(const Symbol &symbol) {
  switch (_label) {
  case Label::START:
    _label = _symbol == symbol ? Label::FINAL : Label::DEAD;
    break;
  case Label::FINAL:
    _label = Label::DEAD;
    break;
  case Label::DEAD:
    break;
  default:
    YAO_CLAIM(false);
    break;
  }
}

template <typename Symbol> bool SymbolState<Symbol>::is_final() const {
  return _label == Label::FINAL;
}

template <typename Symbol> bool SymbolState<Symbol>::is_dead() const {
  return _label == Label::DEAD;
}

} // namespace yao::re::stt

#endif
