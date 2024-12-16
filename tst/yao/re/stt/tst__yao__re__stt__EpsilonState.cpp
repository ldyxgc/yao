#include "yao/def/check.hpp"
#include "yao/re/stt/EpsilonState.hpp"

int main() {

  using EpsilonState = yao::re::stt::EpsilonState<int>;

  {
    auto epsilon_state = EpsilonState::make();
    YAO_CHECK(epsilon_state->is_final() == true);
    YAO_CHECK(epsilon_state->is_dead() == false);

    epsilon_state->match(0);
    YAO_CHECK(epsilon_state->is_final() == false);
    YAO_CHECK(epsilon_state->is_dead() == true);

    epsilon_state->match(0);
    YAO_CHECK(epsilon_state->is_final() == false);
    YAO_CHECK(epsilon_state->is_dead() == true);
  }

  return 0;
}
