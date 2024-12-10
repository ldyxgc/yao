#ifndef __YAO__RE__STT__EPSILON_STATE__HPP__
#define __YAO__RE__STT__EPSILON_STATE__HPP__

#include <concepts>
#include <ostream>

#include "yao/re/c_t_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"

namespace yao::re::stt {

namespace impl {

class EpsilonStateBase {
protected:
  EpsilonStateBase() = default;

  enum class State {
    FINAL,
    DEAD,
  };
  template <typename T, bool ns = false, bool tp = false>
    requires std::same_as<T, EpsilonStateBase::State>
  static void osprint_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  static void osprint_value(std::ostream &os, State state);
};

} // namespace impl

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
class EpsilonState : private StateBase<EpsilonState<_Symbol>>,
                     private impl::EpsilonStateBase {
public:
  using Symbol = _Symbol;

public:
  EpsilonState();

  void match(const Symbol &symbol);
  bool is_final() const;
  bool is_dead() const;

  template <bool ns = false, bool tp = false>
  static void osprint_type(std::ostream &os);
  template <bool ns = false, bool tp = false>
  void osprint_value(std::ostream &os) const;

private:
  State _state;
};

} // namespace yao::re::stt

#include "yao/re/stt/EpsilonState.ipp"

#endif
