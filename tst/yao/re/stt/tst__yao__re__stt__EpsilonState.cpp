#include <memory>

#include "yao/def/check.hpp"
#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/State.hpp"

int main() {

  using State = yao::re::stt::State<int>;
  using EpsilonState = yao::re::stt::EpsilonState<int>;

  {
    std::unique_ptr<EpsilonState> epsilon_state = EpsilonState::make();
    YAO_CHECK(epsilon_state->is_final() == true);
    YAO_CHECK(epsilon_state->is_dead() == false);

    epsilon_state->match(0);
    YAO_CHECK(epsilon_state->is_final() == false);
    YAO_CHECK(epsilon_state->is_dead() == true);

    epsilon_state->match(0);
    YAO_CHECK(epsilon_state->is_final() == false);
    YAO_CHECK(epsilon_state->is_dead() == true);
  }

  {
    std::unique_ptr<State> state = EpsilonState::make();
    YAO_CHECK(state->is_final() == true);
    YAO_CHECK(state->is_dead() == false);

    state->match(0);
    YAO_CHECK(state->is_final() == false);
    YAO_CHECK(state->is_dead() == true);

    state->match(1);
    YAO_CHECK(state->is_final() == false);
    YAO_CHECK(state->is_dead() == true);
  }

  return 0;
}
