#ifndef __YAO__RE__STT__STATE__HPP__
#define __YAO__RE__STT__STATE__HPP__

namespace yao::re::stt {

template <typename Symbol> class State {
public:
  virtual void match(const Symbol &symbol) = 0;
  virtual bool is_final() const = 0;
  virtual bool is_dead() const = 0;

  virtual ~State() = default;
};

} // namespace yao::re::stt

#endif
