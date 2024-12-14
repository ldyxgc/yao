#ifndef __YAO__LAB__RE__STT__ERASED_STATE__HPP__
#define __YAO__LAB__RE__STT__ERASED_STATE__HPP__

#include "yao/config.hpp"

#if YAO_CONFIG__RE_ERASED_STATE == YAO_CONFIG__RE_ERASED_STATE__VIRTUAL_FUNCTION

#include "yao/lab/re/stt/impl/vfun/ErasedState.hpp"

namespace yao::lab::re::stt {

using impl::vfun::ErasedState;

} // namespace yao::lab::re::stt

#elif YAO_CONFIG__RE_ERASED_STATE ==                                           \
    YAO_CONFIG__RE_ERASED_STATE__FUNCTION_POINTER

#include "yao/lab/re/stt/impl/fptr/ErasedState.hpp"

namespace yao::lab::re::stt {

using impl::fptr::ErasedState;

} // namespace yao::lab::re::stt

#elif YAO_CONFIG__RE_ERASED_STATE ==                                           \
    YAO_CONFIG__RE_ERASED_STATE__FUNCTION_OBJECT

#include "yao/lab/re/stt/impl/fobj/ErasedState.hpp"

namespace yao::lab::re::stt {

using impl::fobj::ErasedState;

} // namespace yao::lab::re::stt

#endif

#endif
