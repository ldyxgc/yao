#include "yao/def/check.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UnionState.hpp"

int main() {

  using yao::re::stt::SymbolState;
  using yao::re::stt::UnionState;

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

  {
    UnionState union_state{SymbolState{0}, SymbolState{1}};
    YAO_CHECK((union_state == union_state) == true);
    YAO_CHECK((union_state != union_state) == false);
    YAO_CHECK((union_state < union_state) == false);
    YAO_CHECK((union_state <= union_state) == true);
    YAO_CHECK((union_state > union_state) == false);
    YAO_CHECK((union_state >= union_state) == true);
  }

  {
    UnionState union_state_01{SymbolState{0}, SymbolState{1}},
        union_state_10{SymbolState{1}, SymbolState{0}};
    YAO_CHECK((union_state_01 == union_state_10) == false);
    YAO_CHECK((union_state_01 != union_state_10) == true);
    YAO_CHECK((union_state_01 < union_state_10) == true);
    YAO_CHECK((union_state_01 <= union_state_10) == true);
    YAO_CHECK((union_state_01 > union_state_10) == false);
    YAO_CHECK((union_state_01 >= union_state_10) == false);
  }

  return 0;
}
