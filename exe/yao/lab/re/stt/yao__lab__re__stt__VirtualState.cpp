#include <iostream>
#include <memory>

#include "yao/lab/prt/osprint_value.hpp"
#include "yao/lab/re/stt/ConcatState.hpp"
#include "yao/lab/re/stt/EpsilonState.hpp"
#include "yao/lab/re/stt/KleeneState.hpp"
#include "yao/lab/re/stt/SymbolState.hpp"
#include "yao/lab/re/stt/UnionState.hpp"
#include "yao/lab/re/stt/VirtualState.hpp"
#include "yao/lab/re/stt/VirtualStateBase.hpp"

int main() {

  using std::cout;
  using yao::lab::prt::osprint_value;

  using EpsilonState = yao::lab::re::stt::EpsilonState<int>;
  using SymbolState = yao::lab::re::stt::SymbolState<int>;
  using KleeneState = yao::lab::re::stt::KleeneState<SymbolState>;
  using ConcatState = yao::lab::re::stt::ConcatState<SymbolState, SymbolState>;
  using UnionState = yao::lab::re::stt::UnionState<SymbolState, SymbolState>;

  using VirtualStateBase = yao::lab::re::stt::VirtualStateBase<int>;
  using yao::lab::re::stt::VirtualState;

  using EpsilonVirtualState = VirtualState<EpsilonState>;
  using SymbolVirtualState = VirtualState<SymbolState>;
  using KleeneVirtualState = VirtualState<KleeneState>;
  using ConcatVirtualState = VirtualState<ConcatState>;
  using UnionVirtualState = VirtualState<UnionState>;

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
    EpsilonVirtualState epsilon_virtual_state{};
    print_value.operator()(epsilon_virtual_state);
    print_value.operator()<true>(epsilon_virtual_state);
    print_value.operator()<false, true>(epsilon_virtual_state);
    print_value.operator()<true, true>(epsilon_virtual_state);
  }
  cout << '\n';
  {
    EpsilonVirtualState epsilon_virtual_state{};
    VirtualStateBase &virtual_state_epsilon = epsilon_virtual_state;
    print_value.operator()(virtual_state_epsilon);
    print_value.operator()<true>(virtual_state_epsilon);
    print_value.operator()<false, true>(virtual_state_epsilon);
    print_value.operator()<true, true>(virtual_state_epsilon);
  }
  cout << '\n';
  {
    std::unique_ptr<EpsilonVirtualState> epsilon_virtual_state{
        EpsilonVirtualState::make_uptr()};
    print_value.operator()(epsilon_virtual_state);
    print_value.operator()<true>(epsilon_virtual_state);
    print_value.operator()<false, true>(epsilon_virtual_state);
    print_value.operator()<true, true>(epsilon_virtual_state);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualStateBase> virtual_state_epsilon{
        EpsilonVirtualState::make_uptr()};
    print_value.operator()(virtual_state_epsilon);
    print_value.operator()<true>(virtual_state_epsilon);
    print_value.operator()<false, true>(virtual_state_epsilon);
    print_value.operator()<true, true>(virtual_state_epsilon);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualStateBase> virtual_state_epsilon{
        EpsilonVirtualState::make_uptr()};
    print_state(*virtual_state_epsilon);
    match_print(*virtual_state_epsilon, 0);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualStateBase> virtual_state_symbol{
        SymbolVirtualState::make_uptr(0)};
    print_state(*virtual_state_symbol);
    match_print(*virtual_state_symbol, 0);
    match_print(*virtual_state_symbol, 0);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualStateBase> virtual_state_kleene{
        KleeneVirtualState::make_uptr(SymbolState{0})};
    print_state(*virtual_state_kleene);
    match_print(*virtual_state_kleene, 0);
    match_print(*virtual_state_kleene, 0);
    match_print(*virtual_state_kleene, 1);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualStateBase> virtual_state_concat{
        ConcatVirtualState::make_uptr(SymbolState{0}, SymbolState{1})};
    print_state(*virtual_state_concat);
    match_print(*virtual_state_concat, 0);
    match_print(*virtual_state_concat, 1);
    match_print(*virtual_state_concat, 0);
  }
  cout << '\n';
  {
    std::unique_ptr<VirtualStateBase> virtual_state_union{
        UnionVirtualState::make_uptr(SymbolState{0}, SymbolState{1})};
    print_state(*virtual_state_union);
    match_print(*virtual_state_union, 0);
    match_print(*virtual_state_union, 0);
  }

  return 0;
}
