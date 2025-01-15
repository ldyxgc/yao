#ifndef __YAO__PRT__PRINT_TYPE_ARGS__HPP__
#define __YAO__PRT__PRINT_TYPE_ARGS__HPP__

namespace yao::prt {

struct PrintTypeArgs {
  bool scope = false;     // namespace, struct, class
  bool tmpl_args = false; // template arguments
};

} // namespace yao::prt

#endif
