//
// Created by 刘予顺 on 2019-01-17.
//

#include <limits>
#include "Functions.h"

namespace GL {
    namespace D {
        thread_local Context* _Context = nullptr;
    }

    Context::Context() {

    }

    VkDevice Context::GetDevice() {
        return nullptr;
    }

    void Context::SetError(int error) {

    }

    VkPhysicalDeviceMemoryProperties& Context::GetPhysicalMemoryProperties() { return _PhysicalMemoryProperties; }

    VkCommandBuffer Context::GetCommandBuffer() {
        return nullptr;
    }

    void Texture::CreateTextures(GLenum target) noexcept {

    }

    void Texture::Storage1D(GLsizei levels, GLenum internalformat, GLsizei width) noexcept {

    }

    void Texture::Storage2D(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) noexcept {

    }

    void
    Texture::Storage3D(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) noexcept {

    }

}
