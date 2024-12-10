#ifndef __YAO__RE__STT__C_O_STATE__HPP__
#define __YAO__RE__STT__C_O_STATE__HPP__

#include <type_traits>

#include "yao/re/stt/StateBase.hpp"

namespace yao::re::stt {

// c: concept, o: object
template <typename State>
concept c_o_State = std::is_base_of_v<StateBase<State>, State> &&
                    (!std::is_convertible_v<const volatile State *,
                                            const volatile StateBase<State> *>);

} // namespace yao::re::stt

#endif
