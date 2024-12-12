#include "yao/def/check.hpp"
#include "yao/re/stt/StateType.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UnionState.hpp"
#include "yao/re/stt/c_o_State.hpp"

int main() {

  using yao::re::stt::c_o_State;
  using yao::re::stt::StateType;
  using yao::re::stt::SymbolState;
  using yao::re::stt::UnionState;

  {
    UnionState union_state{SymbolState{0}, SymbolState{1}};
    YAO_CHECK(c_o_State<decltype(union_state)>);

    YAO_CHECK((union_state == union_state) == true);
    YAO_CHECK((union_state != union_state) == false);
    YAO_CHECK((union_state < union_state) == false);
    YAO_CHECK((union_state <= union_state) == true);
    YAO_CHECK((union_state > union_state) == false);
    YAO_CHECK((union_state >= union_state) == true);

    YAO_CHECK(union_state.type() == StateType::UnionState);
  }

  { // 0|1
    UnionState union_state{SymbolState{0}, SymbolState{1}};
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(0);
    YAO_CHECK(union_state.is_final() == true);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(1);
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == true);
  }

  { // 0|1
    UnionState union_state{SymbolState{0}, SymbolState{1}};
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(1);
    YAO_CHECK(union_state.is_final() == true);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(2);
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == true);
  }

  { // 0|1
    UnionState union_state{SymbolState{0}, SymbolState{1}};
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(2);
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == true);

    union_state.match(0);
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == true);
  }

  { // ((0|1)|2)|3
    UnionState union_state{
        UnionState{UnionState{SymbolState{0}, SymbolState{1}}, SymbolState{2}},
        SymbolState{3}};
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(0);
    YAO_CHECK(union_state.is_final() == true);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(1);
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == true);
  }

  { // (0|(1|2))|3
    UnionState union_state{
        UnionState{SymbolState{0}, UnionState{SymbolState{1}, SymbolState{2}}},
        SymbolState{3}};
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(1);
    YAO_CHECK(union_state.is_final() == true);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(2);
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == true);
  }

  { // (0|1)|(2|3)
    UnionState union_state{UnionState{SymbolState{0}, SymbolState{1}},
                           UnionState{SymbolState{2}, SymbolState{3}}};
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(2);
    YAO_CHECK(union_state.is_final() == true);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(3);
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == true);
  }

  { // 0|((1|2)|3)
    UnionState union_state{
        SymbolState{0},
        UnionState{UnionState{SymbolState{1}, SymbolState{2}}, SymbolState{3}}};
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(3);
    YAO_CHECK(union_state.is_final() == true);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(4);
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == true);
  }

  { // 0|(1|(2|3))
    UnionState union_state{
        SymbolState{0},
        UnionState{SymbolState{1}, UnionState{SymbolState{2}, SymbolState{3}}}};
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == false);

    union_state.match(4);
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == true);

    union_state.match(0);
    YAO_CHECK(union_state.is_final() == false);
    YAO_CHECK(union_state.is_dead() == true);
  }

  return 0;
}
