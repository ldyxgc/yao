#ifndef __YAO__RE__STT__EPSILON_STATE__HPP__
#define __YAO__RE__STT__EPSILON_STATE__HPP__

#include <memory>

#include "yao/def/warn.hpp"
#include "yao/re/stt/State.hpp"

namespace yao::re::stt {

YAO_WARN_PUSH
YAO_WARN_OFF__PADDING

template <typename Symbol> class EpsilonState : public State<Symbol> {
public:
  [[deprecated]] EpsilonState();
  static std::unique_ptr<EpsilonState> make();

  void match(const Symbol &symbol) override;
  bool is_final() const override;
  bool is_dead() const override;

  EpsilonState(const EpsilonState &) = delete;
  EpsilonState(EpsilonState &&) = delete;
  EpsilonState &operator=(const EpsilonState &) = delete;
  EpsilonState &operator=(EpsilonState &&) = delete;

private:
  enum class Label {
    FINAL,
    DEAD,
  };

private:
  Label _label;
};

YAO_WARN_POP

} // namespace yao::re::stt

#include "yao/re/stt/EpsilonState.ipp"

#endif
