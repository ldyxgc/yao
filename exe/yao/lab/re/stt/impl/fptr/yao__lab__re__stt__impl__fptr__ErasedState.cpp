#include <chrono>
#include <iostream>
#include <ratio>

#include "yao/lab/re/stt/ConcatState.hpp"
#include "yao/lab/re/stt/EpsilonState.hpp"
#include "yao/lab/re/stt/KleeneState.hpp"
#include "yao/lab/re/stt/SymbolState.hpp"
#include "yao/lab/re/stt/impl/fptr/ErasedState.hpp"

int main() {

  using ErasedState = yao::lab::re::stt::impl::fptr::ErasedState<int>;
  const std::size_t CNT_MAX = 1024 * 32;
  const int NUM_MAX = 10;

  using EpsilonState = yao::lab::re::stt::EpsilonState<int>;
  using SymbolState = yao::lab::re::stt::SymbolState<int>;
  using KleeneErasedState = yao::lab::re::stt::KleeneState<ErasedState>;
  using ConcatErasedState =
      yao::lab::re::stt::ConcatState<ErasedState, ErasedState>;

  ErasedState re = EpsilonState{};
  for (int i = 0; i <= NUM_MAX; i++)
    re = ConcatErasedState{re, KleeneErasedState{SymbolState{i}}};

  auto clk_bgn = std::chrono::high_resolution_clock::now();
  {
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
