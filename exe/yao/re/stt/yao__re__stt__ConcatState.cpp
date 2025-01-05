#include <iostream>

#include "yao/prt/print_value.hpp"
#include "yao/re/stt/ConcatState.hpp"
#include "yao/re/stt/SymbolState.hpp"

int main() {

  using std::cout;
  using yao::prt::print_value;
  using yao::re::stt::ConcatState;
  using yao::re::stt::SymbolState;

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
    ConcatState concat_state{SymbolState{0}, SymbolState{1}};
    print_value_n.operator()(concat_state);
    print_value_n.operator()<true>(concat_state);
    print_value_n.operator()<false, true>(concat_state);
    print_value_n.operator()<true, true>(concat_state);
  }
  cout << '\n';
  {
    ConcatState concat_state{SymbolState{0}, SymbolState{1}};
    print_state_n(concat_state);
    match_print_n(concat_state, 1);
  }
  cout << '\n';
  {
    ConcatState concat_state{SymbolState{0}, SymbolState{1}};
    print_state_n(concat_state);
    match_print_n(concat_state, 0);
    match_print_n(concat_state, 0);
  }
  cout << '\n';
  {
    ConcatState concat_state{SymbolState{0}, SymbolState{1}};
    print_state_n(concat_state);
    match_print_n(concat_state, 0);
    match_print_n(concat_state, 1);
    match_print_n(concat_state, 0);
  }

  return 0;
}
