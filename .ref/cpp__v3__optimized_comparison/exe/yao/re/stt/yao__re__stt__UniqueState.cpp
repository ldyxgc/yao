#include <iostream>

#include "yao/prt/PrintValueArgs.hpp"
#include "yao/prt/print_value.hpp"
#include "yao/re/stt/ConcatState.hpp"
#include "yao/re/stt/ConcreteVirtualState.hpp"
#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/KleeneState.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UnionState.hpp"
#include "yao/re/stt/UniqueState.hpp"
#include "yao/re/stt/VirtualState.hpp"

int main() {

  using std::cout;
  using yao::prt::print_value;
  using yao::prt::PrintValueArgs;

  using Symbol = int;
  using UniqueState = yao::re::stt::UniqueState<Symbol>;

  using EpsilonState = yao::re::stt::EpsilonState<Symbol>;
  using SymbolState = yao::re::stt::SymbolState<Symbol>;
  using KleeneState = yao::re::stt::KleeneState<UniqueState>;
  using ConcatState = yao::re::stt::ConcatState<UniqueState, UniqueState>;
  using UnionState = yao::re::stt::UnionState<UniqueState, UniqueState>;

  using VirtualState = yao::re::stt::VirtualState<Symbol>;
  using yao::re::stt::ConcreteVirtualState;

  using EpsilonVirtualState = ConcreteVirtualState<EpsilonState>;
  using SymbolVirtualState = ConcreteVirtualState<SymbolState>;
  using KleeneVirtualState = ConcreteVirtualState<KleeneState>;
  using ConcatVirtualState = ConcreteVirtualState<ConcatState>;
  using UnionVirtualState = ConcreteVirtualState<UnionState>;

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
    std::unique_ptr<VirtualState> re_option_0_kleene_1_state =
        ConcatVirtualState::make_uptr(
            UniqueState(UnionVirtualState::make_uptr(
                UniqueState(EpsilonVirtualState::make_uptr()),
                UniqueState(SymbolVirtualState::make_uptr(0)))),
            UniqueState(KleeneVirtualState::make_uptr(
                UniqueState(SymbolVirtualState::make_uptr(1)))));

    print_value_n(re_option_0_kleene_1_state);
    print_value_n(re_option_0_kleene_1_state,
                  {.print_type_args = {.scope = true}});
    print_value_n(re_option_0_kleene_1_state,
                  {.print_type_args = {.tmpl_args = true}});
    print_value_n(re_option_0_kleene_1_state,
                  {.print_type_args = {.scope = true, .tmpl_args = true}});
    cout << '\n';

    print_state_n(*re_option_0_kleene_1_state);
    match_print_n(*re_option_0_kleene_1_state, 0);
    match_print_n(*re_option_0_kleene_1_state, 1);
    match_print_n(*re_option_0_kleene_1_state, 1);
    match_print_n(*re_option_0_kleene_1_state, 0);
  }

  {
    std::unique_ptr<VirtualState> re_option_0_kleene_1_state = nullptr;
    {
      std::unique_ptr<VirtualState> re_option_0_state = nullptr;
      {
        std::unique_ptr<VirtualState> re_epsilon_state =
            EpsilonVirtualState::make_uptr();
        std::unique_ptr<VirtualState> re_0_state =
            SymbolVirtualState::make_uptr(0);
        re_option_0_state = UnionVirtualState::make_uptr(
            std::move(re_epsilon_state), std::move(re_0_state));
      }
      std::unique_ptr<VirtualState> re_kleene_1_state = nullptr;
      {
        std::unique_ptr<VirtualState> symbol_1_state =
            SymbolVirtualState::make_uptr(1);
        re_kleene_1_state =
            KleeneVirtualState::make_uptr(std::move(symbol_1_state));
      }
      re_option_0_kleene_1_state = ConcatVirtualState::make_uptr(
          std::move(re_option_0_state), std::move(re_kleene_1_state));
    }

    print_value_n(re_option_0_kleene_1_state);
    print_value_n(re_option_0_kleene_1_state,
                  {.print_type_args = {.scope = true}});
    print_value_n(re_option_0_kleene_1_state,
                  {.print_type_args = {.tmpl_args = true}});
    print_value_n(re_option_0_kleene_1_state,
                  {.print_type_args = {.scope = true, .tmpl_args = true}});
    cout << '\n';

    print_state_n(*re_option_0_kleene_1_state);
    match_print_n(*re_option_0_kleene_1_state, 0);
    match_print_n(*re_option_0_kleene_1_state, 1);
    match_print_n(*re_option_0_kleene_1_state, 1);
    match_print_n(*re_option_0_kleene_1_state, 0);
  }

  return 0;
}
