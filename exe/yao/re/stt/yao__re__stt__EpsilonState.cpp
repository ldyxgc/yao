#include <iostream>

#include "yao/prt/PrintValueArgs.hpp"
#include "yao/prt/print_value.hpp"
#include "yao/re/stt/EpsilonState.hpp"

int main() {

  using std::cout;
  using yao::prt::print_value;
  using yao::prt::PrintValueArgs;
  using yao::re::stt::EpsilonState;

  auto print_value_n = [](const auto &value, const PrintValueArgs &args = {}) {
    print_value(cout, value, args);
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
    print_value_n(epsilon_state);
    print_value_n(epsilon_state, {.print_type_args = {.scope = true}});
    print_value_n(epsilon_state, {.print_type_args = {.tmpl_args = true}});
    print_value_n(epsilon_state,
                  {.print_type_args = {.scope = true, .tmpl_args = true}});
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
