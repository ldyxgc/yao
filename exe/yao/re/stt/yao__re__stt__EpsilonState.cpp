#include <iostream>

#include "yao/prt/osprint_value.hpp"
#include "yao/re/stt/EpsilonState.hpp"

int main() {

  using std::cout;
  using yao::prt::osprint_value;
  using yao::re::stt::EpsilonState;

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
    EpsilonState<int> epsilon_state;
    print_value.operator()(epsilon_state);
    print_value.operator()<true>(epsilon_state);
    print_value.operator()<false, true>(epsilon_state);
    print_value.operator()<true, true>(epsilon_state);
    cout << '\n';
    osprint_value(cout, epsilon_state.type());
    cout << '\n';
  }
  cout << '\n';
  {
    EpsilonState<int> epsilon_state;
    print_state(epsilon_state);
    match_print(epsilon_state, 0);
  }

  return 0;
}
