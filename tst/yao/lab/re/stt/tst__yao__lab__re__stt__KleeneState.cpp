#include "yao/def/check.hpp"
#include "yao/lab/re/stt/KleeneState.hpp"
#include "yao/lab/re/stt/StateType.hpp"
#include "yao/lab/re/stt/SymbolState.hpp"
#include "yao/lab/re/stt/c_o_State.hpp"

int main() {

  using yao::lab::re::stt::c_o_State;
  using yao::lab::re::stt::KleeneState;
  using yao::lab::re::stt::StateType;
  using yao::lab::re::stt::SymbolState;

  {
    KleeneState<SymbolState<int>> kleene_state_0{0};
    KleeneState kleene_state_1{SymbolState{0}};
    KleeneState kleene_state_2{KleeneState{SymbolState{0}}};
    KleeneState kleene_state_3{KleeneState{KleeneState{SymbolState{0}}}};
    YAO_CHECK(typeid(kleene_state_0) == typeid(kleene_state_1));
    YAO_CHECK(typeid(kleene_state_0) == typeid(kleene_state_2));
    YAO_CHECK(typeid(kleene_state_0) == typeid(kleene_state_3));
  }

  {
    KleeneState<KleeneState<SymbolState<int>>> kleene_state_0{SymbolState{0}};
    KleeneState<KleeneState<SymbolState<int>>> kleene_state_1{
        KleeneState{SymbolState{0}}};
    KleeneState<KleeneState<SymbolState<int>>> kleene_state_2{
        KleeneState{KleeneState{SymbolState{0}}}};
    KleeneState<KleeneState<SymbolState<int>>> kleene_state_3{
        KleeneState{KleeneState{KleeneState{SymbolState{0}}}}};
    KleeneState kleene_state_4{kleene_state_0};
    KleeneState kleene_state_5{KleeneState{kleene_state_0}};
    KleeneState kleene_state_6{KleeneState{KleeneState{kleene_state_0}}};
    YAO_CHECK(typeid(kleene_state_0) == typeid(kleene_state_1));
    YAO_CHECK(typeid(kleene_state_0) == typeid(kleene_state_2));
    YAO_CHECK(typeid(kleene_state_0) == typeid(kleene_state_3));
    YAO_CHECK(typeid(kleene_state_0) == typeid(kleene_state_4));
    YAO_CHECK(typeid(kleene_state_0) == typeid(kleene_state_5));
    YAO_CHECK(typeid(kleene_state_0) == typeid(kleene_state_6));
  }

  {
    KleeneState kleene_state{SymbolState{0}};
    YAO_CHECK(c_o_State<decltype(kleene_state)>);

    YAO_CHECK((kleene_state == kleene_state) == true);
    YAO_CHECK((kleene_state != kleene_state) == false);
    YAO_CHECK((kleene_state < kleene_state) == false);
    YAO_CHECK((kleene_state <= kleene_state) == true);
    YAO_CHECK((kleene_state > kleene_state) == false);
    YAO_CHECK((kleene_state >= kleene_state) == true);

    YAO_CHECK(kleene_state.type() == StateType::KleeneState);
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

  return 0;
}
