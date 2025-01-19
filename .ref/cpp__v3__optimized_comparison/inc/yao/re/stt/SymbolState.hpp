#ifndef __YAO__RE__STT__SYMBOL_STATE__HPP__
#define __YAO__RE__STT__SYMBOL_STATE__HPP__

#include <compare>
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
  using CmpOrderInState = std::strong_ordering (*)(const SymbolState &,
                                                   const SymbolState &);
  using CmpLessInState = bool (*)(const SymbolState &, const SymbolState &);

public:
  SymbolState(const Symbol &symbol);
  SymbolState(Symbol &&symbol);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const SymbolState &rhs) const = default;

  static std::strong_ordering cmp_order_in_state(const SymbolState &lhs,
                                                 const SymbolState &rhs);
  CmpOrderInState get_cmp_order_in_state() const;

  static bool cmp_less_in_state(const SymbolState &lhs, const SymbolState &rhs);
  CmpLessInState get_cmp_less_in_state() const;

  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  void print_value(std::ostream &os, const prt::PrintValueArgs &args = {},
                   uint indent_level = 0) const;

private:
  Symbol _symbol; // const
  Label _label;
};

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/SymbolState.ipp"

#endif
