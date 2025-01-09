#include <iostream>

#include "yao/prt/print_value.hpp"
#include "yao/re/stt/EpsilonState.hpp"

int main() {

  using std::cout;
  using yao::prt::print_value;
  using yao::re::stt::EpsilonState;

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
    EpsilonState<int> epsilon_state;
    print_value_n.operator()(epsilon_state);
    print_value_n.operator()<true>(epsilon_state);
    print_value_n.operator()<false, true>(epsilon_state);
    print_value_n.operator()<true, true>(epsilon_state);
  }
  cout << '\n';
  {
    EpsilonState<int> epsilon_state;
    print_state_n(epsilon_state);
    match_print_n(epsilon_state, 0);
    match_print_n(epsilon_state, 0);
  }

  return 0;
}
