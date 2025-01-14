#include <chrono>
#include <iostream>
#include <ratio>

#include "yao/re/stt/ConcatState.hpp"
#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/ErasedState.hpp"
#include "yao/re/stt/KleeneState.hpp"
#include "yao/re/stt/SymbolState.hpp"

int main() {

  using ErasedState = yao::re::stt::ErasedState<int>;
  const std::size_t CNT_MAX = 1024 * 32;
  const int NUM_MAX = 10;

  using EpsilonState = yao::re::stt::EpsilonState<int>;
  using SymbolState = yao::re::stt::SymbolState<int>;
  using KleeneErasedState =
      yao::re::stt::KleeneState<ErasedState, ErasedState::CmpLess2>;
  using ConcatErasedState = yao::re::stt::ConcatState<ErasedState, ErasedState,
                                                      ErasedState::CmpLess2>;

  ErasedState re = EpsilonState{};
  for (int i = 0; i <= NUM_MAX; i++) {
    auto erased_symbol_state = ErasedState{SymbolState{i}};
    re = ConcatErasedState{
        re, KleeneErasedState{
                erased_symbol_state,
                erased_symbol_state.get_cmp_less2_assume_same_known_type()}};
  }
  re = ConcatErasedState{re, re, re.get_cmp_less2_assume_same_known_type()};

  auto clk_bgn = std::chrono::high_resolution_clock::now();
  {
    for (int i = 0; i <= NUM_MAX; i++)
      for (std::size_t cnt = 0; cnt < CNT_MAX; cnt++)
        re.match(i);
    for (int i = 0; i <= NUM_MAX; i++)
      for (std::size_t cnt = 0; cnt < CNT_MAX; cnt++)
        re.match(i);
  }
  auto clk_end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> clk_dur{clk_end - clk_bgn};
  std::cout << "time: " << clk_dur.count() << "ms\n";
  std::cout << "is_final: " << re.is_final() << '\n';

  return 0;
}
