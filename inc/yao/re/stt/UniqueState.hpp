#ifndef __YAO__RE__STT__UNIQUE_STATE__HPP__
#define __YAO__RE__STT__UNIQUE_STATE__HPP__

#include <memory>
#include <ostream>

#include "yao/com.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/re/c_r_no_cvref_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/VirtualState.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
class UniqueState : private StateBase<UniqueState<_Symbol>> {
public:
  using Symbol = _Symbol;
  struct CmpLessInState {
    typename VirtualState<Symbol>::CmpLessInState cmp_less_in_state;
    bool operator()(const UniqueState &lhs, const UniqueState &rhs) const {
      return cmp_less_in_state(*lhs._virtual_state, *rhs._virtual_state);
    }
  };

public:
  UniqueState(std::unique_ptr<VirtualState<Symbol>> &&virtual_state);

  UniqueState(const UniqueState &unique_state);
  UniqueState(UniqueState &&unique_state) = default;
  UniqueState &operator=(const UniqueState &unique_state);
  UniqueState &operator=(UniqueState &&unique_state) = default;

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  bool operator==(const UniqueState &rhs) const;
  auto operator<=>(const UniqueState &rhs) const;

  CmpLessInState get_cmp_less_in_state() const;

  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  void print_value(std::ostream &os, const prt::PrintValueArgs &args = {},
                   uint indent_level = 0) const;

private:
  not_null<std::unique_ptr<VirtualState<Symbol>>> _virtual_state;
};

} // namespace yao::re::stt

#include "yao/re/stt/UniqueState.ipp"

#endif
