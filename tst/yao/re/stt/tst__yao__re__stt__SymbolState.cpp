#include <utility>

#include "yao/def/check.hpp"
#include "yao/re/stt/SymbolState.hpp"

int main() {

  using yao::re::stt::SymbolState;

  {
    SymbolState symbol_state_a{0};
    static_assert(std::same_as<decltype(symbol_state_a), SymbolState<int>>);

    int i{};
    SymbolState symbol_state_b{i};
    static_assert(std::same_as<decltype(symbol_state_b), SymbolState<int>>);
    SymbolState symbol_state_c{std::move(i)};
    static_assert(std::same_as<decltype(symbol_state_c), SymbolState<int>>);

    const int ci{};
    SymbolState symbol_state_d{ci};
    static_assert(std::same_as<decltype(symbol_state_d), SymbolState<int>>);
    SymbolState symbol_state_e{std::move(ci)};
    static_assert(std::same_as<decltype(symbol_state_e), SymbolState<int>>);
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
