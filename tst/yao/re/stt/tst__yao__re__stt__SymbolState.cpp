#include "yao/def/check.hpp"
#include "yao/re/stt/SymbolState.hpp"

int main() {

  using SymbolState = yao::re::stt::SymbolState<int>;

  {
    auto symbol_state = SymbolState::make(0);
    YAO_CHECK(symbol_state->is_final() == false);
    YAO_CHECK(symbol_state->is_dead() == false);

    symbol_state->match(0);
    YAO_CHECK(symbol_state->is_final() == true);
    YAO_CHECK(symbol_state->is_dead() == false);

    symbol_state->match(0);
    YAO_CHECK(symbol_state->is_final() == false);
    YAO_CHECK(symbol_state->is_dead() == true);

    symbol_state->match(0);
    YAO_CHECK(symbol_state->is_final() == false);
    YAO_CHECK(symbol_state->is_dead() == true);
  }

  {
    auto symbol_state = SymbolState::make(0);
    YAO_CHECK(symbol_state->is_final() == false);
    YAO_CHECK(symbol_state->is_dead() == false);

    symbol_state->match(1);
    YAO_CHECK(symbol_state->is_final() == false);
    YAO_CHECK(symbol_state->is_dead() == true);

    symbol_state->match(0);
    YAO_CHECK(symbol_state->is_final() == false);
    YAO_CHECK(symbol_state->is_dead() == true);
  }

  return 0;
}
