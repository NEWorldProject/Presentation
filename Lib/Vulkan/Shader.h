#pragma once

#include "Common.h"
#include <new>
#include <type_traits>

namespace Presentation::Vulkan {
    class ShaderModule {
    public:
        constexpr ShaderModule() noexcept
                :_Device(nullptr), _Module(nullptr) { }

        template <class C>
        ShaderModule(VkDevice dev, const C& con)
                : _Device(dev), _Module(LoadC<C>()(dev, con)) { }

        template <class Sp>
        ShaderModule(VkDevice dev, const Sp& ptr, size_t size)
                : _Device(dev), _Module(LoadSp<Sp>()(dev, ptr, size)) { }

        ShaderModule(VkDevice dev, void* code, size_t size)
                :_Device(dev), _Module(LoadImpl(dev, code, size)) { }
                
        ShaderModule(const ShaderModule&) = delete;

        ShaderModule& operator=(const ShaderModule&) = delete;

        ShaderModule(ShaderModule&& r) noexcept
        :_Device(r._Device), _Module(r._Module) {
            r._Device = nullptr;
            r._Module = nullptr;
        }

        ShaderModule& operator=(ShaderModule&& r) noexcept {
            if (this != std::addressof(r)) {
                _Device = r._Device;
                _Module = r._Module;
                r._Device = nullptr;
                r._Module = nullptr;
            }
            return *this;
        }
        ~ShaderModule() noexcept { if (_Module) vkDestroyShaderModule(_Device, _Module, nullptr); }

        auto NativeHandle() const noexcept { return _Module; }

        auto Release() noexcept {
            auto ret = _Module;
            _Module = nullptr;
            return ret;
        }

        auto CreateStageInfo(VkShaderStageFlagBits stage, const char* entrance = "main") const noexcept {
            VkPipelineShaderStageCreateInfo stageInfo = {};
            stageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            stageInfo.stage = stage;
            stageInfo.module = NativeHandle();
            stageInfo.pName = entrance;
            return stageInfo;
        }
    private:
        template <class C, class = std::void_t<typename std::is_pointer<decltype(std::declval<C>().data())>::type,
                                               decltype(std::declval<C>().size())>>
        struct LoadC {
            VkShaderModule operator()(VkDevice dev, const C& con) {
                return LoadImpl(dev, con.data(), con.size());
            }
        };

        template <class Sp, class = std::void_t<typename std::is_pointer<decltype(std::declval<Sp>().get())>::type>>
        struct LoadSp {
            VkShaderModule operator()(VkDevice dev, const Sp& ptr, size_t size) {
                return LoadImpl(dev, ptr.get(), size);
            }
        };

        static VkShaderModule LoadImpl(VkDevice device, const void* code, size_t size) {
            VkShaderModuleCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            createInfo.codeSize = size;
            createInfo.pCode = reinterpret_cast<const uint32_t*>(code);

            VkShaderModule shaderModule = nullptr;
            __Details::ErrorCheck(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule));
            return shaderModule;
        }

        VkDevice _Device;
        VkShaderModule _Module;
    };
}
