#pragma once

#include "Common.h"

namespace Presentation::Vulkan {
    class Semaphore {
    public:
        constexpr Semaphore() noexcept
                :_Device(nullptr), _Semaphore(Create()) { }

        Semaphore(VkDevice dev)
                :_Device(dev), _Semaphore(Create()) { }

        Semaphore(const Semaphore&) = delete;

        Semaphore& operator=(const Semaphore&) = delete;

        Semaphore(Semaphore&& r) noexcept
                :_Device(r._Device), _Semaphore(r._Semaphore) {
            r._Device = nullptr;
            r._Semaphore = nullptr;
        }

        Semaphore& operator=(Semaphore&& r) noexcept {
            if (this!=std::addressof(r)) {
                _Device = r._Device;
                _Semaphore = r._Semaphore;
                r._Device = nullptr;
                r._Semaphore = nullptr;
            }
            return *this;
        }

        ~Semaphore() noexcept { if (_Semaphore) vkDestroySemaphore(_Device, _Semaphore, nullptr); }

        auto NativeHandle() const noexcept { return _Semaphore; }

        auto Release() noexcept {
            auto ret = _Semaphore;
            _Semaphore = nullptr;
            return ret;
        }
    private:
        VkSemaphore Create() {
            VkSemaphore ret{};
            static constexpr VkSemaphoreCreateInfo info = {
                    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            };
            __Details::ErrorCheck(vkCreateSemaphore(_Device, &info, nullptr, &ret));
            return ret;
        }
        VkDevice _Device;
        VkSemaphore _Semaphore;
    };
}
