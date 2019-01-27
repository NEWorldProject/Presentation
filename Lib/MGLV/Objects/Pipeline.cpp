#include <limits>
#include <MGLV/Functions.h>

namespace GL {
    namespace D {
        extern thread_local Context* _Context;
    }

    void Pipeline::Create() noexcept {
		_CreateInfo = new CreateInfo();
    }

    void Pipeline::Delete() noexcept {
		delete _CreateInfo;
        _Binds.clear();
    }

    void Pipeline::CompileMGLV() noexcept {
		// Success
		_CreateInfo = nullptr;
    }

    void Pipeline::AttachProgram(const Program& program) noexcept {
		_CreateInfo->_Program = std::addressof(program);
    }

    void Pipeline::VertexBufferMGLV(GLuint bindingIndex, Buffer& buffer) noexcept {
    }

    void Pipeline::VertexBuffersMGLV(GLuint first, GLsizei count, const Buffer* buffers) noexcept {
    }

    void Pipeline::AddVertexBindingMGLV(GLuint index, GLsizei stride, GLboolean instanceFeed) noexcept {
        auto& binding = _LocateBinding(index);
        binding.stride = static_cast<uint32_t>(stride);
        binding.inputRate = instanceFeed ? VK_VERTEX_INPUT_RATE_INSTANCE : VK_VERTEX_INPUT_RATE_VERTEX;
    }

    void Pipeline::AddAttribFormatMGLV(GLuint index, GLuint binding, GLint size, GLenum type, GLboolean normalized,
            GLuint offset) noexcept {
        auto& attr = _LocateAttrib(index);
        attr.offset = static_cast<uint32_t>(offset);
        attr.binding = static_cast<uint32_t>(binding);
    }

    void
    Pipeline::AddAttribIFormatMGLV(GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept {
        auto& attr = _LocateAttrib(index);
        attr.offset = static_cast<uint32_t>(offset);
        attr.binding = static_cast<uint32_t>(binding);
    }

    void
    Pipeline::AddAttribLFormatMGLV(GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept {
        auto& attr = _LocateAttrib(index);
        attr.offset = static_cast<uint32_t>(offset);
        attr.binding = static_cast<uint32_t>(binding);
    }

    void Pipeline::BindingDivisor(GLuint bindingIndex, GLuint divisor) noexcept {

    }

    VkVertexInputAttributeDescription& Pipeline::_LocateAttrib(GLuint index) noexcept {
        _CreateInfo->_Attribs.emplace_back().location = static_cast<uint32_t>(index);
        return _CreateInfo->_Attribs.back();
    }

    VkVertexInputBindingDescription& Pipeline::_LocateBinding(GLuint index) noexcept {
		_CreateInfo->_Bindings.emplace_back().binding = static_cast<uint32_t>(index);
		return _CreateInfo->_Bindings.back();
    }
}


void glCreatePipelines(GLsizei n, GLuint *pipelines) noexcept {
    for (GLsizei i = 0; i < n; ++i) {
        auto obj = new GL::Buffer();
        obj->Create();
        pipelines[i] = reinterpret_cast<GLuint>(obj);
    }
}

void glDeletePipelinesMGLV(GLsizei n, const GLuint* pipelines) noexcept {
    for (GLsizei i = 0; i < n; ++i) {
        auto obj = reinterpret_cast<GL::Pipeline*>(pipelines[i]);
        obj->Delete();
        delete obj;
    }
}

void glPipelineCompileMGLV(GLuint pipeline) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->CompileMGLV();
}

void glPipelineElementBufferMGLV(GLuint pipeline, GLuint buffer) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->ElementBuffer(buffer);
}

void glPipelineVertexBufferMGLV(GLuint pipeline, GLuint bindingIndex, GLuint buffer) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->VertexBufferMGLV(bindingIndex, *reinterpret_cast<GL::Buffer*>(buffer));
}

void glPipelineVertexBuffersMGLV(GLuint pipeline, GLuint first, GLsizei count, const GLuint* buffers) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->VertexBuffersMGLV(first, count,
            reinterpret_cast<const GL::Buffer*>(buffers));
}

void glPipelineAddVertexBindingMGLV(GLuint pipeline, GLuint index, GLsizei stride, GLboolean instanceFeed) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->AddVertexBindingMGLV(index, stride, instanceFeed);
}

void glPipelineAddAttribFormatMGLV(GLuint pipeline, GLuint index, GLuint binding, GLint size, GLenum type, GLboolean normalized, GLuint offset) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->AddAttribFormatMGLV(index, binding, size, type, normalized, offset);
}

void glPipelineAddAttribIFormatMGLV(GLuint pipeline, GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->AddAttribIFormatMGLV(index, binding, size, type, offset);
}

void glPipelineAddAttribLFormatMGLV(GLuint pipeline, GLuint index, GLuint binding, GLint size, GLenum type, GLuint offset) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->AddAttribLFormatMGLV(index, binding, size, type, offset);
}

void glPipelineBindingDivisorMGLV(GLuint pipeline, GLuint bindingIndex, GLuint divisor) noexcept {
    reinterpret_cast<GL::Pipeline*>(pipeline)->BindingDivisor(bindingIndex, divisor);
}

