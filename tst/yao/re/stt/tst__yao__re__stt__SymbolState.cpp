#include "yao/def/check.hpp"
#include "yao/re/stt/SymbolState.hpp"

int main() {

  using yao::re::stt::SymbolState;

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

    symbol_state.match(0);
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == true);
  }

  {
    SymbolState symbol_state{0};
    YAO_CHECK((symbol_state == symbol_state) == true);
    YAO_CHECK((symbol_state != symbol_state) == false);
    YAO_CHECK((symbol_state < symbol_state) == false);
    YAO_CHECK((symbol_state <= symbol_state) == true);
    YAO_CHECK((symbol_state > symbol_state) == false);
    YAO_CHECK((symbol_state >= symbol_state) == true);
  }

  {
    SymbolState symbol_state_0{0}, symbol_state_1{1};
    YAO_CHECK((symbol_state_0 == symbol_state_1) == false);
    YAO_CHECK((symbol_state_0 != symbol_state_1) == true);
    YAO_CHECK((symbol_state_0 < symbol_state_1) == true);
    YAO_CHECK((symbol_state_0 <= symbol_state_1) == true);
    YAO_CHECK((symbol_state_0 > symbol_state_1) == false);
    YAO_CHECK((symbol_state_0 >= symbol_state_1) == false);
  }

  return 0;
}
