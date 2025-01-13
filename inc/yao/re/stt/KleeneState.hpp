#ifndef __YAO__RE__STT__KLEENE_STATE__HPP__
#define __YAO__RE__STT__KLEENE_STATE__HPP__

#include <functional>
#include <set>

#include "yao/def/warn.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_r_no_cvref_State.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename SubState, typename SubStateCmp = std::less<SubState>>
  requires c_r_no_cvref_State<SubState>
class KleeneState : private StateBase<KleeneState<SubState>> {
public:
  using Symbol = typename SubState::Symbol;

public:
  KleeneState(const SubState &sub_state,
              const SubStateCmp &sub_state_cmp = SubStateCmp{});
  KleeneState(SubState &&sub_state,
              const SubStateCmp &sub_state_cmp = SubStateCmp{});

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const KleeneState &rhs) const = default;

private:
  SubState _raw_sub_state; // const
  std::set<SubState, SubStateCmp> _sub_state_set;
  bool _is_final;
};

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/KleeneState.ipp"

#endif
