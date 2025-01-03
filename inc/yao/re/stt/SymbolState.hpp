#ifndef __YAO__RE__STT__SYMBOL_STATE__HPP__
#define __YAO__RE__STT__SYMBOL_STATE__HPP__

#include <concepts>
#include <ostream>
#include <type_traits>

#include "yao/re/c_ct_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

namespace impl {

class YAO_ATTR__EMPTY_BASES SymbolStateBase {
protected:
  SymbolStateBase() = default;

  enum class Label {
    START,
    FINAL,
    DEAD,
  };
  template <typename T, bool ns = false, bool tp = false>
    requires std::same_as<T, SymbolStateBase::Label>
  static void print_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  static void print_value(std::ostream &os, Label label);

  friend auto operator<=>(SymbolStateBase lhs, SymbolStateBase rhs) = default;
};

} // namespace impl

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
class SymbolState : private StateBase<SymbolState<_Symbol>>,
                    private impl::SymbolStateBase {
public:
  using Symbol = _Symbol;

public:
  SymbolState(const Symbol &symbol);
  SymbolState(Symbol &&symbol);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const SymbolState &rhs) const = default;

  template <bool ns = false, bool tp = false>
  static void print_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  void print_value(std::ostream &os) const;

private:
  Symbol _symbol; // const
  Label _label;
};

template <typename Symbol, typename _Symbol = std::remove_cvref_t<Symbol>>
  requires c_ct_Symbol<_Symbol>
SymbolState(Symbol &&symbol) -> SymbolState<_Symbol>;

} // namespace yao::re::stt

#include "yao/re/stt/SymbolState.ipp"

#endif
