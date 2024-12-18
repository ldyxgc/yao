#include <memory>

#include "yao/def/check.hpp"
#include "yao/re/stt/State.hpp"
#include "yao/re/stt/SymbolState.hpp"

int main() {

  using State = yao::re::stt::State<int>;
  using SymbolState = yao::re::stt::SymbolState<int>;

  {
    std::unique_ptr<SymbolState> symbol_state = SymbolState::make(0);
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
    std::unique_ptr<State> state = SymbolState::make(0);
    YAO_CHECK(state->is_final() == false);
    YAO_CHECK(state->is_dead() == false);

    state->match(1);
    YAO_CHECK(state->is_final() == false);
    YAO_CHECK(state->is_dead() == true);

    state->match(0);
    YAO_CHECK(state->is_final() == false);
    YAO_CHECK(state->is_dead() == true);
  }

  return 0;
}
