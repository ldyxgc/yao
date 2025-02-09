#ifndef __YAO__RE__STT__SYMBOL_STATE__HPP__
#define __YAO__RE__STT__SYMBOL_STATE__HPP__

#include "yao/def/warn.hpp"
#include "yao/re/c_r_no_cvref_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
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

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/SymbolState.ipp"

#endif
