#ifndef __YAO__RE__STT__VIRTUAL_STATE__HPP__
#define __YAO__RE__STT__VIRTUAL_STATE__HPP__

#include <compare>
#include <memory>
#include <ostream>

#include "yao/com.hpp"
#include "yao/prt/PrintTypeArgs.hpp"
#include "yao/prt/PrintValueArgs.hpp"
#include "yao/re/c_r_no_cvref_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires c_r_no_cvref_Symbol<_Symbol>
class VirtualState : private StateBase<VirtualState<_Symbol>> {
public:
  using Symbol = _Symbol;

protected:
  VirtualState() = default;
  VirtualState(const VirtualState &) = default;
  VirtualState(VirtualState &&) = default;
  VirtualState &operator=(const VirtualState &) = default;
  VirtualState &operator=(VirtualState &&) = default;

public:
  virtual not_null<owner<VirtualState *>> copy_rptr() const = 0;
  not_null<std::unique_ptr<VirtualState>> copy_uptr() const;

  virtual void match(const Symbol &symbol) = 0;
  virtual bool is_final() const = 0;
  virtual bool is_dead() const = 0;

  virtual bool operator==(const VirtualState &rhs) const = 0;
  virtual std::strong_ordering operator<=>(const VirtualState &rhs) const = 0;

  static void print_type(std::ostream &os, const prt::PrintTypeArgs &args = {});
  virtual void print_value(std::ostream &os,
                           const prt::PrintValueArgs &args = {},
                           uint indent_level = 0) const = 0;

  virtual ~VirtualState() = default;
};

} // namespace yao::re::stt

#include "yao/re/stt/VirtualState.ipp"

#endif
