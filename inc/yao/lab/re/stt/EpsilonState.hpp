#ifndef __YAO__LAB__RE__STT__EPSILON_STATE__HPP__
#define __YAO__LAB__RE__STT__EPSILON_STATE__HPP__

#include <concepts>
#include <ostream>

#include "yao/def/attr.hpp"
#include "yao/def/warn.hpp"
#include "yao/lab/re/c_t_Symbol.hpp"
#include "yao/lab/re/stt/StateBase.hpp"
#include "yao/lab/re/stt/StateType.hpp"

namespace yao::lab::re::stt {

namespace impl {

class YAO_ATTR__EMPTY_BASES EpsilonStateBase {
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

public:
  auto operator<=>(const EpsilonStateBase &rhs) const = default;
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

  YAO_WARN_PUSH
  YAO_WARN_OFF__ZERO_AS_NULL_POINTER_CONSTANT
  auto operator<=>(const EpsilonState &rhs) const = default;
  YAO_WARN_POP

  StateType type() const;

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

} // namespace yao::lab::re::stt

#include "yao/lab/re/stt/EpsilonState.ipp"

#endif
