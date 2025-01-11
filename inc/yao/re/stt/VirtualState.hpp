#ifndef __YAO__RE__STT__VIRTUAL_STATE__HPP__
#define __YAO__RE__STT__VIRTUAL_STATE__HPP__

#include <compare>
#include <memory>

#include "yao/com.hpp"
#include "yao/re/c_ct_Symbol.hpp"
#include "yao/re/stt/StateBase.hpp"
#include "yao/req/c_r_no_cvref.hpp"

namespace yao::re::stt {

template <typename _Symbol>
  requires req::c_r_no_cvref<_Symbol> && c_ct_Symbol<_Symbol>
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

  virtual ~VirtualState() = default;
};

} // namespace yao::re::stt

#include "yao/re/stt/VirtualState.ipp"

#endif
