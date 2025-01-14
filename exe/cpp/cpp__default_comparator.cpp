#include <chrono>
#include <compare>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <typeindex>

#include "yao/def/warn.hpp"
YAO_WARN_OFF__PADDING

class Num {
  int _n;

public:
  Num(int n) : _n{n} {}
  friend auto operator<=>(Num lhs, Num rhs) = default;
};

class Erased;

class Base {
public:
  using Cmp1 = bool (*)(const Base &, const Base &);
  using Cmp2 = bool (*)(const Erased &, const Erased &);

  virtual std::strong_ordering operator<=>(const Base &rhs) const = 0;
  virtual Cmp1 get_cmp1() const = 0;
  virtual Cmp2 get_cmp2() const = 0;

  virtual ~Base() = default;
};

class Derived : public Base {
  Num _num;

public:
  using Cmp1 = typename Base::Cmp1;
  using Cmp2 = typename Base::Cmp2;

  Derived(Num num) : _num{num} {}
  std::strong_ordering operator<=>(const Base &rhs) const override {
    auto that = dynamic_cast<const Derived *>(&rhs);
    if (that == nullptr)
      return std::type_index{typeid(*this)} <=> std::type_index{typeid(rhs)};
    return _num <=> that->_num;
  }
  static bool cmp1(const Base &lhs, const Base &rhs) {
    auto lhs_derived = static_cast<const Derived *>(&lhs);
    auto rhs_derived = static_cast<const Derived *>(&rhs);
    return lhs_derived->_num < rhs_derived->_num;
  }
  Cmp1 get_cmp1() const override { return cmp1; }
  static bool cmp2(const Erased &lhs, const Erased &rhs);
  Cmp2 get_cmp2() const override { return cmp2; }
};

class Erased {
  std::unique_ptr<Base> _base;

public:
  struct Cmp1 {
    typename Base::Cmp1 sub_cmp;
    bool operator()(const Erased &lhs, const Erased &rhs) const {
      return sub_cmp(*lhs._base, *rhs._base);
    }
  };
  using Cmp2 = bool (*)(const Erased &, const Erased &);

  Erased(Num n) : _base(std::make_unique<Derived>(n)) {}
  std::strong_ordering operator<=>(const Erased &rhs) const {
    return *_base <=> *rhs._base;
  }
  Base *get() const { return _base.get(); }
  Cmp1 get_cmp1() const { return Cmp1{_base->get_cmp1()}; }
  Cmp2 get_cmp2() const { return _base->get_cmp2(); }
};

bool Derived::cmp2(const Erased &lhs, const Erased &rhs) {
  auto lhs_derived = static_cast<const Derived *>(lhs.get());
  auto rhs_derived = static_cast<const Derived *>(rhs.get());
  return lhs_derived->_num < rhs_derived->_num;
}

int main() {

  std::set<Erased> num_set;
  const std::size_t CNT_MAX = 1024 * 1024 * 4;

  std::uniform_int_distribution<int> uni_int;
  std::mt19937 gen;

  auto clk_bgn = std::chrono::high_resolution_clock::now();
  {
    for (std::size_t cnt = 0; cnt < CNT_MAX; cnt++)
      num_set.insert(Num{uni_int(gen)});
  }
  auto clk_end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> clk_dur{clk_end - clk_bgn};
  std::cout << "time: " << clk_dur.count() << "ms\n";
  std::cout << "size: " << num_set.size() << '\n';

  return 0;
}
