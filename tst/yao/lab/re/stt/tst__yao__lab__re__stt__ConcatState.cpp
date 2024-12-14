#include "yao/def/check.hpp"
#include "yao/lab/re/stt/ConcatState.hpp"
#include "yao/lab/re/stt/KleeneState.hpp"
#include "yao/lab/re/stt/StateType.hpp"
#include "yao/lab/re/stt/SymbolState.hpp"
#include "yao/lab/re/stt/c_o_State.hpp"

int main() {

  using yao::lab::re::stt::c_o_State;
  using yao::lab::re::stt::ConcatState;
  using yao::lab::re::stt::KleeneState;
  using yao::lab::re::stt::StateType;
  using yao::lab::re::stt::SymbolState;

  {
    ConcatState concat_state{SymbolState{0}, SymbolState{1}};
    YAO_CHECK(c_o_State<decltype(concat_state)>);

    YAO_CHECK((concat_state == concat_state) == true);
    YAO_CHECK((concat_state != concat_state) == false);
    YAO_CHECK((concat_state < concat_state) == false);
    YAO_CHECK((concat_state <= concat_state) == true);
    YAO_CHECK((concat_state > concat_state) == false);
    YAO_CHECK((concat_state >= concat_state) == true);

    YAO_CHECK(concat_state.type() == StateType::ConcatState);
  }

  { // 01
    ConcatState concat_state{SymbolState{0}, SymbolState{1}};
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 01
    ConcatState concat_state{SymbolState{0}, SymbolState{1}};
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 01
    ConcatState concat_state{SymbolState{0}, SymbolState{1}};
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 0*1*
    ConcatState concat_state{KleeneState{SymbolState{0}},
                             KleeneState{SymbolState{1}}};
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(2);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 0*1*
    ConcatState concat_state{KleeneState{SymbolState{0}},
                             KleeneState{SymbolState{1}}};
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(2);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 0*1*
    ConcatState concat_state{KleeneState{SymbolState{0}},
                             KleeneState{SymbolState{1}}};
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 0*1*
    ConcatState concat_state{KleeneState{SymbolState{0}},
                             KleeneState{SymbolState{1}}};
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(2);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 0*1*
    ConcatState concat_state{KleeneState{SymbolState{0}},
                             KleeneState{SymbolState{1}}};
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 0*1*
    ConcatState concat_state{KleeneState{SymbolState{0}},
                             KleeneState{SymbolState{1}}};
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 0*1*
    ConcatState concat_state{KleeneState{SymbolState{0}},
                             KleeneState{SymbolState{1}}};
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(2);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 0*1*
    ConcatState concat_state{KleeneState{SymbolState{0}},
                             KleeneState{SymbolState{1}}};
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 0*1*
    ConcatState concat_state{KleeneState{SymbolState{0}},
                             KleeneState{SymbolState{1}}};
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  { // 0*1*
    ConcatState concat_state{KleeneState{SymbolState{0}},
                             KleeneState{SymbolState{1}}};
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(1);
    YAO_CHECK(concat_state.is_final() == true);
    YAO_CHECK(concat_state.is_dead() == false);

    concat_state.match(0);
    YAO_CHECK(concat_state.is_final() == false);
    YAO_CHECK(concat_state.is_dead() == true);
  }

  return 0;
}
