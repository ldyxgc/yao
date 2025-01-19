#include <concepts>
#include <utility>

#include "yao/def/check.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UnionState.hpp"

int main() {

  using yao::re::stt::SymbolState;
  using yao::re::stt::UnionState;

  {
    using TargetState = UnionState<SymbolState<int>, SymbolState<int>>;

    UnionState union_state_a{SymbolState{0}, SymbolState{1}};
    static_assert(std::same_as<decltype(union_state_a), TargetState>);

    SymbolState<int> lhs_0{0}, lhs_1{1};
    UnionState union_state_b{lhs_0, lhs_1};
    static_assert(std::same_as<decltype(union_state_b), TargetState>);
    UnionState union_state_c{std::move(lhs_0), lhs_1};
    static_assert(std::same_as<decltype(union_state_c), TargetState>);
    UnionState union_state_d{lhs_0, std::move(lhs_1)};
    static_assert(std::same_as<decltype(union_state_d), TargetState>);
    UnionState union_state_e{std::move(lhs_0), std::move(lhs_1)};
    static_assert(std::same_as<decltype(union_state_e), TargetState>);

    const SymbolState<int> c_lhs_0{0}, c_lhs_1{1};
    UnionState union_state_f{c_lhs_0, c_lhs_1};
    static_assert(std::same_as<decltype(union_state_f), TargetState>);
    UnionState union_state_g{std::move(c_lhs_0), c_lhs_1};
    static_assert(std::same_as<decltype(union_state_g), TargetState>);
    UnionState union_state_h{c_lhs_0, std::move(c_lhs_1)};
    static_assert(std::same_as<decltype(union_state_h), TargetState>);
    UnionState union_state_i{std::move(c_lhs_0), std::move(c_lhs_1)};
    static_assert(std::same_as<decltype(union_state_i), TargetState>);
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
