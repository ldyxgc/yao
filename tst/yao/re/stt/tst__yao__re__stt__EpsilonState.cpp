#include "yao/def/check.hpp"
#include "yao/re/stt/EpsilonState.hpp"

int main() {

  using EpsilonState = yao::re::stt::EpsilonState<int>;

  {
    EpsilonState epsilon_state;
    YAO_CHECK(epsilon_state.is_final() == true);
    YAO_CHECK(epsilon_state.is_dead() == false);

    epsilon_state.match(0);
    YAO_CHECK(epsilon_state.is_final() == false);
    YAO_CHECK(epsilon_state.is_dead() == true);

    epsilon_state.match(0);
    YAO_CHECK(epsilon_state.is_final() == false);
    YAO_CHECK(epsilon_state.is_dead() == true);
  }

  {
    EpsilonState epsilon_state;
    YAO_CHECK((epsilon_state == epsilon_state) == true);
    YAO_CHECK((epsilon_state != epsilon_state) == false);
    YAO_CHECK((epsilon_state < epsilon_state) == false);
    YAO_CHECK((epsilon_state <= epsilon_state) == true);
    YAO_CHECK((epsilon_state > epsilon_state) == false);
    YAO_CHECK((epsilon_state >= epsilon_state) == true);
  }

  return 0;
}
