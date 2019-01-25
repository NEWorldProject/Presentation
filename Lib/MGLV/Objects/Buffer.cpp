#include <limits>
#include <MGLV/Functions.h>

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

    void Buffer::ClearSubDataMGLV(GLuint unitSize, GLintptr offset, GLsizeiptr size, const void* data) noexcept {
        if (offset<0 || size<0) {
            D::_Context->SetError(GL_INVALID_VALUE);
            return;
        }
        if ((offset%unitSize) || (size%unitSize)) {
            D::_Context->SetError(GL_INVALID_VALUE);
            return;
        }
        if (!data) {
            ZeroSubDataMGLV(offset, size);
        }
        else {
            switch (unitSize) {
            case 4:SegmentFill4(_Buffer, offset, size, *reinterpret_cast<const uint32_t*>(data));
                break;
            case 2:SegmentFill2(_Buffer, offset, size, *reinterpret_cast<const uint16_t*>(data));
                break;
            case 1:SegmentFill1(_Buffer, offset, size, *reinterpret_cast<const uint8_t*>(data));
                break;
            default:D::_Context->SetError(GL_INVALID_ENUM);
            };
        }
    }

    void Buffer::ClearDataMGLV(GLuint unitSize, const void* data) noexcept {
        if (!data) {
            ZeroDataMGLV();
        }
        else {
            switch (unitSize) {
            case 4: {
                const auto val = *reinterpret_cast<const uint32_t*>(data);
                vkCmdFillBuffer(D::_Context->GetCommandBuffer(), _Buffer, 0, VK_WHOLE_SIZE, val);
                return;
            }
            case 2: {
                const auto dt = *reinterpret_cast<const uint16_t*>(data);
                const auto val = dt << 16 | dt;
                vkCmdFillBuffer(D::_Context->GetCommandBuffer(), _Buffer, 0, VK_WHOLE_SIZE, val);
                return;
            }
            case 1: {
                const auto dt = *reinterpret_cast<const uint8_t*>(data);
                const auto val = dt << 24 | dt << 16 | dt << 8 | dt;
                vkCmdFillBuffer(D::_Context->GetCommandBuffer(), _Buffer, 0, VK_WHOLE_SIZE, val);
                return;
            }
            default:D::_Context->SetError(GL_INVALID_ENUM);
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

void glCreateBuffers(GLsizei n, GLuint *buffers) noexcept {
    for (GLsizei i = 0; i < n; ++i) {
        auto obj = new GL::Buffer();
        obj->Create();
        buffers[i] = reinterpret_cast<GLuint>(obj);
    }
}

void glDeleteBuffers(GLsizei n, const GLuint *buffers) noexcept{
    for (GLsizei i = 0; i < n; ++i) {
        auto obj = reinterpret_cast<GL::Buffer*>(buffers[i]);
        obj->Delete();
        delete obj;
    }
}

void glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->Storage(size, data, flags);
}

void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->SubData(offset, size, data);
}

void glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) noexcept {
    GL::Buffer::CopySubData(*reinterpret_cast<GL::Buffer*>(readBuffer), *reinterpret_cast<GL::Buffer*>(writeBuffer),
            readBuffer, writeBuffer, size);
}

void glClearNamedBufferDataMGLV(GLuint buffer, GLuint unitSize, const void* data) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->ClearDataMGLV(unitSize, data);
}

void glClearNamedBufferSubDataMGLV(GLuint buffer, GLuint unitSize, GLintptr offset, GLsizeiptr size, const void* data) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->ClearSubDataMGLV(unitSize, offset, size, data);
}

void glZeroNamedBufferDataMGLV(GLuint buffer) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->ZeroDataMGLV();
}

void glZeroNamedBufferSubDataMGLV(GLuint buffer, GLintptr offset, GLsizeiptr size) noexcept{
    reinterpret_cast<GL::Buffer*>(buffer)->ZeroSubDataMGLV(offset, size);
}

void * glMapNamedBuffer(GLuint buffer, GLenum access) noexcept {
    return reinterpret_cast<GL::Buffer*>(buffer)->Map(access);
}

void * glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) noexcept {
    return reinterpret_cast<GL::Buffer*>(buffer)->MapRange(offset, length, access);
}

GLboolean glUnmapNamedBuffer(GLuint buffer) noexcept {
    return reinterpret_cast<GL::Buffer*>(buffer)->Unmap();
}

void glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length) noexcept {
    reinterpret_cast<GL::Buffer*>(buffer)->FlushMappedRange(offset, length);
}
