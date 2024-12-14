#include <iostream>

#include "yao/lab/prt/osprint_value.hpp"
#include "yao/lab/re/stt/ConcatState.hpp"
#include "yao/lab/re/stt/EpsilonState.hpp"
#include "yao/lab/re/stt/ErasedState.hpp"
#include "yao/lab/re/stt/KleeneState.hpp"
#include "yao/lab/re/stt/SymbolState.hpp"
#include "yao/lab/re/stt/UnionState.hpp"

int main() {

  using std::cout;
  using yao::lab::prt::osprint_value;
  using ErasedState = yao::lab::re::stt::ErasedState<int>;
  using EpsilonState = yao::lab::re::stt::EpsilonState<int>;
  using SymbolState = yao::lab::re::stt::SymbolState<int>;
  using KleeneErasedState = yao::lab::re::stt::KleeneState<ErasedState>;
  using ConcatErasedState =
      yao::lab::re::stt::ConcatState<ErasedState, ErasedState>;
  using UnionErasedState =
      yao::lab::re::stt::UnionState<ErasedState, ErasedState>;

  auto print_value = []<bool ns = false, bool tp = false>(const auto &value) {
    osprint_value<ns, tp>(cout, value);
    cout << '\n';
  };
  auto print_state = [&](const auto &state) {
    print_value(state);
    cout << "is_final: " << state.is_final() << ", is_dead: " << state.is_dead()
         << '\n';
  };
  auto match_print = [&](auto &state, auto symbol) {
    state.match(symbol);
    cout << ">> ";
    osprint_value(cout, symbol);
    cout << '\n';
    print_state(state);
  };

  {
    ErasedState erased_state{EpsilonState{}};
    print_value.operator()(erased_state);
    print_value.operator()<true>(erased_state);
    print_value.operator()<false, true>(erased_state);
    print_value.operator()<true, true>(erased_state);
    cout << '\n';
    osprint_value(cout, erased_state.type());
    cout << '\n';
  }
  cout << '\n';
  {
    ErasedState erased_epsilon_state{EpsilonState{}};
    print_state(erased_epsilon_state);
    match_print(erased_epsilon_state, 0);
  }
  cout << '\n';
  {
    ErasedState erased_symbol_state{SymbolState{0}};
    print_state(erased_symbol_state);
    match_print(erased_symbol_state, 0);
    match_print(erased_symbol_state, 0);
  }
  cout << '\n';
  {
    ErasedState erased_kleene_state{KleeneErasedState{SymbolState{0}}};
    print_state(erased_kleene_state);
    match_print(erased_kleene_state, 0);
    match_print(erased_kleene_state, 0);
    match_print(erased_kleene_state, 1);
  }
  cout << '\n';
  {
    ErasedState erased_concat_state{
        ConcatErasedState{SymbolState{0}, SymbolState{1}}};
    print_state(erased_concat_state);
    match_print(erased_concat_state, 0);
    match_print(erased_concat_state, 1);
    match_print(erased_concat_state, 0);
  }
  cout << '\n';
  {
    ErasedState erased_union_state{
        UnionErasedState{SymbolState{0}, SymbolState{1}}};
    print_state(erased_union_state);
    match_print(erased_union_state, 0);
    match_print(erased_union_state, 0);
  }

  return 0;
}
