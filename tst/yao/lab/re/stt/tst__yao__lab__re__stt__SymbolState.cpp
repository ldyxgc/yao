#include "yao/def/check.hpp"
#include "yao/lab/re/stt/StateType.hpp"
#include "yao/lab/re/stt/SymbolState.hpp"
#include "yao/lab/re/stt/c_o_State.hpp"

int main() {

  using yao::lab::re::stt::c_o_State;
  using yao::lab::re::stt::StateType;
  using yao::lab::re::stt::SymbolState;

  {
    SymbolState symbol_state{0};
    YAO_CHECK(c_o_State<decltype(symbol_state)>);

    YAO_CHECK((symbol_state == symbol_state) == true);
    YAO_CHECK((symbol_state != symbol_state) == false);
    YAO_CHECK((symbol_state < symbol_state) == false);
    YAO_CHECK((symbol_state <= symbol_state) == true);
    YAO_CHECK((symbol_state > symbol_state) == false);
    YAO_CHECK((symbol_state >= symbol_state) == true);

    YAO_CHECK(symbol_state.type() == StateType::SymbolState);
  }

  {
    SymbolState symbol_state{0};
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == false);

    symbol_state.match(0);
    YAO_CHECK(symbol_state.is_final() == true);
    YAO_CHECK(symbol_state.is_dead() == false);

    symbol_state.match(0);
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == true);
  }

  {
    SymbolState symbol_state{0};
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == false);

    symbol_state.match(1);
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == true);

    symbol_state.match(0);
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == true);
  }

  return 0;
}
