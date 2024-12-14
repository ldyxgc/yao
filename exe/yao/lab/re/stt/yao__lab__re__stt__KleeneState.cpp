#include <iostream>

#include "yao/lab/prt/osprint_value.hpp"
#include "yao/lab/re/stt/KleeneState.hpp"
#include "yao/lab/re/stt/SymbolState.hpp"

int main() {

  using std::cout;
  using yao::lab::prt::osprint_value;
  using yao::lab::re::stt::KleeneState;
  using yao::lab::re::stt::SymbolState;

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
    KleeneState kleene_state{SymbolState{0}};
    print_value.operator()(kleene_state);
    print_value.operator()<true>(kleene_state);
    print_value.operator()<false, true>(kleene_state);
    print_value.operator()<true, true>(kleene_state);
    cout << '\n';
    osprint_value(cout, kleene_state.type());
    cout << '\n';
  }
  cout << '\n';
  {
    KleeneState kleene_state{SymbolState{0}};
    print_state(kleene_state);
    match_print(kleene_state, 1);
    match_print(kleene_state, 0);
  }
  cout << '\n';
  {
    KleeneState kleene_state{SymbolState{0}};
    print_state(kleene_state);
    match_print(kleene_state, 0);
    match_print(kleene_state, 1);
    match_print(kleene_state, 0);
  }
  cout << '\n';
  {
    KleeneState kleene_state{SymbolState{0}};
    print_state(kleene_state);
    match_print(kleene_state, 0);
    match_print(kleene_state, 0);
    match_print(kleene_state, 1);
    match_print(kleene_state, 0);
  }

  return 0;
}
