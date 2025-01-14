#include <concepts>
#include <memory>
#include <typeindex>

#include "yao/com.hpp"
#include "yao/def/check.hpp"
#include "yao/re/stt/ConcatState.hpp"
#include "yao/re/stt/ConcreteVirtualState.hpp"
#include "yao/re/stt/EpsilonState.hpp"
#include "yao/re/stt/KleeneState.hpp"
#include "yao/re/stt/SymbolState.hpp"
#include "yao/re/stt/UnionState.hpp"
#include "yao/re/stt/VirtualState.hpp"

int main() {

  using yao::not_null;
  using yao::owner;

  using EpsilonState = yao::re::stt::EpsilonState<int>;
  using SymbolState = yao::re::stt::SymbolState<int>;
  using KleeneState = yao::re::stt::KleeneState<SymbolState>;
  using ConcatState = yao::re::stt::ConcatState<SymbolState, SymbolState>;
  using UnionState = yao::re::stt::UnionState<SymbolState, SymbolState>;

  using VirtualState = yao::re::stt::VirtualState<int>;
  using yao::re::stt::ConcreteVirtualState;

  using EpsilonVirtualState = ConcreteVirtualState<EpsilonState>;
  using SymbolVirtualState = ConcreteVirtualState<SymbolState>;
  using KleeneVirtualState = ConcreteVirtualState<KleeneState>;
  using ConcatVirtualState = ConcreteVirtualState<ConcatState>;
  using UnionVirtualState = ConcreteVirtualState<UnionState>;

  {
    {
      not_null<owner<EpsilonVirtualState *>> epsilon_virtual_state{
          new EpsilonVirtualState{}};
      YAO_CHECK(epsilon_virtual_state->is_final() == true);
      YAO_CHECK(epsilon_virtual_state->is_dead() == false);
      epsilon_virtual_state->match(0);
      YAO_CHECK(epsilon_virtual_state->is_final() == false);
      YAO_CHECK(epsilon_virtual_state->is_dead() == true);

      auto copied_virtual_state{epsilon_virtual_state->copy_rptr()};
      YAO_CHECK(std::same_as<decltype(copied_virtual_state),
                             decltype(epsilon_virtual_state)>);

      delete epsilon_virtual_state;
      delete copied_virtual_state;
    }
    {
      not_null<owner<VirtualState *>> virtual_state_epsilon{
          new EpsilonVirtualState{}};
      YAO_CHECK(virtual_state_epsilon->is_final() == true);
      YAO_CHECK(virtual_state_epsilon->is_dead() == false);
      virtual_state_epsilon->match(1);
      YAO_CHECK(virtual_state_epsilon->is_final() == false);
      YAO_CHECK(virtual_state_epsilon->is_dead() == true);

      auto copied_virtual_state{virtual_state_epsilon->copy_rptr()};
      YAO_CHECK(std::same_as<decltype(copied_virtual_state),
                             decltype(virtual_state_epsilon)>);

      delete virtual_state_epsilon;
      delete copied_virtual_state;
    }
  }

  {
    {
      not_null<owner<SymbolVirtualState *>> symbol_virtual_state{
          SymbolVirtualState::make_rptr(0)};
      YAO_CHECK(symbol_virtual_state->is_final() == false);
      YAO_CHECK(symbol_virtual_state->is_dead() == false);
      symbol_virtual_state->match(1);
      YAO_CHECK(symbol_virtual_state->is_final() == false);
      YAO_CHECK(symbol_virtual_state->is_dead() == true);

      auto copied_virtual_state{symbol_virtual_state->copy_rptr()};
      YAO_CHECK(std::same_as<decltype(copied_virtual_state),
                             decltype(symbol_virtual_state)>);

      delete symbol_virtual_state;
      delete copied_virtual_state;
    }
    {
      not_null<owner<VirtualState *>> virtual_state_symbol{
          SymbolVirtualState::make_rptr(0)};
      YAO_CHECK(virtual_state_symbol->is_final() == false);
      YAO_CHECK(virtual_state_symbol->is_dead() == false);
      virtual_state_symbol->match(0);
      YAO_CHECK(virtual_state_symbol->is_final() == true);
      YAO_CHECK(virtual_state_symbol->is_dead() == false);
      virtual_state_symbol->match(0);
      YAO_CHECK(virtual_state_symbol->is_final() == false);
      YAO_CHECK(virtual_state_symbol->is_dead() == true);

      auto copied_virtual_state{virtual_state_symbol->copy_rptr()};
      YAO_CHECK(std::same_as<decltype(copied_virtual_state),
                             decltype(virtual_state_symbol)>);

      delete virtual_state_symbol;
      delete copied_virtual_state;
    }
  }

  {
    {
      not_null<std::unique_ptr<KleeneVirtualState>> kleene_virtual_state{
          new KleeneVirtualState{SymbolState{0}}};
      YAO_CHECK(kleene_virtual_state->is_final() == true);
      YAO_CHECK(kleene_virtual_state->is_dead() == false);
      kleene_virtual_state->match(1);
      YAO_CHECK(kleene_virtual_state->is_final() == false);
      YAO_CHECK(kleene_virtual_state->is_dead() == true);

      auto copied_virtual_state{kleene_virtual_state->copy_uptr()};
      YAO_CHECK(std::same_as<decltype(copied_virtual_state),
                             decltype(kleene_virtual_state)>);
    }
    {
      not_null<std::unique_ptr<VirtualState>> virtual_state_kleene{
          new KleeneVirtualState{SymbolState{0}}};
      YAO_CHECK(virtual_state_kleene->is_final() == true);
      YAO_CHECK(virtual_state_kleene->is_dead() == false);
      virtual_state_kleene->match(0);
      YAO_CHECK(virtual_state_kleene->is_final() == true);
      YAO_CHECK(virtual_state_kleene->is_dead() == false);
      virtual_state_kleene->match(0);
      YAO_CHECK(virtual_state_kleene->is_final() == true);
      YAO_CHECK(virtual_state_kleene->is_dead() == false);
      virtual_state_kleene->match(1);
      YAO_CHECK(virtual_state_kleene->is_final() == false);
      YAO_CHECK(virtual_state_kleene->is_dead() == true);

      auto copied_virtual_state{virtual_state_kleene->copy_uptr()};
      YAO_CHECK(std::same_as<decltype(copied_virtual_state),
                             decltype(virtual_state_kleene)>);
    }
  }

  {
    {
      not_null<std::unique_ptr<ConcatVirtualState>> concat_virtual_state{
          std::make_unique<ConcatVirtualState>(SymbolState{0}, SymbolState{1})};
      YAO_CHECK(concat_virtual_state->is_final() == false);
      YAO_CHECK(concat_virtual_state->is_dead() == false);
      concat_virtual_state->match(1);
      YAO_CHECK(concat_virtual_state->is_final() == false);
      YAO_CHECK(concat_virtual_state->is_dead() == true);

      auto copied_virtual_state{concat_virtual_state->copy_uptr()};
      YAO_CHECK(std::same_as<decltype(copied_virtual_state),
                             decltype(concat_virtual_state)>);
    }
    {
      not_null<std::unique_ptr<VirtualState>> virtual_state_concat{
          std::make_unique<ConcatVirtualState>(SymbolState{0}, SymbolState{1})};
      YAO_CHECK(virtual_state_concat->is_final() == false);
      YAO_CHECK(virtual_state_concat->is_dead() == false);
      virtual_state_concat->match(0);
      YAO_CHECK(virtual_state_concat->is_final() == false);
      YAO_CHECK(virtual_state_concat->is_dead() == false);
      virtual_state_concat->match(1);
      YAO_CHECK(virtual_state_concat->is_final() == true);
      YAO_CHECK(virtual_state_concat->is_dead() == false);
      virtual_state_concat->match(0);
      YAO_CHECK(virtual_state_concat->is_final() == false);
      YAO_CHECK(virtual_state_concat->is_dead() == true);

      auto copied_virtual_state{virtual_state_concat->copy_uptr()};
      YAO_CHECK(std::same_as<decltype(copied_virtual_state),
                             decltype(virtual_state_concat)>);
    }
  }

  {
    {
      not_null<std::unique_ptr<UnionVirtualState>> union_virtual_state{
          UnionVirtualState::make_rptr(SymbolState{0}, SymbolState{1})};
      YAO_CHECK(union_virtual_state->is_final() == false);
      YAO_CHECK(union_virtual_state->is_dead() == false);
      union_virtual_state->match(2);
      YAO_CHECK(union_virtual_state->is_final() == false);
      YAO_CHECK(union_virtual_state->is_dead() == true);

      auto copied_virtual_state{union_virtual_state->copy_uptr()};
      YAO_CHECK(std::same_as<decltype(copied_virtual_state),
                             decltype(union_virtual_state)>);
    }
    {
      not_null<std::unique_ptr<VirtualState>> virtual_state_union{
          UnionVirtualState::make_rptr(SymbolState{0}, SymbolState{1})};
      YAO_CHECK(virtual_state_union->is_final() == false);
      YAO_CHECK(virtual_state_union->is_dead() == false);
      virtual_state_union->match(0);
      YAO_CHECK(virtual_state_union->is_final() == true);
      YAO_CHECK(virtual_state_union->is_dead() == false);
      virtual_state_union->match(0);
      YAO_CHECK(virtual_state_union->is_final() == false);
      YAO_CHECK(virtual_state_union->is_dead() == true);

      auto copied_virtual_state{virtual_state_union->copy_uptr()};
      YAO_CHECK(std::same_as<decltype(copied_virtual_state),
                             decltype(virtual_state_union)>);
    }
  }

  {
    EpsilonVirtualState epsilon_virtual_state{};
    SymbolVirtualState symbol_virtual_state_0{0};
    SymbolVirtualState symbol_virtual_state_1{1};
    KleeneVirtualState kleene_virtual_state_0{SymbolState{0}};
    KleeneVirtualState kleene_virtual_state_1{SymbolState{1}};
    ConcatVirtualState concat_virtual_state_00{SymbolState{0}, SymbolState{0}};
    ConcatVirtualState concat_virtual_state_01{SymbolState{0}, SymbolState{1}};
    UnionVirtualState union_virtual_state_00{SymbolState{0}, SymbolState{0}};
    UnionVirtualState union_virtual_state_01{SymbolState{0}, SymbolState{1}};

    YAO_CHECK((epsilon_virtual_state <=> symbol_virtual_state_0) ==
              (std::type_index{typeid(EpsilonState)} <=>
               std::type_index{typeid(SymbolState)}));
    YAO_CHECK(symbol_virtual_state_0 < symbol_virtual_state_1);
    YAO_CHECK((symbol_virtual_state_1 <=> kleene_virtual_state_0) ==
              (std::type_index{typeid(SymbolState)} <=>
               std::type_index{typeid(KleeneState)}));
    YAO_CHECK(kleene_virtual_state_0 < kleene_virtual_state_1);
    YAO_CHECK((kleene_virtual_state_1 <=> concat_virtual_state_00) ==
              (std::type_index{typeid(KleeneState)} <=>
               std::type_index{typeid(ConcatState)}));
    YAO_CHECK(concat_virtual_state_00 < concat_virtual_state_01);
    YAO_CHECK((concat_virtual_state_01 <=> union_virtual_state_00) ==
              (std::type_index{typeid(ConcatState)} <=>
               std::type_index{typeid(UnionState)}));
    YAO_CHECK(union_virtual_state_00 < union_virtual_state_01);

    VirtualState &virtual_state_epsilon = epsilon_virtual_state;
    VirtualState &virtual_state_symbol_0 = symbol_virtual_state_0;
    VirtualState &virtual_state_symbol_1 = symbol_virtual_state_1;
    VirtualState &virtual_state_kleene_0 = kleene_virtual_state_0;
    VirtualState &virtual_state_kleene_1 = kleene_virtual_state_1;
    VirtualState &virtual_state_concat_00 = concat_virtual_state_00;
    VirtualState &virtual_state_concat_01 = concat_virtual_state_01;
    VirtualState &virtual_state_union_00 = union_virtual_state_00;
    VirtualState &virtual_state_union_01 = union_virtual_state_01;

    YAO_CHECK((virtual_state_epsilon <=> virtual_state_symbol_0) ==
              (std::type_index{typeid(EpsilonState)} <=>
               std::type_index{typeid(SymbolState)}));
    YAO_CHECK(virtual_state_symbol_0 < virtual_state_symbol_1);
    YAO_CHECK((virtual_state_symbol_1 <=> virtual_state_kleene_0) ==
              (std::type_index{typeid(SymbolState)} <=>
               std::type_index{typeid(KleeneState)}));
    YAO_CHECK(virtual_state_kleene_0 < virtual_state_kleene_1);
    YAO_CHECK((virtual_state_kleene_1 <=> virtual_state_concat_00) ==
              (std::type_index{typeid(KleeneState)} <=>
               std::type_index{typeid(ConcatState)}));
    YAO_CHECK(virtual_state_concat_00 < virtual_state_concat_01);
    YAO_CHECK((virtual_state_concat_01 <=> virtual_state_union_00) ==
              (std::type_index{typeid(ConcatState)} <=>
               std::type_index{typeid(UnionState)}));
    YAO_CHECK(virtual_state_union_00 < virtual_state_union_01);
  }

  return 0;
}
