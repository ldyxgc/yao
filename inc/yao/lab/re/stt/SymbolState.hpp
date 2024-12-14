#ifndef __YAO__LAB__RE__STT__SYMBOL_STATE__HPP__
#define __YAO__LAB__RE__STT__SYMBOL_STATE__HPP__

#include <concepts>
#include <ostream>

#include "yao/def/attr.hpp"
#include "yao/def/warn.hpp"
#include "yao/lab/re/c_t_Symbol.hpp"
#include "yao/lab/re/stt/StateBase.hpp"
#include "yao/lab/re/stt/StateType.hpp"

namespace yao::lab::re::stt {

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

public:
  auto operator<=>(const SymbolStateBase &rhs) const = default;
};

} // namespace impl

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
class SymbolState : private StateBase<SymbolState<_Symbol>>,
                    private impl::SymbolStateBase {
public:
  using Symbol = _Symbol;

public:
  SymbolState(const Symbol &symbol);

  YAO_WARN_PUSH
  YAO_WARN_OFF__ZERO_AS_NULL_POINTER_CONSTANT
  auto operator<=>(const SymbolState &rhs) const = default;
  YAO_WARN_POP

  StateType type() const;

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

YAO_WARN_POP

template <typename Symbol>
  requires c_t_Symbol<Symbol>
SymbolState(const Symbol &symbol) -> SymbolState<Symbol>;

} // namespace yao::lab::re::stt

#include "yao/lab/re/stt/SymbolState.ipp"

#endif
