#include <iostream>

#include "yao/prt/print_value.hpp"
#include "yao/re/stt/ConcatState.hpp"
#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/ErasedState.hpp"
#include "yao/re/stt/KleeneState.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UnionState.hpp"

int main() {

  using std::cout;
  using yao::prt::print_value;
  using ErasedState = yao::re::stt::ErasedState<int>;
  using EpsilonState = yao::re::stt::EpsilonState<int>;
  using SymbolState = yao::re::stt::SymbolState<int>;
  using KleeneErasedState = yao::re::stt::KleeneState<ErasedState>;
  using ConcatErasedState = yao::re::stt::ConcatState<ErasedState, ErasedState>;
  using UnionErasedState = yao::re::stt::UnionState<ErasedState, ErasedState>;

  auto print_value_n = []<bool ns = false, bool tp = false>(const auto &value) {
    print_value<ns, tp>(cout, value);
    cout << '\n';
  };
  auto print_state_n = [&](const auto &state) {
    print_value_n(state);
    cout << "is_final: " << state.is_final() << ", is_dead: " << state.is_dead()
         << '\n';
  };
  auto match_print_n = [&](auto &state, auto symbol) {
    state.match(symbol);
    cout << ">> ";
    print_value(cout, symbol);
    cout << '\n';
    print_state_n(state);
  };

  {
    ErasedState erased_state{EpsilonState{}};
    print_value_n.operator()(erased_state);
    print_value_n.operator()<true>(erased_state);
    print_value_n.operator()<false, true>(erased_state);
    print_value_n.operator()<true, true>(erased_state);
  }
  cout << '\n';
  {
    ErasedState erased_epsilon_state{EpsilonState{}};
    print_state_n(erased_epsilon_state);
    match_print_n(erased_epsilon_state, 0);
  }
  cout << '\n';
  {
    ErasedState erased_symbol_state{SymbolState{0}};
    print_state_n(erased_symbol_state);
    match_print_n(erased_symbol_state, 0);
    match_print_n(erased_symbol_state, 0);
  }
  cout << '\n';
  {
    ErasedState erased_kleene_state{KleeneErasedState{SymbolState{0}}};
    print_state_n(erased_kleene_state);
    match_print_n(erased_kleene_state, 0);
    match_print_n(erased_kleene_state, 0);
    match_print_n(erased_kleene_state, 1);
  }
  cout << '\n';
  {
    ErasedState erased_concat_state{
        ConcatErasedState{SymbolState{0}, SymbolState{1}}};
    print_state_n(erased_concat_state);
    match_print_n(erased_concat_state, 0);
    match_print_n(erased_concat_state, 1);
    match_print_n(erased_concat_state, 0);
  }
  cout << '\n';
  {
    ErasedState erased_union_state{
        UnionErasedState{SymbolState{0}, SymbolState{1}}};
    print_state_n(erased_union_state);
    match_print_n(erased_union_state, 0);
    match_print_n(erased_union_state, 0);
  }

  return 0;
}
