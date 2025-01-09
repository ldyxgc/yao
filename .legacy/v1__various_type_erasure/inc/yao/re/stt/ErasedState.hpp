#ifndef __YAO__RE__STT__ERASED_STATE__HPP__
#define __YAO__RE__STT__ERASED_STATE__HPP__

#include "yao/config.hpp"

#if YAO_CONFIG__RE_ERASED_STATE == YAO_CONFIG__RE_ERASED_STATE__VIRTUAL_FUNCTION

#include "yao/re/stt/impl/vfun/ErasedState.hpp"

namespace yao::re::stt {

using impl::vfun::ErasedState;

} // namespace yao::re::stt

#elif YAO_CONFIG__RE_ERASED_STATE ==                                           \
    YAO_CONFIG__RE_ERASED_STATE__FUNCTION_POINTER

#include "yao/re/stt/impl/fptr/ErasedState.hpp"

namespace yao::re::stt {

using impl::fptr::ErasedState;

} // namespace yao::re::stt

#elif YAO_CONFIG__RE_ERASED_STATE ==                                           \
    YAO_CONFIG__RE_ERASED_STATE__FUNCTION_OBJECT

#include "yao/re/stt/impl/fobj/ErasedState.hpp"

namespace yao::re::stt {

using impl::fobj::ErasedState;

} // namespace yao::re::stt

#endif

#endif
