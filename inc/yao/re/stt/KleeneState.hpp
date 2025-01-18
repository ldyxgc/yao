#ifndef __YAO__RE__STT__KLEENE_STATE__HPP__
#define __YAO__RE__STT__KLEENE_STATE__HPP__

#include <ostream>
#include <set>

#include "yao/com.hpp"
#include "yao/def/warn.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_r_no_cvref_State.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename SubState>
  requires c_r_no_cvref_State<SubState>
class KleeneState : private StateBase<KleeneState<SubState>> {
public:
  using Symbol = typename SubState::Symbol;
  using CmpLessInState = bool (*)(const KleeneState &, const KleeneState &);

public:
  KleeneState(const SubState &sub_state);
  KleeneState(SubState &&sub_state);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const KleeneState &rhs) const = default;

  static bool cmp_less_in_state(const KleeneState &lhs, const KleeneState &rhs);
  CmpLessInState get_cmp_less_in_state() const;

  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  void print_value(std::ostream &os, const prt::PrintValueArgs &args = {},
                   uint indent_level = 0) const;

private:
  SubState _raw_sub_state; // const
  std::set<SubState> _sub_state_set;
  bool _is_final;
};

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/KleeneState.ipp"

#endif
