#include <concepts>
#include <utility>

#include "yao/def/check.hpp"
#include "yao/re/stt/KleeneState.hpp"
#include "yao/re/stt/SymbolState.hpp"

int main() {

  using yao::re::stt::KleeneState;
  using yao::re::stt::SymbolState;

  {
    using TargetState = KleeneState<SymbolState<int>>;

    KleeneState kleene_state_a{SymbolState<int>{0}};
    static_assert(std::same_as<decltype(kleene_state_a), TargetState>);

    SymbolState<int> symbol_state{0};
    KleeneState kleene_state_b{symbol_state};
    static_assert(std::same_as<decltype(kleene_state_b), TargetState>);
    KleeneState kleene_state_c{std::move(symbol_state)};
    static_assert(std::same_as<decltype(kleene_state_c), TargetState>);

    const SymbolState<int> const_symbol_state{0};
    KleeneState kleene_state_d{const_symbol_state};
    static_assert(std::same_as<decltype(kleene_state_d), TargetState>);
    KleeneState kleene_state_e{std::move(const_symbol_state)};
    static_assert(std::same_as<decltype(kleene_state_e), TargetState>);
  }

  {
    KleeneState<SymbolState<int>> kleene_state{0};

    SymbolState symbol_state{0};
    KleeneState kleene_state_a{symbol_state};
    KleeneState kleene_state_b{KleeneState{symbol_state}};
    KleeneState kleene_state_c{KleeneState{KleeneState{symbol_state}}};
    KleeneState kleene_state_d{kleene_state};
    KleeneState kleene_state_e{KleeneState{kleene_state}};
    KleeneState kleene_state_f{KleeneState{KleeneState{kleene_state}}};

    using std::same_as;
    static_assert(same_as<decltype(kleene_state_a), decltype(kleene_state)>);
    static_assert(same_as<decltype(kleene_state_b), decltype(kleene_state)>);
    static_assert(same_as<decltype(kleene_state_c), decltype(kleene_state)>);
    static_assert(same_as<decltype(kleene_state_d), decltype(kleene_state)>);
    static_assert(same_as<decltype(kleene_state_e), decltype(kleene_state)>);
    static_assert(same_as<decltype(kleene_state_f), decltype(kleene_state)>);
  }

  {
    KleeneState<KleeneState<SymbolState<int>>> kleene_state{SymbolState{0}};

    KleeneState<KleeneState<SymbolState<int>>> kleene_state_a{
        KleeneState{SymbolState{0}}};
    KleeneState<KleeneState<SymbolState<int>>> kleene_state_b{
        KleeneState{KleeneState{SymbolState{0}}}};
    KleeneState<KleeneState<SymbolState<int>>> kleene_state_c{
        KleeneState{KleeneState{KleeneState{SymbolState{0}}}}};
    KleeneState kleene_state_d{kleene_state};
    KleeneState kleene_state_e{KleeneState{kleene_state}};
    KleeneState kleene_state_f{KleeneState{KleeneState{kleene_state}}};

    using std::same_as;
    static_assert(same_as<decltype(kleene_state_a), decltype(kleene_state)>);
    static_assert(same_as<decltype(kleene_state_b), decltype(kleene_state)>);
    static_assert(same_as<decltype(kleene_state_c), decltype(kleene_state)>);
    static_assert(same_as<decltype(kleene_state_d), decltype(kleene_state)>);
    static_assert(same_as<decltype(kleene_state_e), decltype(kleene_state)>);
    static_assert(same_as<decltype(kleene_state_f), decltype(kleene_state)>);
  }

  {
    KleeneState kleene_state{SymbolState{0}};
    YAO_CHECK(kleene_state.is_final() == true);
    YAO_CHECK(kleene_state.is_dead() == false);

    kleene_state.match(1);
    YAO_CHECK(kleene_state.is_final() == false);
    YAO_CHECK(kleene_state.is_dead() == true);

    kleene_state.match(0);
    YAO_CHECK(kleene_state.is_final() == false);
    YAO_CHECK(kleene_state.is_dead() == true);
  }

  {
    KleeneState kleene_state{SymbolState{0}};
    YAO_CHECK(kleene_state.is_final() == true);
    YAO_CHECK(kleene_state.is_dead() == false);

    kleene_state.match(0);
    YAO_CHECK(kleene_state.is_final() == true);
    YAO_CHECK(kleene_state.is_dead() == false);

    kleene_state.match(1);
    YAO_CHECK(kleene_state.is_final() == false);
    YAO_CHECK(kleene_state.is_dead() == true);

    kleene_state.match(0);
    YAO_CHECK(kleene_state.is_final() == false);
    YAO_CHECK(kleene_state.is_dead() == true);
  }

  {
    KleeneState kleene_state{SymbolState{0}};
    YAO_CHECK(kleene_state.is_final() == true);
    YAO_CHECK(kleene_state.is_dead() == false);

    kleene_state.match(0);
    YAO_CHECK(kleene_state.is_final() == true);
    YAO_CHECK(kleene_state.is_dead() == false);

    kleene_state.match(0);
    YAO_CHECK(kleene_state.is_final() == true);
    YAO_CHECK(kleene_state.is_dead() == false);

    kleene_state.match(1);
    YAO_CHECK(kleene_state.is_final() == false);
    YAO_CHECK(kleene_state.is_dead() == true);

    kleene_state.match(0);
    YAO_CHECK(kleene_state.is_final() == false);
    YAO_CHECK(kleene_state.is_dead() == true);
  }

  {
    KleeneState inner_state{SymbolState{0}};
    KleeneState<decltype(inner_state)> outer_state{inner_state};
    YAO_CHECK(outer_state.is_final() == true);
    YAO_CHECK(outer_state.is_dead() == false);

    outer_state.match(1);
    YAO_CHECK(outer_state.is_final() == false);
    YAO_CHECK(outer_state.is_dead() == true);

    outer_state.match(0);
    YAO_CHECK(outer_state.is_final() == false);
    YAO_CHECK(outer_state.is_dead() == true);
  }

  {
    KleeneState inner_state{SymbolState{0}};
    KleeneState<decltype(inner_state)> outer_state{inner_state};
    YAO_CHECK(outer_state.is_final() == true);
    YAO_CHECK(outer_state.is_dead() == false);

    outer_state.match(0);
    YAO_CHECK(outer_state.is_final() == true);
    YAO_CHECK(outer_state.is_dead() == false);

    outer_state.match(1);
    YAO_CHECK(outer_state.is_final() == false);
    YAO_CHECK(outer_state.is_dead() == true);

    outer_state.match(0);
    YAO_CHECK(outer_state.is_final() == false);
    YAO_CHECK(outer_state.is_dead() == true);
  }

  {
    KleeneState inner_state{SymbolState{0}};
    KleeneState<decltype(inner_state)> outer_state{inner_state};
    YAO_CHECK(outer_state.is_final() == true);
    YAO_CHECK(outer_state.is_dead() == false);

    outer_state.match(0);
    YAO_CHECK(outer_state.is_final() == true);
    YAO_CHECK(outer_state.is_dead() == false);

    outer_state.match(0);
    YAO_CHECK(outer_state.is_final() == true);
    YAO_CHECK(outer_state.is_dead() == false);

    outer_state.match(1);
    YAO_CHECK(outer_state.is_final() == false);
    YAO_CHECK(outer_state.is_dead() == true);

    outer_state.match(0);
    YAO_CHECK(outer_state.is_final() == false);
    YAO_CHECK(outer_state.is_dead() == true);
  }

  {
    KleeneState kleene_state{SymbolState{0}};
    YAO_CHECK((kleene_state == kleene_state) == true);
    YAO_CHECK((kleene_state != kleene_state) == false);
    YAO_CHECK((kleene_state < kleene_state) == false);
    YAO_CHECK((kleene_state <= kleene_state) == true);
    YAO_CHECK((kleene_state > kleene_state) == false);
    YAO_CHECK((kleene_state >= kleene_state) == true);
  }

  {
    KleeneState<SymbolState<int>> kleene_state_0{0}, kleene_state_1{1};
    YAO_CHECK((kleene_state_0 == kleene_state_1) == false);
    YAO_CHECK((kleene_state_0 != kleene_state_1) == true);
    YAO_CHECK((kleene_state_0 < kleene_state_1) == true);
    YAO_CHECK((kleene_state_0 <= kleene_state_1) == true);
    YAO_CHECK((kleene_state_0 > kleene_state_1) == false);
    YAO_CHECK((kleene_state_0 >= kleene_state_1) == false);
  }

  return 0;
}
