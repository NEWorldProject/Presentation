#pragma once

#include "Common.h"

namespace Presentation::Vulkan {
    class Framebuffer {
    public:
        constexpr Framebuffer() noexcept
                :_Device(nullptr), _Buffer(nullptr) { }

        template <class C, class = std::void_t<typename std::is_pointer<decltype(std::declval<C>().begin())>::type,
                                               decltype(std::declval<C>().size())>>
        Framebuffer(VkDevice dev, VkRenderPass renderPass, const C& attachments, VkExtent2D extent, uint32_t layers = 1)
                : _Device(dev), _Buffer(Create(renderPass, attachments, extent, layers)) { }

        Framebuffer(const Framebuffer&) = delete;

        Framebuffer& operator=(const Framebuffer&) = delete;

        Framebuffer(Framebuffer&& r) noexcept
                :_Device(r._Device), _Buffer(r._Buffer) {
            r._Device = nullptr;
            r._Buffer = nullptr;
        }

        Framebuffer& operator=(Framebuffer&& r) noexcept {
            if (this != std::addressof(r)) {
                _Device = r._Device;
                _Buffer = r._Buffer;
                r._Device = nullptr;
                r._Buffer = nullptr;
            }
            return *this;
        }

        ~Framebuffer() noexcept { if (_Buffer) vkDestroyFramebuffer(_Device, _Buffer, nullptr); }

        auto NativeHandle() const noexcept { return _Buffer; }

        auto Release() noexcept {
            auto ret = _Buffer;
            _Buffer = nullptr;
            return ret;
        }
    private:
        template <class C>
        VkFramebuffer Create(VkRenderPass renderPass, const C& attachments, VkExtent2D extent, uint32_t layers) {
            VkFramebuffer buffer{};
            VkFramebufferCreateInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            info.renderPass = renderPass;
            info.attachmentCount = attachments.size();
            info.pAttachments = std::addressof(*attachments.begin());
            info.width = extent.width;
            info.height = extent.height;
            info.layers = layers;
            __Details::ErrorCheck(vkCreateFramebuffer(_Device, &info, nullptr, &buffer));
            return buffer;
        }

        VkDevice _Device;
        VkFramebuffer _Buffer;
    };
}
