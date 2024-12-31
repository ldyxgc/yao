#ifndef __YAO__RE__STT__SYMBOL_STATE__HPP__
#define __YAO__RE__STT__SYMBOL_STATE__HPP__

namespace yao::re::stt {

template <typename Symbol> class SymbolState {
public:
  SymbolState(const Symbol &symbol);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

private:
  enum class Label { START, FINAL, DEAD };

private:
  const Symbol _symbol;
  Label _label;
};

} // namespace yao::re::stt

#include "yao/re/stt/SymbolState.ipp"

#endif
