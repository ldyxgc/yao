#include <chrono>
#include <iostream>
#include <ratio>

#include "yao/re/stt/ConcatState.hpp"
#include "yao/re/stt/ConcreteVirtualState.hpp"
#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/KleeneState.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UniqueState.hpp"

int main() {

  const std::size_t CNT_MAX = 1024 * 32;
  const int NUM_MAX = 10;

  using Symbol = int;
  using UniqueState = yao::re::stt::UniqueState<Symbol>;

  using EpsilonState = yao::re::stt::EpsilonState<Symbol>;
  using SymbolState = yao::re::stt::SymbolState<Symbol>;
  using KleeneState = yao::re::stt::KleeneState<UniqueState>;
  using ConcatState = yao::re::stt::ConcatState<UniqueState, UniqueState>;

  using VirtualState = yao::re::stt::VirtualState<Symbol>;
  using yao::re::stt::ConcreteVirtualState;

  using EpsilonVirtualState = ConcreteVirtualState<EpsilonState>;
  using SymbolVirtualState = ConcreteVirtualState<SymbolState>;
  using KleeneVirtualState = ConcreteVirtualState<KleeneState>;
  using ConcatVirtualState = ConcreteVirtualState<ConcatState>;

  std::unique_ptr<VirtualState> re = EpsilonVirtualState::make_uptr();
  for (int i = 0; i <= NUM_MAX; i++)
    re = ConcatVirtualState::make_uptr(
        re->copy_uptr(), UniqueState(KleeneVirtualState::make_uptr(
                             UniqueState(SymbolVirtualState::make_uptr(i)))));
  re = ConcatVirtualState::make_uptr(re->copy_uptr(), re->copy_uptr());

  auto clk_bgn = std::chrono::high_resolution_clock::now();
  {
    for (int i = 0; i <= NUM_MAX; i++)
      for (std::size_t cnt = 0; cnt < CNT_MAX; cnt++)
        re->match(i);
    for (int i = 0; i <= NUM_MAX; i++)
      for (std::size_t cnt = 0; cnt < CNT_MAX; cnt++)
        re->match(i);
  }
  auto clk_end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> clk_dur{clk_end - clk_bgn};
  std::cout << "time: " << clk_dur.count() << "ms\n";
  std::cout << "is_final: " << re->is_final() << '\n';

  return 0;
}
