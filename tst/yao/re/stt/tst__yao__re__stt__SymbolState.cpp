#include "yao/def/check.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/c_o_State.hpp"

int main() {

  using yao::re::stt::c_o_State;
  using yao::re::stt::SymbolState;

  {
    SymbolState symbol_state{0};
    YAO_CHECK(c_o_State<decltype(symbol_state)>);
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
