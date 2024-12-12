#include "yao/def/check.hpp"
#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/StateType.hpp"
#include "yao/re/stt/c_o_State.hpp"

int main() {

  using yao::re::stt::c_o_State;
  using yao::re::stt::EpsilonState;
  using yao::re::stt::StateType;

  {
    EpsilonState<int> epsilon_state;
    YAO_CHECK(c_o_State<decltype(epsilon_state)>);

    YAO_CHECK((epsilon_state == epsilon_state) == true);
    YAO_CHECK((epsilon_state != epsilon_state) == false);
    YAO_CHECK((epsilon_state < epsilon_state) == false);
    YAO_CHECK((epsilon_state <= epsilon_state) == true);
    YAO_CHECK((epsilon_state > epsilon_state) == false);
    YAO_CHECK((epsilon_state >= epsilon_state) == true);

    YAO_CHECK(epsilon_state.type() == StateType::EpsilonState);
  }

  {
    EpsilonState<int> epsilon_state;
    YAO_CHECK(epsilon_state.is_final() == true);
    YAO_CHECK(epsilon_state.is_dead() == false);

    epsilon_state.match(0);
    YAO_CHECK(epsilon_state.is_final() == false);
    YAO_CHECK(epsilon_state.is_dead() == true);
  }

  return 0;
}
