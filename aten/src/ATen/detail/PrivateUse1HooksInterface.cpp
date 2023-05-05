#include <ATen/detail/PrivateUse1HooksInterface.h>

#include <c10/util/Exception.h>
#include <c10/util/CallOnce.h>

#include <cstddef>
#include <memory>
#include <mutex>

namespace at {
namespace detail {

static PrivateUse1HooksInterface* privateuse1_hooks = nullptr;

const PrivateUse1HooksInterface& getPrivateUse1Hooks() {
#if !defined C10_MOBILE
  static c10::once_flag once;
  c10::call_once(once, [] {
    privateuse1_hooks = 
        PrivateUse1HooksRegistry()->Create("PrivateUse1Hooks", PrivateUse1HooksArgs{}).release();
    if (!privateuse1_hooks) {
      privateuse1_hooks = new PrivateUse1HooksInterface();
    }
  });
#else
  if (privateuse1_hooks == nullptr) {
    privateuse1_hooks = new PrivateUse1HooksInterface();
  }
#endif
  return *privateuse1_hooks;
}
} // namespace detail

C10_DEFINE_REGISTRY(PrivateUse1HooksRegistry, PrivateUse1HooksInterface, PrivateUse1HooksArgs)

} // namespace at
