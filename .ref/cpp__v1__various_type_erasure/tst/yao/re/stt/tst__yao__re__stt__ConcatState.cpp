#include <concepts>
#include <utility>

#include "yao/def/check.hpp"
#include "yao/re/stt/ConcatState.hpp"
#include "yao/re/stt/KleeneState.hpp"
#include "yao/re/stt/SymbolState.hpp"

int main() {

  using yao::re::stt::ConcatState;
  using yao::re::stt::KleeneState;
  using yao::re::stt::SymbolState;

  {
    using TargetState = ConcatState<SymbolState<int>, SymbolState<int>>;

    ConcatState concat_state_a{SymbolState{0}, SymbolState{1}};
    static_assert(std::same_as<decltype(concat_state_a), TargetState>);

    SymbolState<int> lhs_0{0}, lhs_1{1};
    ConcatState concat_state_b{lhs_0, lhs_1};
    static_assert(std::same_as<decltype(concat_state_b), TargetState>);
    ConcatState concat_state_c{std::move(lhs_0), lhs_1};
    static_assert(std::same_as<decltype(concat_state_c), TargetState>);
    ConcatState concat_state_d{lhs_0, std::move(lhs_1)};
    static_assert(std::same_as<decltype(concat_state_d), TargetState>);
    ConcatState concat_state_e{std::move(lhs_0), std::move(lhs_1)};
    static_assert(std::same_as<decltype(concat_state_e), TargetState>);

    const SymbolState<int> c_lhs_0{0}, c_lhs_1{1};
    ConcatState concat_state_f{c_lhs_0, c_lhs_1};
    static_assert(std::same_as<decltype(concat_state_f), TargetState>);
    ConcatState concat_state_g{std::move(c_lhs_0), c_lhs_1};
    static_assert(std::same_as<decltype(concat_state_g), TargetState>);
    ConcatState concat_state_h{c_lhs_0, std::move(c_lhs_1)};
    static_assert(std::same_as<decltype(concat_state_h), TargetState>);
    ConcatState concat_state_i{std::move(c_lhs_0), std::move(c_lhs_1)};
    static_assert(std::same_as<decltype(concat_state_i), TargetState>);
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

  {
    ConcatState concat_state{SymbolState{0}, SymbolState{1}};
    YAO_CHECK((concat_state == concat_state) == true);
    YAO_CHECK((concat_state != concat_state) == false);
    YAO_CHECK((concat_state < concat_state) == false);
    YAO_CHECK((concat_state <= concat_state) == true);
    YAO_CHECK((concat_state > concat_state) == false);
    YAO_CHECK((concat_state >= concat_state) == true);
  }

  {
    ConcatState concat_state_01{SymbolState{0}, SymbolState{1}},
        concat_state_10{SymbolState{1}, SymbolState{0}};
    YAO_CHECK((concat_state_01 == concat_state_10) == false);
    YAO_CHECK((concat_state_01 != concat_state_10) == true);
    YAO_CHECK((concat_state_01 < concat_state_10) == true);
    YAO_CHECK((concat_state_01 <= concat_state_10) == true);
    YAO_CHECK((concat_state_01 > concat_state_10) == false);
    YAO_CHECK((concat_state_01 >= concat_state_10) == false);
  }

  return 0;
}
