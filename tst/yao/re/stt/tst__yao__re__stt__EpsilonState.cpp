#include "yao/re/stt/EpsilonState.hpp"

#include "yao/def/check.hpp"

int main() {

  yao::re::stt::EpsilonState<int> epsilon_state;
  YAO_CHECK(epsilon_state.is_final() == true);
  YAO_CHECK(epsilon_state.is_dead() == false);

  epsilon_state.match(0);
  YAO_CHECK(epsilon_state.is_final() == false);
  YAO_CHECK(epsilon_state.is_dead() == true);

  epsilon_state.match(0);
  YAO_CHECK(epsilon_state.is_final() == false);
  YAO_CHECK(epsilon_state.is_dead() == true);

  return 0;
}
