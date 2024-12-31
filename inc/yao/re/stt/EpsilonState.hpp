#ifndef __YAO__RE__STT__EPSILON_STATE__HPP__
#define __YAO__RE__STT__EPSILON_STATE__HPP__

#include "yao/re/c_ct_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
class EpsilonState : private StateBase<EpsilonState<_Symbol>> {
public:
  using Symbol = _Symbol;

public:
  EpsilonState();

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

private:
  enum class Label { FINAL, DEAD };

private:
  Label _label;
};

} // namespace yao::re::stt

#include "yao/re/stt/EpsilonState.ipp"

#endif
