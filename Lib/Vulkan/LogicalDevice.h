#pragma once

#include "Common.h"

namespace Presentation::Vulkan {
    class LogicalDevice {
    public:
        constexpr LogicalDevice() noexcept
                :_Device(nullptr) { }

        LogicalDevice(VkPhysicalDevice physical,
                const std::vector<VkDeviceQueueCreateInfo>& queues,
                const VkPhysicalDeviceFeatures* features,
                const std::vector<const char*>& extensions,
                const std::vector<const char*>& layers
        ) : LogicalDevice() {
            VkPhysicalDeviceFeatures deviceFeatures = {};

            VkDeviceCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

            createInfo.queueCreateInfoCount = static_cast<uint32_t>(queues.size());
            createInfo.pQueueCreateInfos = queues.data();

            createInfo.pEnabledFeatures = &deviceFeatures;

            createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
            createInfo.ppEnabledExtensionNames = extensions.data();

            createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
            createInfo.ppEnabledLayerNames = layers.data();

            __Details::ErrorCheck(vkCreateDevice(physical, &createInfo, nullptr, &_Device));
        }

        LogicalDevice(const LogicalDevice&) = delete;

        LogicalDevice& operator=(const LogicalDevice&) = delete;

        LogicalDevice(LogicalDevice&& r) noexcept
                :_Device(r._Device) {
            r._Device = nullptr;
        }

        LogicalDevice& operator=(LogicalDevice&& r) noexcept {
            if (this != std::addressof(r)) {
                _Device = r._Device;
                r._Device = nullptr;
            }
            return *this;
        }

        ~LogicalDevice() noexcept { if (_Device) vkDestroyDevice(_Device, nullptr); }

        auto NativeHandle() const noexcept { return _Device; }

        auto Release() noexcept {
            auto ret = _Device;
            _Device = nullptr;
            return ret;
        }
    private:
        VkDevice _Device;
    };
}
