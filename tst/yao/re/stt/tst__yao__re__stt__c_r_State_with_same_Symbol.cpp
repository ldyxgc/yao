#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/c_r_State_with_same_Symbol.hpp"

using yao::re::stt::c_r_State_with_same_Symbol;
using yao::re::stt::EpsilonState;
using yao::re::stt::SymbolState;

static_assert(c_r_State_with_same_Symbol<char, char> == false);
static_assert(c_r_State_with_same_Symbol<char, int> == false);

static_assert(c_r_State_with_same_Symbol<char, EpsilonState<char>> == false);
static_assert(c_r_State_with_same_Symbol<EpsilonState<char>, char> == false);

static_assert(
    c_r_State_with_same_Symbol<EpsilonState<char>, EpsilonState<int>> == false);
static_assert(
    c_r_State_with_same_Symbol<EpsilonState<char>, SymbolState<int>> == false);

static_assert(
    c_r_State_with_same_Symbol<EpsilonState<char>, EpsilonState<char>> == true);
static_assert(
    c_r_State_with_same_Symbol<EpsilonState<char>, SymbolState<char>> == true);

int main() { return 0; }
