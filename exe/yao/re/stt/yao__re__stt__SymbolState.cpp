#include <iostream>

#include "yao/prt/osprint_value.hpp"
#include "yao/re/stt/SymbolState.hpp"

int main() {

  using std::cout;
  using yao::prt::osprint_value;
  using yao::re::stt::SymbolState;

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
    SymbolState symbol_state(0);
    print_value.operator()(symbol_state);
    print_value.operator()<true>(symbol_state);
    print_value.operator()<false, true>(symbol_state);
    print_value.operator()<true, true>(symbol_state);
  }
  cout << '\n';
  {
    SymbolState symbol_state(0);
    print_state(symbol_state);
    match_print(symbol_state, 0);
    match_print(symbol_state, 0);
  }
  cout << '\n';
  {
    SymbolState symbol_state(0);
    print_state(symbol_state);
    match_print(symbol_state, 1);
    match_print(symbol_state, 0);
  }

  return 0;
}
