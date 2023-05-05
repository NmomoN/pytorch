#pragma once

#include <c10/core/Allocator.h>
#include <c10/util/Exception.h>
#include <c10/util/Optional.h>
#include <c10/util/Registry.h>
#include <c10/core/DeviceType.h>

#include <cstddef>
#include <functional>
#include <memory>

// Forward-declares at::Context, at::Generator and at::cuda::NVRTC
namespace at {
class Context;
} // namespace at

// NB: Class must live in `at` due to limitations of Registry.h.
namespace at {

auto privateuse1_backend = get_privateuse1_backend();

struct TORCH_API PrivateUse1HooksInterface {
  virtual ~PrivateUse1HooksInterface() = default;

  virtual void initPrivateUse1() const {
    TORCH_CHECK(
        false, 
        "Cannot initialize " + privateuse1_backend + " without Intel Extension for Pytorch.");
  }

  // virtual const Generator& getDefaultCUDAGenerator(DeviceIndex device_index = -1) const {
  //   (void)device_index; // Suppress unused variable warning
  //   TORCH_CHECK(false, "Cannot get default CUDA generator without ATen_cuda library. ", CUDA_HELP);
  // }

  virtual bool hasPrivateUse1() const {
    return false;
  }
};

// NB: dummy argument to suppress "ISO C++11 requires at least one argument
// for the "..." in a variadic macro"
struct TORCH_API PrivateUse1HooksArgs {};

TORCH_DECLARE_REGISTRY(PrivateUse1HooksRegistry, PrivateUse1HooksInterface, PrivateUse1HooksArgs);
#define REGISTER_PrivateUse1_HOOKS(clsname) \
  C10_REGISTER_CLASS(PrivateUse1HooksRegistry, clsname, clsname)

namespace detail {
TORCH_API const PrivateUse1HooksInterface& getPrivateUse1Hooks();
} // namespace detail
} // namespace at
