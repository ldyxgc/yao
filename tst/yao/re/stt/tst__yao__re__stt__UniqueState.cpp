#include <utility>

#include "yao/def/check.hpp"
#include "yao/re/stt/ConcatState.hpp"
#include "yao/re/stt/ConcreteVirtualState.hpp"
#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/KleeneState.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UnionState.hpp"
#include "yao/re/stt/UniqueState.hpp"
#include "yao/re/stt/VirtualState.hpp"

int main() {

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

  {
    std::unique_ptr<VirtualState> re_option_0_kleene_1_state =
        ConcatVirtualState::make_uptr(
            UniqueState(UnionVirtualState::make_uptr(
                UniqueState(EpsilonVirtualState::make_uptr()),
                UniqueState(SymbolVirtualState::make_uptr(0)))),
            UniqueState(KleeneVirtualState::make_uptr(
                UniqueState(SymbolVirtualState::make_uptr(1)))));
    YAO_CHECK(re_option_0_kleene_1_state->is_final() == true);
    YAO_CHECK(re_option_0_kleene_1_state->is_dead() == false);

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(2);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }
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
    YAO_CHECK(re_option_0_kleene_1_state->is_final() == true);
    YAO_CHECK(re_option_0_kleene_1_state->is_dead() == false);

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(2);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }

    {
      std::unique_ptr<VirtualState> re_state =
          re_option_0_kleene_1_state->copy_uptr();
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(1);
      YAO_CHECK(re_state->is_final() == true);
      YAO_CHECK(re_state->is_dead() == false);

      re_state->match(0);
      YAO_CHECK(re_state->is_final() == false);
      YAO_CHECK(re_state->is_dead() == true);
    }
  }

  {
    std::unique_ptr<VirtualState> re_option_0_kleene_1_state_1 =
        ConcatVirtualState::make_uptr(
            UniqueState(UnionVirtualState::make_uptr(
                UniqueState(EpsilonVirtualState::make_uptr()),
                UniqueState(SymbolVirtualState::make_uptr(0)))),
            UniqueState(KleeneVirtualState::make_uptr(
                UniqueState(SymbolVirtualState::make_uptr(1)))));

    std::unique_ptr<VirtualState> re_option_0_kleene_1_state_2 = nullptr;
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
      re_option_0_kleene_1_state_2 = ConcatVirtualState::make_uptr(
          std::move(re_option_0_state), std::move(re_kleene_1_state));
    }

    YAO_CHECK(*re_option_0_kleene_1_state_1 == *re_option_0_kleene_1_state_2);
  }

  return 0;
}
