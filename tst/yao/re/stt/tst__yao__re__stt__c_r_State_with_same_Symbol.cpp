#include "yao/def/check.hpp"
#include "yao/re/stt/ErasedState.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/c_r_State_with_same_Symbol.hpp"

int main() {

  using yao::re::stt::c_r_State_with_same_Symbol;
  using yao::re::stt::ErasedState;
  using yao::re::stt::SymbolState;

  YAO_CHECK(c_r_State_with_same_Symbol<char, char> == false);
  YAO_CHECK(c_r_State_with_same_Symbol<char, long> == false);

  YAO_CHECK(c_r_State_with_same_Symbol<char, ErasedState<char>> == false);
  YAO_CHECK(c_r_State_with_same_Symbol<ErasedState<char>, char> == false);

  YAO_CHECK(c_r_State_with_same_Symbol<ErasedState<char>, ErasedState<long>> ==
            false);
  YAO_CHECK(c_r_State_with_same_Symbol<ErasedState<char>, SymbolState<long>> ==
            false);

  YAO_CHECK(c_r_State_with_same_Symbol<ErasedState<char>, ErasedState<char>> ==
            true);
  YAO_CHECK(c_r_State_with_same_Symbol<ErasedState<char>, SymbolState<char>> ==
            true);

  return 0;
}
