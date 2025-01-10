#ifndef __YAO__RE__STT__KLEENE_STATE__HPP__
#define __YAO__RE__STT__KLEENE_STATE__HPP__

#include <set>

#include "yao/def/warn.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/c_ct_State.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename SubState>
  requires req::c_r_no_cvref<SubState> && c_ct_State<SubState>
class KleeneState : private StateBase<KleeneState<SubState>> {
public:
  using Symbol = typename SubState::Symbol;

public:
  KleeneState(const SubState &sub_state);
  KleeneState(SubState &&sub_state);

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  auto operator<=>(const KleeneState &rhs) const = default;

private:
  SubState _raw_sub_state; // const
  std::set<SubState> _sub_state_set;
  bool _is_final;
};

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/KleeneState.ipp"

#endif
