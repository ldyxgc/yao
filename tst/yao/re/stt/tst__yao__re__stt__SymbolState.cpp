#include "yao/re/stt/SymbolState.hpp"

#include "yao/def/check.hpp"

class Int {
public:
  Int(int i) : _i{i} {}
  Int(const Int &) = default;
  Int(Int &&) = delete;
  operator int() const { return _i; }

private:
  int _i;
};

class Uint {
public:
  Uint(unsigned u) : _u{u} {}
  Uint(const Uint &) = delete;
  Uint(Uint &&) = default;
  operator unsigned() const { return _u; }

private:
  unsigned _u;
};

int main() {

  using yao::re::stt::SymbolState;

  {
    Int i{0};
    SymbolState symbol_state{i};
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == false);

    symbol_state.match(0);
    YAO_CHECK(symbol_state.is_final() == true);
    YAO_CHECK(symbol_state.is_dead() == false);

    symbol_state.match(0);
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == true);
  }

  {
    SymbolState symbol_state{Uint{0}};
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == false);

    symbol_state.match(1);
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == true);

    symbol_state.match(0);
    YAO_CHECK(symbol_state.is_final() == false);
    YAO_CHECK(symbol_state.is_dead() == true);
  }

  return 0;
}
