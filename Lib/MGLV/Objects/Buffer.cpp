#include "../Functions.h"
#include <limits>

namespace GL {
    namespace D {
        extern thread_local Context* _Context;
    }

    void Buffer::Create() noexcept { }

    void Buffer::Storage(GLsizeiptr size, const void* data, GLbitfield flags) noexcept {
        constexpr auto FlagMap = [](GLbitfield flags) noexcept -> VkMemoryPropertyFlags {
            VkMemoryPropertyFlags ret = 0;
            if ((flags | GL_MAP_READ_BIT) || (flags | GL_MAP_WRITE_BIT))
                ret |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
            if (flags | GL_MAP_COHERENT_BIT)
                ret |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
            return ret;
        };
        constexpr auto UsageMap = [](GLbitfield flags) noexcept -> VkBufferUsageFlags {
            // we do not know what we will do with this, so we or everything none-ext together
            VkBufferUsageFlags ret = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT |
                    VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT |
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
                    VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                    VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
                    VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
                    VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
            if (flags | GL_DYNAMIC_STORAGE_BIT)
                ret |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
            return ret;
        };
        {
            // setup the buffer object
            VkBufferCreateInfo bufferInfo = {};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.size = (size & 0b11) ? (size & (~0b11) + 4) : size;
            bufferInfo.usage = UsageMap(flags);
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            if (auto res = vkCreateBuffer(D::_Context->GetDevice(), &bufferInfo, nullptr, &_Buffer); res!=VK_SUCCESS) {
                D::_Context->SetError(GL_OUT_OF_MEMORY);
                return;
            }
        }
        {
            uint32_t found = std::numeric_limits<uint32_t>::max();
            VkMemoryRequirements memRequirements;
            vkGetBufferMemoryRequirements(D::_Context->GetDevice(), _Buffer, &memRequirements);
            {
                // find a good heap
                const auto& memProperties = D::_Context->GetPhysicalMemoryProperties();
                const auto memFlags = FlagMap(flags);
                for (uint32_t i = 0; i<memProperties.memoryTypeCount; ++i) {
                    if (memRequirements.memoryTypeBits & (1 << i)
                            && (memProperties.memoryTypes[i].propertyFlags & memFlags)==memFlags) {
                        found = i;
                        break;
                    }
                }
                if (found==std::numeric_limits<uint32_t>::max()) {
                    D::_Context->SetError(GL_OUT_OF_MEMORY);
                    return;
                }
            }
            {
                // Allocate the memory
                VkMemoryAllocateInfo allocInfo = {};
                allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                allocInfo.allocationSize = memRequirements.size;
                allocInfo.memoryTypeIndex = found;
                if (vkAllocateMemory(D::_Context->GetDevice(), &allocInfo, nullptr, &_Memory)!=VK_SUCCESS) {
                    D::_Context->SetError(GL_OUT_OF_MEMORY);
                    return;
                }
            }
        }
        vkBindBufferMemory(D::_Context->GetDevice(), _Buffer, _Memory, 0);
    }

    void Buffer::Delete() noexcept {
        vkDestroyBuffer(D::_Context->GetDevice(), _Buffer, nullptr);
        vkFreeMemory(D::_Context->GetDevice(), _Memory, nullptr);
        _Buffer = VK_NULL_HANDLE;
        _Memory = VK_NULL_HANDLE;
    }

    void Buffer::SubData(GLintptr offset, GLsizeiptr size, const void* data) noexcept {
        vkCmdUpdateBuffer(D::_Context->GetCommandBuffer(), _Buffer, static_cast<VkDeviceSize>(offset), size, data);
    }

    void* Buffer::Map(GLenum access) noexcept {
        void* ret{};
        if (vkMapMemory(D::_Context->GetDevice(), _Memory, 0, VK_WHOLE_SIZE, 0, &ret)!=VK_SUCCESS) {
            D::_Context->SetError(GL_OUT_OF_MEMORY);
            return nullptr;
        }
        return ret;
    }

    GLboolean Buffer::Unmap() noexcept {
        vkUnmapMemory(D::_Context->GetDevice(), _Memory);
        return GL_TRUE;
    }

    void* Buffer::MapRange(GLintptr offset, GLsizeiptr length, GLbitfield access) noexcept {
        void* ret{};
        if (vkMapMemory(D::_Context->GetDevice(), _Memory, 0, length, 0, &ret)!=VK_SUCCESS) {
            D::_Context->SetError(GL_OUT_OF_MEMORY);
            return nullptr;
        }
        return ret;
    }

    void Buffer::CopySubData(Buffer& read, Buffer& write, GLintptr readOffset, GLintptr writeOffset,
            GLsizeiptr size) noexcept {
        VkBufferCopy reg{static_cast<VkDeviceSize>(readOffset), static_cast<VkDeviceSize>(writeOffset), size};
        vkCmdCopyBuffer(D::_Context->GetCommandBuffer(), read._Buffer, write._Buffer, 1, &reg);
    }

    namespace {
        auto TypeMatch(GLenum internalFormat, GLenum format, GLenum type) noexcept {
            #define C(fmt, t) return (format == fmt) && (type == t);
            switch (internalFormat) {
            case GL_R8: C(GL_RED, GL_UNSIGNED_BYTE)
            case GL_R16: C(GL_RED, GL_UNSIGNED_SHORT)
            case GL_R16F: C(GL_RED, GL_HALF_FLOAT)
            case GL_R32F: C(GL_RED, GL_FLOAT)
            case GL_R8I: C(GL_RED, GL_BYTE)
            case GL_R16I: C(GL_RED, GL_SHORT)
            case GL_R32I: C(GL_RED, GL_INT)
            case GL_R8UI: C(GL_RED, GL_UNSIGNED_BYTE)
            case GL_R16UI: C(GL_RED, GL_UNSIGNED_SHORT)
            case GL_R32UI: C(GL_RED, GL_UNSIGNED_INT)
            case GL_RG8: C(GL_RG, GL_UNSIGNED_BYTE)
            case GL_RG16: C(GL_RG, GL_UNSIGNED_SHORT)
            case GL_RG16F: C(GL_RG, GL_HALF_FLOAT)
            case GL_RG8I: C(GL_RG, GL_BYTE)
            case GL_RG16I: C(GL_RG, GL_SHORT)
            case GL_RG8UI: C(GL_RG, GL_UNSIGNED_BYTE)
            case GL_RG16UI: C(GL_RG, GL_UNSIGNED_SHORT)
            case GL_RGBA8: C(GL_RGBA, GL_UNSIGNED_BYTE)
            case GL_RGBA8I:C(GL_RGBA, GL_BYTE)
            case GL_RGBA8UI: C(GL_RGBA, GL_UNSIGNED_BYTE)
            default:return false;
            }
            #undef C
        }

        auto GetUnitSize(GLenum internalFormat) noexcept {
            switch (internalFormat) {
            case GL_R8: return 1;
            case GL_R16: return 2;
            case GL_R16F: return 2;
            case GL_R32F: return 4;
            case GL_R8I: return 1;
            case GL_R16I: return 2;
            case GL_R32I: return 4;
            case GL_R8UI: return 1;
            case GL_R16UI: return 2;
            case GL_R32UI: return 4;
            case GL_RG8: return 2;
            case GL_RG16: return 4;
            case GL_RG16F: return 4;
            case GL_RG8I: return 2;
            case GL_RG16I: return 4;
            case GL_RG8UI: return 2;
            case GL_RG16UI: return 4;
            case GL_RGBA8: return 4;
            case GL_RGBA8I: return 4;
            case GL_RGBA8UI: return 4;
            default:return -1;
            }
        }

        uint32_t GetUnitAlign(GLenum internalFormat) noexcept {
            switch (internalFormat) {
            case GL_R8: return 1;
            case GL_R16: return 2;
            case GL_R16F: return 2;
            case GL_R32F: return 4;
            case GL_R8I: return 1;
            case GL_R16I: return 2;
            case GL_R32I: return 4;
            case GL_R8UI: return 1;
            case GL_R16UI: return 2;
            case GL_R32UI: return 4;
            case GL_RG8: return 1;
            case GL_RG16: return 2;
            case GL_RG16F: return 2;
            case GL_RG8I: return 1;
            case GL_RG16I: return 2;
            case GL_RG8UI: return 1;
            case GL_RG16UI: return 2;
            case GL_RGBA8: return 1;
            case GL_RGBA8I: return 1;
            case GL_RGBA8UI: return 1;
            default:return std::numeric_limits<uint32_t>::max();
            }
        }

        void SegmentFill4(VkBuffer buffer, GLintptr offset, GLsizeiptr size, uint32_t data) noexcept {
            if (size)
                vkCmdFillBuffer(D::_Context->GetCommandBuffer(), buffer, static_cast<VkDeviceSize>(offset), size, data);
        }

        void SegmentFill2(VkBuffer buffer, GLintptr offset, GLsizeiptr size, uint16_t data) noexcept {
            if (size) {
                const uint32_t val = data << 16 | data;
                if (const auto rm = offset & 0b11; rm) {
                    const auto _offset = static_cast<VkDeviceSize>(offset);
                    vkCmdUpdateBuffer(D::_Context->GetCommandBuffer(), buffer, _offset, 2, &val);
                    offset += 2;
                    size -= 2;
                }
                const auto aligned = size & (~0b11);
                const auto remain = size-aligned;
                SegmentFill4(buffer, offset, aligned, val);
                if (remain)
                    vkCmdUpdateBuffer(D::_Context->GetCommandBuffer(), buffer, offset+aligned, remain, &val);
            }
        }

        void SegmentFill1(VkBuffer buffer, GLintptr offset, GLsizeiptr size, uint8_t data) noexcept {
            if (size) {
                const uint32_t val = data << 24 | data << 16 | data << 8 | data;
                if (const auto rm = offset & 0b11; rm) {
                    const auto bytes = static_cast<VkDeviceSize>(4-rm);
                    const auto _offset = static_cast<VkDeviceSize>(offset);
                    vkCmdUpdateBuffer(D::_Context->GetCommandBuffer(), buffer, _offset, bytes, &val);
                    offset += bytes;
                    size -= bytes;
                }
                const auto aligned = size & (~0b11);
                const auto remain = size-aligned;
                SegmentFill4(buffer, offset, aligned, val);
                if (remain)
                    vkCmdUpdateBuffer(D::_Context->GetCommandBuffer(), buffer, offset+aligned, remain, &val);
            }
        }
    }

    void Buffer::ClearSubData(GLenum internalFormat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type,
            const void* data) noexcept {
        if (auto a = GetUnitAlign(internalFormat); (offset%a) || (size%a) || !TypeMatch(internalFormat, format, type)) {
            D::_Context->SetError(a==std::numeric_limits<uint32_t>::max() ? GL_INVALID_ENUM : GL_INVALID_VALUE);
            return;
        }
        if (!data) {
            ZeroSubDataMGLV(offset, size);
        }
        else {
            if (offset<0 || size<0) {
                D::_Context->SetError(GL_INVALID_VALUE);
                return;
            }
            if (TypeMatch(internalFormat, format, type)) {
                const auto* buffer = reinterpret_cast<const uint32_t*>(data);
                const auto unitSize = GetUnitSize(internalFormat);
                if (unitSize==4)
                    SegmentFill4(_Buffer, offset, size, buffer[0]);
                else if (unitSize==2)
                    SegmentFill2(_Buffer, offset, size, *reinterpret_cast<const uint16_t*>(buffer));
                else if (unitSize==1)
                    SegmentFill1(_Buffer, offset, size, *reinterpret_cast<const uint8_t*>(buffer));
            }
            else {
                D::_Context->SetError(GL_INVALID_ENUM);
            }
        }
    }

    void Buffer::ClearData(GLenum internalFormat, GLenum format, GLenum type, const void* data) noexcept {
        if (!data) {
            ZeroDataMGLV();
        }
        else {
            if (TypeMatch(internalFormat, format, type)) {
                const auto* buffer = reinterpret_cast<const uint32_t*>(data);
                const auto unitSize = GetUnitSize(internalFormat);
                if (unitSize==4) {
                    const auto val = buffer[0];
                    vkCmdFillBuffer(D::_Context->GetCommandBuffer(), _Buffer, 0, VK_WHOLE_SIZE, val);
                }
                else if (unitSize==2) {
                    const auto dt = *reinterpret_cast<const uint16_t*>(buffer);
                    const auto val = dt << 16 | dt;
                    vkCmdFillBuffer(D::_Context->GetCommandBuffer(), _Buffer, 0, VK_WHOLE_SIZE, val);
                }
                else if (unitSize==1) {
                    const auto dt = *reinterpret_cast<const uint8_t*>(buffer);
                    const auto val = dt << 24 | dt << 16 | dt << 8 | dt;
                    vkCmdFillBuffer(D::_Context->GetCommandBuffer(), _Buffer, 0, VK_WHOLE_SIZE, val);
                }
            }
            else {
                D::_Context->SetError(GL_INVALID_ENUM);
            }
        }
    }

    void Buffer::ZeroDataMGLV() noexcept {
        vkCmdFillBuffer(D::_Context->GetCommandBuffer(), _Buffer, 0, VK_WHOLE_SIZE, 0);
    }

    void Buffer::ZeroSubDataMGLV(GLintptr offset, GLsizeiptr size) noexcept {
        if (offset<0 || size<0)
            D::_Context->SetError(GL_INVALID_VALUE);
        else
            SegmentFill1(_Buffer, offset, size, 0);
    }

    void Buffer::FlushMappedRange(GLintptr offset, GLsizeiptr length) noexcept {
        VkMappedMemoryRange range {
            VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
            nullptr,
            _Memory, static_cast<VkDeviceSize>(offset), length
        };
        vkFlushMappedMemoryRanges(D::_Context->GetDevice(), 1, &range);
    }

}
