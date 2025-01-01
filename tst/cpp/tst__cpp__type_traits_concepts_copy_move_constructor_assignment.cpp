#include <concepts>
#include <type_traits>

// std::is_copy_constructible_v
struct A {
  A(const A &) = default;
  A(A &&) = delete;
  A &operator=(const A &) = delete;
  A &operator=(A &&) = delete;
};
static_assert(std::is_copy_constructible_v<A>);  // std::is_copy_constructible_v
static_assert(!std::is_move_constructible_v<A>); //
static_assert(!std::is_copy_assignable_v<A>);    //
static_assert(!std::is_move_assignable_v<A>);    //
static_assert(!std::move_constructible<A>);      //
static_assert(!std::copy_constructible<A>);      //
static_assert(!std::movable<A>);                 //
static_assert(!std::copyable<A>);                //

// std::is_move_constructible_v
struct B {
  B(const B &) = delete;
  B(B &&) = default;
  B &operator=(const B &) = delete;
  B &operator=(B &&) = delete;
};
static_assert(!std::is_copy_constructible_v<B>); //
static_assert(std::is_move_constructible_v<B>);  // std::is_move_constructible_v
static_assert(!std::is_copy_assignable_v<B>);    //
static_assert(!std::is_move_assignable_v<B>);    //
static_assert(std::move_constructible<B>);       // std::move_constructible
static_assert(!std::copy_constructible<B>);      //
static_assert(!std::movable<B>);                 //
static_assert(!std::copyable<B>);                //

// std::is_copy_assignable_v
struct C {
  C(const C &) = delete;
  C(C &&) = delete;
  C &operator=(const C &) = default;
  C &operator=(C &&) = delete;
};
static_assert(!std::is_copy_constructible_v<C>); //
static_assert(!std::is_move_constructible_v<C>); //
static_assert(std::is_copy_assignable_v<C>);     // std::is_copy_assignable_v
static_assert(!std::is_move_assignable_v<C>);    //
static_assert(!std::move_constructible<C>);      //
static_assert(!std::copy_constructible<C>);      //
static_assert(!std::movable<C>);                 //
static_assert(!std::copyable<C>);                //

// std::is_move_assignable_v
struct D {
  D(const D &) = delete;
  D(D &&) = delete;
  D &operator=(const D &) = delete;
  D &operator=(D &&) = default;
};
static_assert(!std::is_copy_constructible_v<D>); //
static_assert(!std::is_move_constructible_v<D>); //
static_assert(!std::is_copy_assignable_v<D>);    //
static_assert(std::is_move_assignable_v<D>);     // std::is_move_assignable_v
static_assert(!std::move_constructible<D>);      //
static_assert(!std::copy_constructible<D>);      //
static_assert(!std::movable<D>);                 //
static_assert(!std::copyable<D>);                //

// std::move_constructible
struct E {
  E(const E &) = delete;
  E(E &&) = default;
  E &operator=(const E &) = delete;
  E &operator=(E &&) = delete;
};
static_assert(!std::is_copy_constructible_v<E>); //
static_assert(std::is_move_constructible_v<E>);  // std::is_move_constructible_v
static_assert(!std::is_copy_assignable_v<E>);    //
static_assert(!std::is_move_assignable_v<E>);    //
static_assert(std::move_constructible<E>);       // std::move_constructible
static_assert(!std::copy_constructible<E>);      //
static_assert(!std::movable<E>);                 //
static_assert(!std::copyable<E>);                //

// std::copy_constructible
struct F {
  F(const F &) = default;
  F(F &&) = default;
  F &operator=(const F &) = delete;
  F &operator=(F &&) = delete;
};
static_assert(std::is_copy_constructible_v<F>); // std::is_copy_constructible_v
static_assert(std::is_move_constructible_v<F>); // std::is_move_constructible_v
static_assert(!std::is_copy_assignable_v<F>);   //
static_assert(!std::is_move_assignable_v<F>);   //
static_assert(std::move_constructible<F>);      // std::move_constructible
static_assert(std::copy_constructible<F>);      // std::copy_constructible
static_assert(!std::movable<F>);                //
static_assert(!std::copyable<F>);               //

// std::movable
struct G {
  G(const G &) = delete;
  G(G &&) = default;
  G &operator=(const G &) = delete;
  G &operator=(G &&) = default;
};
static_assert(!std::is_copy_constructible_v<G>); //
static_assert(std::is_move_constructible_v<G>);  // std::is_move_constructible_v
static_assert(!std::is_copy_assignable_v<G>);    //
static_assert(std::is_move_assignable_v<G>);     // std::is_move_assignable_v
static_assert(std::move_constructible<G>);       // std::move_constructible
static_assert(!std::copy_constructible<G>);      //
static_assert(std::movable<G>);                  // std::movable
static_assert(!std::copyable<G>);                //

// std::copyable
struct H {
  H(const H &) = default;
  H(H &&) = default;
  H &operator=(const H &) = default;
  H &operator=(H &&) = default;
};
static_assert(std::is_copy_constructible_v<H>); // std::is_copy_constructible_v
static_assert(std::is_move_constructible_v<H>); // std::is_move_constructible_v
static_assert(std::is_copy_assignable_v<H>);    // std::is_copy_assignable_v
static_assert(std::is_move_assignable_v<H>);    // std::is_move_assignable_v
static_assert(std::move_constructible<H>);      // std::move_constructible
static_assert(std::copy_constructible<H>);      // std::copy_constructible
static_assert(std::movable<H>);                 // std::movable
static_assert(std::copyable<H>);                // std::copyable

int main() { return 0; }
