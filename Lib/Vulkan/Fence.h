#pragma once

#include "Common.h"

namespace Presentation::Vulkan {
    class Fence {
    public:
        constexpr Fence() noexcept
                :_Device(nullptr), _Fence(nullptr) { }

        Fence(VkDevice dev)
                :_Device(dev), _Fence(Create()) { }

        Fence(const Fence&) = delete;

        Fence& operator=(const Fence&) = delete;

        Fence(Fence&& r) noexcept
                :_Device(r._Device), _Fence(r._Fence) {
            r._Device = nullptr;
            r._Fence = nullptr;
        }

        Fence& operator=(Fence&& r) noexcept {
            if (this!=std::addressof(r)) {
                _Device = r._Device;
                _Fence = r._Fence;
                r._Device = nullptr;
                r._Fence = nullptr;
            }
            return *this;
        }

        ~Fence() noexcept { if (_Fence) vkDestroyFence(_Device, _Fence, nullptr); }

        auto NativeHandle() const noexcept { return _Fence; }

        auto Release() noexcept {
            auto ret = _Fence;
            _Fence = nullptr;
            return ret;
        }

        void Reset() noexcept { vkResetFences(_Device, 1, &_Fence); }

        void Wait() noexcept { vkWaitForFences(_Device, 1, &_Fence, VK_TRUE, std::numeric_limits<uint64_t>::max()); }
    private:
        VkFence Create() {
            VkFence ret{};
            static constexpr VkFenceCreateInfo info = {
                    .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
                    .flags = VK_FENCE_CREATE_SIGNALED_BIT
            };
            __Details::ErrorCheck(vkCreateFence(_Device, &info, nullptr, &ret));
            return ret;
        }
        VkDevice _Device;
        VkFence _Fence;
    };
}
