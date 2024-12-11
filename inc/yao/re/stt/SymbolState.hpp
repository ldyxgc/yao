#ifndef __YAO__RE__STT__SYMBOL_STATE__HPP__
#define __YAO__RE__STT__SYMBOL_STATE__HPP__

#include <concepts>
#include <ostream>

#include "yao/def/attr.hpp"
#include "yao/re/c_t_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"

namespace yao::re::stt {

namespace impl {

class YAO_ATTR__EMPTY_BASES SymbolStateBase {
protected:
  SymbolStateBase() = default;

  enum class State {
    START,
    FINAL,
    DEAD,
  };
  template <typename T, bool ns = false, bool tp = false>
    requires std::same_as<T, SymbolStateBase::State>
  static void osprint_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  static void osprint_value(std::ostream &os, State state);
};

} // namespace impl

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
class SymbolState : private StateBase<SymbolState<_Symbol>>,
                    private impl::SymbolStateBase {
public:
  using Symbol = _Symbol;

public:
  SymbolState(const Symbol &symbol);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  template <bool ns = false, bool tp = false>
  static void osprint_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  void osprint_value(std::ostream &os) const;

private:
  Symbol _symbol; // const
  State _state;
};

template <typename Symbol>
  requires c_t_Symbol<Symbol>
SymbolState(const Symbol &symbol) -> SymbolState<Symbol>;

} // namespace yao::re::stt

#include "yao/re/stt/SymbolState.ipp"

#endif
