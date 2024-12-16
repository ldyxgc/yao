#ifndef __YAO__RE__STT__SYMBOL_STATE__HPP__
#define __YAO__RE__STT__SYMBOL_STATE__HPP__

#include <memory>

#include "yao/def/warn.hpp"
#include "yao/re/stt/State.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename Symbol> class SymbolState : public State<Symbol> {
public:
  [[deprecated]] SymbolState(const Symbol &symbol);
  static std::unique_ptr<SymbolState> make(const Symbol &symbol);

  void match(const Symbol &symbol) override;
  bool is_final() const override;
  bool is_dead() const override;

  SymbolState(const SymbolState &) = delete;
  SymbolState(SymbolState &&) = delete;
  SymbolState &operator=(const SymbolState &) = delete;
  SymbolState &operator=(SymbolState &&) = delete;

private:
  enum class State {
    START,
    FINAL,
    DEAD,
  };

private:
  const Symbol _symbol;
  State _state;
};

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/SymbolState.ipp"

#endif
