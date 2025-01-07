#include <iostream>
#include <memory>

#include "yao/prt/print_value.hpp"
#include "yao/re/stt/ConcatState.hpp"
#include "yao/re/stt/ConcreteVirtualState.hpp"
#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/KleeneState.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UnionState.hpp"
#include "yao/re/stt/VirtualState.hpp"

int main() {

  using std::cout;
  using yao::prt::print_value;

  using EpsilonState = yao::re::stt::EpsilonState<int>;
  using SymbolState = yao::re::stt::SymbolState<int>;
  using KleeneState = yao::re::stt::KleeneState<SymbolState>;
  using ConcatState = yao::re::stt::ConcatState<SymbolState, SymbolState>;
  using UnionState = yao::re::stt::UnionState<SymbolState, SymbolState>;

  using VirtualState = yao::re::stt::VirtualState<int>;
  using yao::re::stt::ConcreteVirtualState;

  using EpsilonVirtualState = ConcreteVirtualState<EpsilonState>;
  using SymbolVirtualState = ConcreteVirtualState<SymbolState>;
  using KleeneVirtualState = ConcreteVirtualState<KleeneState>;
  using ConcatVirtualState = ConcreteVirtualState<ConcatState>;
  using UnionVirtualState = ConcreteVirtualState<UnionState>;

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
    EpsilonVirtualState epsilon_virtual_state{};
    print_value_n.operator()(epsilon_virtual_state);
    print_value_n.operator()<true>(epsilon_virtual_state);
    print_value_n.operator()<false, true>(epsilon_virtual_state);
    print_value_n.operator()<true, true>(epsilon_virtual_state);
  }
  cout << '\n';
  {
    EpsilonVirtualState epsilon_virtual_state{};
    VirtualState &virtual_state_epsilon = epsilon_virtual_state;
    print_value_n.operator()(virtual_state_epsilon);
    print_value_n.operator()<true>(virtual_state_epsilon);
    print_value_n.operator()<false, true>(virtual_state_epsilon);
    print_value_n.operator()<true, true>(virtual_state_epsilon);
  }
  cout << '\n';
  {
    std::unique_ptr<EpsilonVirtualState> epsilon_virtual_state{
        EpsilonVirtualState::make_uptr()};
    print_value_n.operator()(epsilon_virtual_state);
    print_value_n.operator()<true>(epsilon_virtual_state);
    print_value_n.operator()<false, true>(epsilon_virtual_state);
    print_value_n.operator()<true, true>(epsilon_virtual_state);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualState> virtual_state_epsilon{
        EpsilonVirtualState::make_uptr()};
    print_value_n.operator()(virtual_state_epsilon);
    print_value_n.operator()<true>(virtual_state_epsilon);
    print_value_n.operator()<false, true>(virtual_state_epsilon);
    print_value_n.operator()<true, true>(virtual_state_epsilon);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualState> virtual_state_epsilon{
        EpsilonVirtualState::make_uptr()};
    print_state_n(*virtual_state_epsilon);
    match_print_n(*virtual_state_epsilon, 0);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualState> virtual_state_symbol{
        SymbolVirtualState::make_uptr(0)};
    print_state_n(*virtual_state_symbol);
    match_print_n(*virtual_state_symbol, 0);
    match_print_n(*virtual_state_symbol, 0);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualState> virtual_state_kleene{
        KleeneVirtualState::make_uptr(SymbolState{0})};
    print_state_n(*virtual_state_kleene);
    match_print_n(*virtual_state_kleene, 0);
    match_print_n(*virtual_state_kleene, 0);
    match_print_n(*virtual_state_kleene, 1);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualState> virtual_state_concat{
        ConcatVirtualState::make_uptr(SymbolState{0}, SymbolState{1})};
    print_state_n(*virtual_state_concat);
    match_print_n(*virtual_state_concat, 0);
    match_print_n(*virtual_state_concat, 1);
    match_print_n(*virtual_state_concat, 0);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualState> virtual_state_union{
        UnionVirtualState::make_uptr(SymbolState{0}, SymbolState{1})};
    print_state_n(*virtual_state_union);
    match_print_n(*virtual_state_union, 0);
    match_print_n(*virtual_state_union, 0);
  }

  return 0;
}
