#include <concepts>
#include <utility>

enum class Type {
  I,    // int
  IR,   // int &
  IRR,  // int &&
  CI,   // const int
  CIR,  // const int &
  CIRR, // const int &&
};

template <typename T> constexpr Type type() {
  if constexpr (std::same_as<T, int>)
    return Type::I;
  else if constexpr (std::same_as<T, int &>)
    return Type::IR;
  else if constexpr (std::same_as<T, int &&>)
    return Type::IRR;
  else if constexpr (std::same_as<T, const int>)
    return Type::CI;
  else if constexpr (std::same_as<T, const int &>)
    return Type::CIR;
  else if constexpr (std::same_as<T, const int &&>)
    return Type::CIRR;
  else
    static_assert([]() { return false; }());
}

// -----------------------------------------------------------------------------

static int i{};
const int ci{};

// -----------------------------------------------------------------------------

template <typename T> constexpr std::pair<Type, Type> fun(T &&t) {
  return {type<T>(), type<decltype(t)>()};
}

static_assert(fun(0) == std::pair{Type::I, Type::IRR});

static_assert(fun(i) == std::pair{Type::IR, Type::IR});
static_assert(fun(std::move(i)) == std::pair{Type::I, Type::IRR});

static_assert(fun(ci) == std::pair{Type::CIR, Type::CIR});
static_assert(fun(std::move(ci)) == std::pair{Type::CI, Type::CIRR});

// -----------------------------------------------------------------------------

template <typename T> struct Obj {
  Type _T, _U, _V;

  template <typename U>
  constexpr Obj(U &&v)
      : _T{type<T>()}, _U{type<U>()}, _V{type<decltype(v)>()} {}
};

template <typename U> Obj(U &&v) -> Obj<U>;

static_assert(Obj{0}._T == Type::I);
static_assert(Obj{0}._U == Type::I);
static_assert(Obj{0}._V == Type::IRR);

static_assert(Obj{i}._T == Type::IR);
static_assert(Obj{i}._U == Type::IR);
static_assert(Obj{i}._V == Type::IR);

static_assert(Obj{std::move(i)}._T == Type::I);
static_assert(Obj{std::move(i)}._U == Type::I);
static_assert(Obj{std::move(i)}._V == Type::IRR);

static_assert(Obj{ci}._T == Type::CIR);
static_assert(Obj{ci}._U == Type::CIR);
static_assert(Obj{ci}._V == Type::CIR);

static_assert(Obj{std::move(ci)}._T == Type::CI);
static_assert(Obj{std::move(ci)}._U == Type::CI);
static_assert(Obj{std::move(ci)}._V == Type::CIRR);

// -----------------------------------------------------------------------------

int main() { return 0; }
