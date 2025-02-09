#ifndef __YAO__RE__STT__EPSILON_STATE__HPP__
#define __YAO__RE__STT__EPSILON_STATE__HPP__

#include <concepts>
#include <ostream>

#include "yao/com.hpp"
#include "yao/def/attr.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/re/c_r_no_cvref_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"

namespace yao::re::stt {

namespace impl {

class YAO_ATTR__EMPTY_BASES EpsilonStateBase {
protected:
  EpsilonStateBase() = default;

  enum class Label {
    FINAL,
    DEAD,
  };
  template <typename T>
    requires std::same_as<T, EpsilonStateBase::Label>
  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  static void print_value(std::ostream &os, Label label,
                          const prt::PrintValueArgs &args = {},
                          uint indent_level = 0);

  friend auto operator<=>(EpsilonStateBase lhs, EpsilonStateBase rhs) = default;
};

} // namespace impl

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
class EpsilonState : private StateBase<EpsilonState<_Symbol>>,
                     private impl::EpsilonStateBase {
public:
  using Symbol = _Symbol;

public:
  EpsilonState();

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  friend auto operator<=>(EpsilonState lhs, EpsilonState rhs) = default;

  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  void print_value(std::ostream &os, const prt::PrintValueArgs &args = {},
                   uint indent_level = 0) const;

private:
  Label _label;
};

} // namespace yao::re::stt

#include "yao/re/stt/EpsilonState.ipp"

#endif
