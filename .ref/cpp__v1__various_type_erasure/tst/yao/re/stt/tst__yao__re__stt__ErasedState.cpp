#include <typeindex>

#include "yao/def/check.hpp"
#include "yao/re/stt/ConcatState.hpp"
#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/ErasedState.hpp"
#include "yao/re/stt/KleeneState.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UnionState.hpp"

int main() {

  using ErasedState = yao::re::stt::ErasedState<int>;
  using EpsilonState = yao::re::stt::EpsilonState<int>;
  using SymbolState = yao::re::stt::SymbolState<int>;
  using KleeneErasedState = yao::re::stt::KleeneState<ErasedState>;
  using ConcatErasedState = yao::re::stt::ConcatState<ErasedState, ErasedState>;
  using UnionErasedState = yao::re::stt::UnionState<ErasedState, ErasedState>;

  {
    ErasedState erased_state_0{EpsilonState{}};
    ErasedState erased_state_1{ErasedState{EpsilonState{}}};
    ErasedState erased_state_2{ErasedState{ErasedState{EpsilonState{}}}};
    YAO_CHECK(erased_state_0 == erased_state_1);
    YAO_CHECK(erased_state_0 == erased_state_2);
  }

  {
    ErasedState erased_epsilon_state{EpsilonState{}};
    YAO_CHECK(erased_epsilon_state.is_final() == true);
    YAO_CHECK(erased_epsilon_state.is_dead() == false);

    erased_epsilon_state.match(0);
    YAO_CHECK(erased_epsilon_state.is_final() == false);
    YAO_CHECK(erased_epsilon_state.is_dead() == true);
  }

  {
    ErasedState erased_symbol_state{SymbolState{0}};
    YAO_CHECK(erased_symbol_state.is_final() == false);
    YAO_CHECK(erased_symbol_state.is_dead() == false);

    erased_symbol_state.match(0);
    YAO_CHECK(erased_symbol_state.is_final() == true);
    YAO_CHECK(erased_symbol_state.is_dead() == false);

    erased_symbol_state.match(0);
    YAO_CHECK(erased_symbol_state.is_final() == false);
    YAO_CHECK(erased_symbol_state.is_dead() == true);
  }

  {
    ErasedState erased_kleene_state{KleeneErasedState{SymbolState{0}}};
    YAO_CHECK(erased_kleene_state.is_final() == true);
    YAO_CHECK(erased_kleene_state.is_dead() == false);

    erased_kleene_state.match(0);
    YAO_CHECK(erased_kleene_state.is_final() == true);
    YAO_CHECK(erased_kleene_state.is_dead() == false);

    erased_kleene_state.match(0);
    YAO_CHECK(erased_kleene_state.is_final() == true);
    YAO_CHECK(erased_kleene_state.is_dead() == false);

    erased_kleene_state.match(1);
    YAO_CHECK(erased_kleene_state.is_final() == false);
    YAO_CHECK(erased_kleene_state.is_dead() == true);
  }

  {
    ErasedState erased_concat_state{
        ConcatErasedState{SymbolState{0}, SymbolState{1}}};
    YAO_CHECK(erased_concat_state.is_final() == false);
    YAO_CHECK(erased_concat_state.is_dead() == false);

    erased_concat_state.match(0);
    YAO_CHECK(erased_concat_state.is_final() == false);
    YAO_CHECK(erased_concat_state.is_dead() == false);

    erased_concat_state.match(1);
    YAO_CHECK(erased_concat_state.is_final() == true);
    YAO_CHECK(erased_concat_state.is_dead() == false);

    erased_concat_state.match(0);
    YAO_CHECK(erased_concat_state.is_final() == false);
    YAO_CHECK(erased_concat_state.is_dead() == true);
  }

  {
    ErasedState erased_union_state{
        UnionErasedState{SymbolState{0}, SymbolState{1}}};
    YAO_CHECK(erased_union_state.is_final() == false);
    YAO_CHECK(erased_union_state.is_dead() == false);

    erased_union_state.match(0);
    YAO_CHECK(erased_union_state.is_final() == true);
    YAO_CHECK(erased_union_state.is_dead() == false);

    erased_union_state.match(0);
    YAO_CHECK(erased_union_state.is_final() == false);
    YAO_CHECK(erased_union_state.is_dead() == true);
  }

  {
    ErasedState erased_state{EpsilonState{}};
    YAO_CHECK((erased_state == erased_state) == true);
    YAO_CHECK((erased_state != erased_state) == false);
    YAO_CHECK((erased_state < erased_state) == false);
    YAO_CHECK((erased_state <= erased_state) == true);
    YAO_CHECK((erased_state > erased_state) == false);
    YAO_CHECK((erased_state >= erased_state) == true);
  }

  {
    ErasedState erased_epsilon_state{EpsilonState{}};
    ErasedState erased_symbol_state_0{SymbolState{0}};
    ErasedState erased_symbol_state_1{SymbolState{1}};
    ErasedState erased_kleene_state_0{KleeneErasedState{SymbolState{0}}};
    ErasedState erased_kleene_state_1{KleeneErasedState{SymbolState{1}}};
    ErasedState erased_concat_state_00{
        ConcatErasedState{SymbolState{0}, SymbolState{0}}};
    ErasedState erased_concat_state_01{
        ConcatErasedState{SymbolState{0}, SymbolState{1}}};
    ErasedState erased_union_state_00{
        UnionErasedState{SymbolState{0}, SymbolState{0}}};
    ErasedState erased_union_state_01{
        UnionErasedState{SymbolState{0}, SymbolState{1}}};

    YAO_CHECK((erased_epsilon_state <=> erased_symbol_state_0) ==
              (std::type_index{typeid(EpsilonState)} <=>
               std::type_index{typeid(SymbolState)}));
    YAO_CHECK(erased_symbol_state_0 < erased_symbol_state_1);
    YAO_CHECK((erased_symbol_state_1 <=> erased_kleene_state_0) ==
              (std::type_index{typeid(SymbolState)} <=>
               std::type_index{typeid(KleeneErasedState)}));
    YAO_CHECK(erased_kleene_state_0 < erased_kleene_state_1);
    YAO_CHECK((erased_kleene_state_1 <=> erased_concat_state_00) ==
              (std::type_index{typeid(KleeneErasedState)} <=>
               std::type_index{typeid(ConcatErasedState)}));
    YAO_CHECK(erased_concat_state_00 < erased_concat_state_01);
    YAO_CHECK((erased_concat_state_01 <=> erased_union_state_00) ==
              (std::type_index{typeid(ConcatErasedState)} <=>
               std::type_index{typeid(UnionErasedState)}));
    YAO_CHECK(erased_union_state_00 < erased_union_state_01);
  }

  return 0;
}
