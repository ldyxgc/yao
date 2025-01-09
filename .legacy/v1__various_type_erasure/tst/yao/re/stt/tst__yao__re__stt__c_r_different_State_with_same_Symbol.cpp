#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/c_r_different_State_with_same_Symbol.hpp"

using yao::re::stt::c_r_different_State_with_same_Symbol;
using yao::re::stt::EpsilonState;
using yao::re::stt::SymbolState;

static_assert(!c_r_different_State_with_same_Symbol<long, long>);
static_assert(!c_r_different_State_with_same_Symbol<char, long>);

static_assert(!c_r_different_State_with_same_Symbol<long, EpsilonState<long>>);
static_assert(!c_r_different_State_with_same_Symbol<EpsilonState<long>, long>);

static_assert(!c_r_different_State_with_same_Symbol<EpsilonState<char>,
                                                    EpsilonState<long>>);
static_assert(!c_r_different_State_with_same_Symbol<EpsilonState<char>,
                                                    SymbolState<long>>);

static_assert(!c_r_different_State_with_same_Symbol<EpsilonState<long>,
                                                    EpsilonState<long>>);
static_assert(c_r_different_State_with_same_Symbol<EpsilonState<long>,
                                                   SymbolState<long>>);

int main() { return 0; }
