#include <iostream>

#include "yao/prt/osprint_value.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UnionState.hpp"

int main() {

  using std::cout;
  using yao::prt::osprint_value;
  using yao::re::stt::SymbolState;
  using yao::re::stt::UnionState;

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
    UnionState union_state{SymbolState{0}, SymbolState{1}};
    print_value.operator()(union_state);
    print_value.operator()<true>(union_state);
    print_value.operator()<false, true>(union_state);
    print_value.operator()<true, true>(union_state);
    cout << '\n';
    osprint_value(cout, union_state.type());
    cout << '\n';
  }
  cout << '\n';
  { // 0|1
    UnionState union_state{SymbolState{0}, SymbolState{1}};
    print_state(union_state);
    match_print(union_state, 0);
    match_print(union_state, 1);
  }
  cout << '\n';
  { // 0|1
    UnionState union_state{SymbolState{0}, SymbolState{1}};
    print_state(union_state);
    match_print(union_state, 1);
    match_print(union_state, 2);
  }
  cout << '\n';
  { // 0|1
    UnionState union_state{SymbolState{0}, SymbolState{1}};
    print_state(union_state);
    match_print(union_state, 2);
    match_print(union_state, 0);
  }

  return 0;
}
