#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <ratio>
#include <sstream>

#include "yao/prt/impl/tmpl/print_format.hpp"

int main() {

  using yao::prt::impl::tmpl::print_format;
  const std::size_t CNT_MAX = 1024 * 1024 * 4;

  std::ostringstream oss;
  auto f = [&](auto fmt, auto... args) { print_format(oss, fmt, args...); };
  auto funcs = std::to_array<std::function<void(int)>>({
      [&](int i) { f("%i", i); },
      [&](int i) { f("%i%i", i, i); },
      [&](int i) { f("%i%i%i", i, i, i); },
      [&](int i) { f("%i%i%i%i", i, i, i, i); },
      [&](int i) { f("%i%i%i%i%i", i, i, i, i, i); },
      [&](int i) { f("%i%i%i%i%i%i", i, i, i, i, i, i); },
      [&](int i) { f("%i%i%i%i%i%i%i", i, i, i, i, i, i, i); },
      [&](int i) { f("%i%i%i%i%i%i%i%i", i, i, i, i, i, i, i, i); },
      [&](int i) { f("%i%i%i%i%i%i%i%i%i", i, i, i, i, i, i, i, i, i); },
      [&](int i) { f("%i%i%i%i%i%i%i%i%i%i", i, i, i, i, i, i, i, i, i, i); },
  });

  std::uniform_int_distribution<std::size_t> uni_idx{0, funcs.size() - 1};
  std::uniform_int_distribution<int> uni_int;
  std::mt19937 gen;

  auto clk_bgn = std::chrono::high_resolution_clock::now();
  {
    for (std::size_t cnt = 0; cnt < CNT_MAX; cnt++)
      funcs[uni_idx(gen)](uni_int(gen));
  }
  auto clk_end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> clk_dur{clk_end - clk_bgn};
  std::cout << "size: " << oss.str().size() << std::endl;
  std::cout << "time: " << clk_dur.count() << "ms\n";

  return 0;
}
