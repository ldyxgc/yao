#ifndef __YAO__HELP__HPP__
#define __YAO__HELP__HPP__

#include <concepts>
#include <memory>
#include <type_traits>

namespace yao {

// Zero-terminated string (C-style string)
using zstring = char *;
using czstring = const char *;

template <typename T>
  requires std::is_pointer_v<T>
using owner = T;

template <typename T>
  requires std::is_pointer_v<T> ||
               std::same_as<T, std::unique_ptr<typename T::element_type,
                                               typename T::deleter_type>> ||
               std::same_as<T, std::shared_ptr<typename T::element_type>>
using not_null = T;

} // namespace yao

#endif
