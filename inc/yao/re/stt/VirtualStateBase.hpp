#ifndef __YAO__RE__STT__VIRTUAL_STATE_BASE__HPP__
#define __YAO__RE__STT__VIRTUAL_STATE_BASE__HPP__

#include <compare>
#include <memory>
#include <ostream>

#include "yao/def/attr.hpp"
#include "yao/help.hpp"
#include "yao/re/c_t_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/re/stt/StateType.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires c_t_Symbol<_Symbol>
class YAO_ATTR__EMPTY_BASES VirtualStateBase
    : private StateBase<VirtualStateBase<_Symbol>> {
public:
  using Symbol = _Symbol;

protected:
  VirtualStateBase() = default;
  VirtualStateBase(const VirtualStateBase &) = default;

public:
  virtual not_null<owner<VirtualStateBase *>> copy_rptr() const = 0;
  not_null<std::unique_ptr<VirtualStateBase>> copy_uptr() const;

  virtual bool operator==(const VirtualStateBase &rhs) const = 0;
  virtual std::strong_ordering
  operator<=>(const VirtualStateBase &rhs) const = 0;

  virtual StateType type() const = 0;

  virtual void match(const Symbol &symbol) = 0;
  virtual bool is_final() const = 0;
  virtual bool is_dead() const = 0;

  template <bool ns = false, bool tp = false>
  static void osprint_type(std::ostream &os);
  virtual void osprint_value(std::ostream &os, bool ns = false,
                             bool tp = false) const = 0;

  virtual ~VirtualStateBase() = default;
};

} // namespace yao::re::stt

#include "yao/re/stt/VirtualStateBase.ipp"

#endif
