#ifndef __YAO__RE__STT__SYMBOL_STATE__HPP__
#define __YAO__RE__STT__SYMBOL_STATE__HPP__

#include <concepts>
#include <ostream>
#include <type_traits>

#include "yao/com.hpp"
#include "yao/def/attr.hpp"
#include "yao/def/warn.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/re/c_ct_Symbol.hpp"
#include "yao/re/c_r_no_cvref_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"

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
  template <typename T>
    requires std::same_as<T, SymbolStateBase::Label>
  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  static void print_value(std::ostream &os, Label label,
                          const prt::PrintValueArgs &args = {},
                          uint indent_level = 0);

  friend auto operator<=>(SymbolStateBase lhs, SymbolStateBase rhs) = default;
};

} // namespace impl

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
class SymbolState : private StateBase<SymbolState<_Symbol>>,
                    private impl::SymbolStateBase {
public:
  using Symbol = _Symbol;

public:
  template <typename __Symbol>
    requires c_ct_Symbol<std::remove_cvref_t<__Symbol>>
  SymbolState(__Symbol &&symbol);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const SymbolState &rhs) const = default;

  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  void print_value(std::ostream &os, const prt::PrintValueArgs &args = {},
                   uint indent_level = 0) const;

private:
  Symbol _symbol; // const
  Label _label;
};

YAO_WARN_POP

template <typename Symbol, typename _Symbol = std::remove_cvref_t<Symbol>>
  requires c_ct_Symbol<_Symbol>
SymbolState(Symbol &&symbol) -> SymbolState<_Symbol>;

} // namespace yao::re::stt

#include "yao/re/stt/SymbolState.ipp"

#endif
